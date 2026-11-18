#include "app_protocol_sim_state.h"

uint16_t crc_16_modbus(const uint8_t *data, uint16_t length)
{
    uint16_t crc = 0xFFFF;
    while (length--) {
        crc ^= *data++;
        for (uint8_t i = 0; i < 8; i++) {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

uint8_t app_panel_frame_sum(uint8_t *rxbuf, uint8_t len)
{
    uint8_t sum = 0;
    for (uint8_t i = 0; i < len; i++)
        sum += rxbuf[i];
    return sum; // 直接返回累加和
}

AppProtocolSimState::AppProtocolSimState(QObject *parent, AppProtocolSetConfig *config, AppSerial *serialWidget)
    : QObject(parent)
{
    m_config       = config;
    m_serialWidget = serialWidget;
}

// 接收模拟按键数据
void AppProtocolSimState::RecvSimPanelData(const panel_frame_t panel_frame)
{
    if (panel_frame.panel_tx_head != 0xAA) {
        return;
    }

    QByteArray sim_panel_frame; // 用于保存按键发出的数据

    // 增加上位机软件所需的帧头
    sim_panel_frame.append(static_cast<char>(0xFF));
    sim_panel_frame.append(static_cast<char>(0xAA));
    sim_panel_frame.append(static_cast<char>(12));
    sim_panel_frame.append(static_cast<char>(8));
    sim_panel_frame.append(reinterpret_cast<const char *>(&panel_frame), sizeof(panel_frame));

    if (m_serialWidget && m_serialWidget->SerialIsOpen()) {
        m_serialWidget->SerialSendData(sim_panel_frame); // 调用串口发送给上位机
    }

    RecvPanelFrame(sim_panel_frame.mid(4, 12)); // 向后偏移4个字节,去掉上位机所需的帧头
}

// 接收模拟led数据
void AppProtocolSimState::RecvSimLedData(const uint8_t led_num, const uint8_t lum, const uint8_t cct)
{
    my_extend_all_status.led[led_num].lum = lum;
    my_extend_all_status.led[led_num].cct = cct;

    QByteArray sim_frame;
    sim_frame.append(static_cast<char>(0xFF));
    sim_frame.append(static_cast<char>(0xAA));
    sim_frame.append(static_cast<char>(152));
    sim_frame.append(static_cast<char>(7));
    sim_frame.append(BuildExtendRecvFrame());

    if (m_serialWidget && m_serialWidget->SerialIsOpen()) {
        m_serialWidget->SerialSendData(sim_frame);
    }
}

// 接收模拟继电器数据
void AppProtocolSimState::RecvSimRelayData(const uint8_t num, const bool status)
{
    uint8_t byte_index = num / 8;
    uint8_t bit_index  = num % 8;

    if (status) {
        my_extend_all_status.relay[byte_index] |= (1 << bit_index);
    } else {
        my_extend_all_status.relay[byte_index] &= ~(1 << bit_index);
    }

    QByteArray sim_frame;
    sim_frame.append(static_cast<char>(0xFF));
    sim_frame.append(static_cast<char>(0xAA));
    sim_frame.append(static_cast<char>(152));
    sim_frame.append(static_cast<char>(7));
    sim_frame.append(BuildExtendRecvFrame());

    if (m_serialWidget && m_serialWidget->SerialIsOpen()) {
        m_serialWidget->SerialSendData(sim_frame); // 调用串口发送
    }
}

// 接收面板数据
void AppProtocolSimState::RecvPanelFrame(const QByteArray &data)
{
    uint8_t frame_type = data[1];
    uint8_t panel_addr = data[3];
    uint8_t status     = data[5];
    uint8_t key_num    = data[6];

    switch (frame_type) {
        case SIM_KEY: {
            bool key_status          = (status >> key_num) & 0x01; // 计算出该按键的状态
            bind_data_t allBindsData = m_config->getAllBindData();
            for (const bind_save_t &item : std::as_const(allBindsData.bind_data)) {
                uint8_t bind_addr     = static_cast<uint8_t>(item.bind_data[0]);
                uint8_t bind_key_num  = static_cast<uint8_t>(item.bind_data[1]);
                uint8_t bind_status   = static_cast<uint8_t>(item.bind_data[2]);
                uint8_t bind_scene_id = static_cast<uint8_t>(item.bind_data[3]);

                if ((bind_addr == panel_addr) && (bind_key_num == key_num) && (key_status == bind_status) && (bind_scene_id != 0xFF)) {
                    ExeSceneById(bind_scene_id);
                }
            }
        } break;
        case SIM_KNOB_LUM:
        case SIM_KNOB_CCT: {
            uint8_t lum = data[7];
            uint8_t cct = data[8];

            bind_knob_data_t allBindsKnobData = m_config->getAllBindKnobData();
            for (const bind_save_knob_t &item : std::as_const(allBindsKnobData.bind_knob_data)) {
                uint8_t bind_addr        = static_cast<uint8_t>(item.bind_data[0]);
                uint8_t bind_open_scene  = static_cast<uint8_t>(item.bind_data[1]);
                uint8_t bind_close_scene = static_cast<uint8_t>(item.bind_data[2]);
                uint8_t bind_ctrls[8]    = {0};
                std::memcpy(bind_ctrls, item.bind_data.constData() + 3, 8);

                if (bind_addr != panel_addr) {
                    continue;
                }
                uint8_t lastLum = m_knob_last_lum[panel_addr];
                if (lastLum == 0 && lum != 0) { // 由灭到亮,执行开场景
                    if (bind_open_scene != 0xFF) {
                        ExeSceneById(bind_open_scene);
                    }
                } else if (lastLum != 0 && lum == 0) { // 由亮到灭,执行关场景
                    if (bind_close_scene != 0xFF) {
                        ExeSceneById(bind_close_scene);
                    }
                }
                m_knob_last_lum[panel_addr] = lum;

                for (int byte_idx = 0; byte_idx < 8; ++byte_idx) {
                    for (int bit_idx = 0; bit_idx < 8; ++bit_idx) {
                        int led_index = byte_idx * 8 + bit_idx;

                        if ((bind_ctrls[byte_idx] >> bit_idx) & 0x01) {
                            my_extend_all_status.led[led_index].lum = lum;
                            my_extend_all_status.led[led_index].cct = cct;
                        }
                    }
                }
            }
            SendExtendData(BuildExtendRecvFrame());
        } break;
        default:
            return;
    }
}

// 执行场景
void AppProtocolSimState::ExeSceneById(const uint8_t scene_id)
{
    config_data_t localConfig = m_config->getSceneConfigDataById(scene_id);

    if (!localConfig.scene.isEmpty()) {
        // uint8_t   id    = localConfig.scene[0].scene_id;
        QString name    = localConfig.scene[0].scene_name;
        QByteArray data = localConfig.scene[0].scene_data;

        scene_id_panel_t panel_scenes; // 用于存放该场景下的面板数据
        FindPanenDataById(data, panel_scenes);

        // 遍历每个面板
        for (uint8_t j = 0; j < PANEL_DEV_MAX; j++) {
            uint8_t sub_idx  = j / 8;
            uint8_t addr_idx = j % 8;

            panel_sub_idx *target_idx = &my_panel_full_status.sub_frame[sub_idx].idx[addr_idx];
            uint8_t ctrl              = panel_scenes.panel_ctrl[j];
            uint8_t status            = panel_scenes.panel_status[j];
            target_idx->status        = (target_idx->status & ~ctrl) | (status & ctrl);

            uint8_t r_1 = panel_scenes.panel_reserve_1[j];
            uint8_t r_2 = panel_scenes.panel_reserve_2[j];
            if (r_1 & 0x80) {
                target_idx->reserve_1 = r_1;
            }
            if (r_2 & 0x80) {
                target_idx->reserve_2 = r_2;
            }
        }
        SendPanelData(BilidPanelRecvFrame());

        // 找出LED的数据
        QByteArray led_data;
        if (FindLedDataFromScene(data, led_data)) {
            const uint8_t *src = reinterpret_cast<const uint8_t *>(led_data.constData());

            for (int i = 0; i < 64; ++i) // 128 个字节,64组数据
            {
                uint8_t raw_lum = src[i * 2];     // 亮度字节
                uint8_t raw_cct = src[i * 2 + 1]; // 色温字节
                if (raw_lum & 0x80) {
                    my_extend_all_status.led[i].lum = static_cast<uint8_t>(raw_lum & 0x7F);
                }
                if (raw_cct & 0x80) {
                    my_extend_all_status.led[i].cct = static_cast<uint8_t>(raw_cct & 0x7F);
                }
            }
        }

        // 找出RELAY的数据
        QByteArray relay_data;
        if (FindRelayDataFromScene(data, relay_data)) {
            for (int i = 0; i < 8; ++i) {
                uint8_t ctrl_byte   = static_cast<uint8_t>(relay_data[i * 2]);
                uint8_t status_byte = static_cast<uint8_t>(relay_data[i * 2 + 1]);

                my_extend_all_status.relay[i] = (my_extend_all_status.relay[i] & ~ctrl_byte) | (status_byte & ctrl_byte);
            }
        }
        // qDebug() << "SendExtendData:" << BuildExtendRecvFrame().toHex(' ').toUpper();
        SendExtendData(BuildExtendRecvFrame());
    }
}

// 找出该场景下的面板数据
void AppProtocolSimState::FindPanenDataById(const QByteArray &data, scene_id_panel_t &out_scene_id)
{
    // 重置内存
    std::memset(&out_scene_id, 0, sizeof(scene_id_panel_t));

    // 寻找 "PANEL:" 关键字
    const QByteArray marker = "PANEL:";
    int panelIdx            = data.indexOf(marker);

    if (panelIdx == -1) {
        qWarning() << "PANEL marker not found!";
        return;
    }
    // 跳过 "PANEL:" (6 字节)
    int offset = panelIdx + marker.size();

    // 计算面板数据总共需要多少字节 (4 * PANEL_DEV_MAX，也就是 4 * 32 = 128 字节)
    int requiredLen = PANEL_DEV_MAX * 4;

    if (data.size() - offset < requiredLen) {
        qCritical() << "Panel data size error! Available:" << (data.size() - offset) << "Required:" << requiredLen;
        return;
    }
    const uint8_t *cfg = reinterpret_cast<const uint8_t *>(data.constData()) + offset;

    std::memcpy(out_scene_id.panel_ctrl, cfg, PANEL_DEV_MAX);
    std::memcpy(out_scene_id.panel_status, cfg + PANEL_DEV_MAX, PANEL_DEV_MAX);
    std::memcpy(out_scene_id.panel_reserve_1, cfg + PANEL_DEV_MAX * 2, PANEL_DEV_MAX);
    std::memcpy(out_scene_id.panel_reserve_2, cfg + PANEL_DEV_MAX * 3, PANEL_DEV_MAX);
}

// 找出该场景下的LED数据
bool AppProtocolSimState::FindLedDataFromScene(const QByteArray &scene_data, QByteArray &out_led_data)
{
    const QByteArray marker = "LED:";
    int index               = scene_data.indexOf(marker);

    if (index != -1 && (index + marker.size() + 128) <= scene_data.size()) {
        out_led_data = scene_data.mid(index + marker.size(), 128);
        return true;
    }
    return false;
}

// 找出该场景下的RELAY数据
bool AppProtocolSimState::FindRelayDataFromScene(const QByteArray &scene_data, QByteArray &relay_data)
{
    const QByteArray marker = "RELAY:";
    int index               = scene_data.indexOf(marker);

    if (index != -1 && (index + marker.size() + 16) <= scene_data.size()) {
        relay_data = scene_data.mid(index + marker.size(), 16);
        return true;
    }
    return false;
}

// 构造面板接收数据帧
const QByteArray AppProtocolSimState::BilidPanelRecvFrame()
{
    panel_tx_buf_t my_panel_tx_buf = {};
    my_panel_tx_buf.fh_1           = PANEL_FRAME_TX_HEAD_1;
    my_panel_tx_buf.fh_2           = PANEL_FRAME_TX_HEAD_2;
    my_panel_tx_buf.type           = PANEL_FRAME_TX_TYPE;
    my_panel_tx_buf.length         = sizeof(my_panel_full_status);
    my_panel_tx_buf.full_frame     = my_panel_full_status;
    my_panel_tx_buf.crc            = app_panel_frame_sum((uint8_t *)my_panel_full_status.sub_frame, sizeof(my_panel_full_status.sub_frame));
    my_panel_tx_buf.ft_1           = 0x0D;
    my_panel_tx_buf.ft_2           = 0x0A;
    QByteArray sendData(reinterpret_cast<const char *>(&my_panel_tx_buf), sizeof(my_panel_tx_buf));
    // qDebug() << "Panel Tx Data (Hex):" << sendData.toHex(' ');
    return QByteArray(reinterpret_cast<const char *>(&my_panel_tx_buf), sizeof(my_panel_tx_buf));
}

// 构造扩展数据帧
const QByteArray AppProtocolSimState::BuildExtendRecvFrame()
{
    extend_tx_buf_t my_extend_tx_buf = {};

    // 填充帧头 (FB FC)
    my_extend_tx_buf.fh_1 = 0xFB;
    my_extend_tx_buf.fh_2 = 0xFC;

    // 填充 LED 识别码 ("LED:")
    my_extend_tx_buf.led_tag[0] = 'L';
    my_extend_tx_buf.led_tag[1] = 'E';
    my_extend_tx_buf.led_tag[2] = 'D';
    my_extend_tx_buf.led_tag[3] = ':';

    // 填充 64 路 LED 数据 (直接拷贝 my_extend_all_status.led)
    std::memcpy(my_extend_tx_buf.led, my_extend_all_status.led, sizeof(my_extend_tx_buf.led));

    // 填充 Relay 识别码 ("RELAY:")
    my_extend_tx_buf.relay_tag[0] = 'R';
    my_extend_tx_buf.relay_tag[1] = 'E';
    my_extend_tx_buf.relay_tag[2] = 'L';
    my_extend_tx_buf.relay_tag[3] = 'A';
    my_extend_tx_buf.relay_tag[4] = 'Y';
    my_extend_tx_buf.relay_tag[5] = ':';

    // 填充 Relay 数据 (直接拷贝 my_extend_all_status.relay)
    std::memcpy(my_extend_tx_buf.relay, my_extend_all_status.relay, sizeof(my_extend_tx_buf.relay));

    // 计算 CRC16 校验 (从 led_tag 开始到 relay 数据结束)
    const uint8_t *crc_start_ptr = (const uint8_t *)&my_extend_tx_buf.led_tag;

    // 计算参与校验的数据总长度 (led_tag[4] + led[128] + relay_tag[6] + relay[64] = 202 字节)
    uint16_t crc_len = sizeof(my_extend_tx_buf.led_tag) + sizeof(my_extend_tx_buf.led) + sizeof(my_extend_tx_buf.relay_tag) + sizeof(my_extend_tx_buf.relay);
    uint16_t crc     = crc_16_modbus(crc_start_ptr, crc_len);

    my_extend_tx_buf.crc16_h = crc & 0xFF;
    my_extend_tx_buf.crc16_l = (crc >> 8) & 0xFF;

    // 填充帧尾 (0D 0A)
    my_extend_tx_buf.ft_1 = 0x0D;
    my_extend_tx_buf.ft_2 = 0x0A;

    // 构造二进制 QByteArray 字节流
    QByteArray sendData(reinterpret_cast<const char *>(&my_extend_tx_buf), sizeof(my_extend_tx_buf));
    // qDebug() << "sendData:" << sendData.toHex(' ').toUpper();
    return sendData;
}
