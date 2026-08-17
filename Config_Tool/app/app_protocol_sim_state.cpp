#include "app_protocol_sim_state.h"


uint8_t *app_get_led_by_num(extend_all_status_t *status, uint8_t index)
{
    if (status == NULL) return NULL;

    if (index < 4) {
        return &status->led_sel_1[index];
    } else if (index < 16) {
        return &status->led_sel_2[index - 4];
    } else if (index < 24) {
        return &status->led_sel_3[index - 16];
    } else if (index < 32) {
        return &status->led_sel_4[index - 24];
    }
    return NULL;
}

uint8_t app_panel_frame_crc(uint8_t *rxbuf, uint8_t len)
{
    uint8_t i, sum = 0;
    for (i = 0; i < len; i++) sum = sum + rxbuf[i];
    return (0xff - sum + 1);
}

uint8_t app_panel_frame_sum(uint8_t *rxbuf, uint8_t len)
{
    uint8_t sum = 0;
    for (uint8_t i = 0; i < len; i++)
        sum += rxbuf[i];
    return sum; // 直接返回累加和
}


AppProtocolSimState::AppProtocolSimState(QObject *parent, AppProtocolSetConfig * config, AppSerial* serialWidget)
    : QObject(parent)
{
    m_config = config;
    m_serialWidget = serialWidget;
}

// 接收模拟按键数据
void AppProtocolSimState::RecvSimPanelData(const panel_frame_t panel_frame)
{
    if(panel_frame.panel_tx_head != 0xAA){
        return;
    }
    QByteArray build_panel_frame = BilidPanelSendFrame(panel_frame);    // 构造面板发送数据帧

    if(m_serialWidget && m_serialWidget->SerialIsOpen())
    {
        m_serialWidget->SerialSendData(build_panel_frame);// 调用串口发送
    }
    RecvPanelFrame(build_panel_frame);
}

// 接收面板数据
void AppProtocolSimState::RecvPanelFrame(const QByteArray &data)
{
    uint8_t frame_type = data[1];
    uint8_t panel_addr = data[3];
    uint8_t status     = data[5];
    uint8_t key_num    = data[6];

    switch(frame_type)
    {
    case SIM_KEY:{
        bool key_status = (status >> key_num) & 0x01; // 计算出该按键的状态
        bind_data_t allBindsData = m_config->getAllBindData();
        for (const bind_save_t& item : std::as_const(allBindsData.bind_data))
        {
            uint8_t bind_addr     = static_cast<uint8_t>(item.bind_data[0]);
            uint8_t bind_key_num  = static_cast<uint8_t>(item.bind_data[1]);
            uint8_t bind_status   = static_cast<uint8_t>(item.bind_data[2]);
            uint8_t bind_scene_id = static_cast<uint8_t>(item.bind_data[3]);

            if ((bind_addr == panel_addr) && (bind_key_num == key_num) && (key_status == bind_status) && (bind_scene_id != 0xFF))
            {
                ExeSceneById(bind_scene_id);
            }
        }
    }break;
    case SIM_KNOB:{

    }break;
    default:
        return;
    }
}

void AppProtocolSimState::ExeSceneById(const uint8_t scene_id)
{
    config_data_t localConfig = m_config->getSceneConfigDataById(scene_id);

    if (!localConfig.scene.isEmpty())
    {
        uint8_t   id    = localConfig.scene[0].scene_id;
        QString   name  = localConfig.scene[0].scene_name;
        QByteArray data = localConfig.scene[0].scene_data;

        qDebug() << "场景 ID   :" << id;
        qDebug() << "场景名称  :" << name;
        qDebug() << "场景数据  :" << data.toHex(' ').toUpper();

        scene_id_t get_scene_id = {};
        UnpackSceneData(data, get_scene_id);

        // 构造发送给面板设备的数据帧
        for (uint8_t j = 0; j < PANEL_DEV_MAX; j++) {

            uint8_t sub_idx  = j / 8; // 在哪个 sub_frame 中

            for (uint8_t bit = 0; bit <= 5; bit++) {
                // 如果 ctrl 的该位被勾选,则赋值 status 对应位
                if (get_scene_id.key_ctrl[j] & (1U << bit)) {

                    my_panel_full_status.sub_frame[sub_idx].idx[j].status &= ~(1U << bit);
                    my_panel_full_status.sub_frame[sub_idx].idx[j].status |= (get_scene_id.key_status[j] & (1U << bit));
                }
            }
            if ((get_scene_id.key_reserve[j] & 0x80)) { // 是否控制该旋钮

                my_panel_full_status.sub_frame[sub_idx].idx[j].status |= (1U << 6); // 将 status 的 bit6 置1,表示key_reserve中的数据为旋钮值
                my_panel_full_status.sub_frame[sub_idx].idx[j].reserve = get_scene_id.key_reserve[j] & 0x7F;
            }
        }

        // 构造发送给扩展的数据帧
        for (uint8_t j = 0; j < LED_NUM_MAX; j++) {
            if (!(get_scene_id.led[j] & 0x80)) continue;

            uint8_t val    = get_scene_id.led[j] & 0x7F; // 读取实际的亮度值
            uint8_t *p_led = app_get_led_by_num(&my_extend_all_status, j);
            if (p_led) *p_led = val;
        }

        // 将 relay_sel_1 的首地址作为 9 字节缓冲区的起点
        for (uint8_t g = 0; g < 9; g++)
        {
            uint8_t ctrl   = get_scene_id.relay[g * 2];
            uint8_t status = get_scene_id.relay[g * 2 + 1];

            if (ctrl == 0)
                continue;

            if (g < 6)
            {
                my_extend_all_status.relay_sel_1[g] =
                    (my_extend_all_status.relay_sel_1[g] & ~ctrl) |
                    (status & ctrl);
            }
            else
            {
                my_extend_all_status.relay_sel_2[g - 6] =
                    (my_extend_all_status.relay_sel_2[g - 6] & ~ctrl) |
                    (status & ctrl);
            }
        }
        SendPanelData(BilidPanelRecvFrame());
        SendExtendData(BuildExtendRecvFrame());
    }
    else
    {
        qDebug() << "未捞到场景 ID" << scene_id << "的数据，无法打印";
    }
}

void AppProtocolSimState::UnpackSceneData(const QByteArray &data, scene_id_t &out_scene_id)
{
    if (data.size() != SCENE_INFO_SIZE) {
        qCritical() << "Scene data length error:" << data.size();
        return;
    }

    const uint8_t *cfg = reinterpret_cast<const uint8_t*>(data.constData());
    uint16_t offset = 0;

    // scene
    out_scene_id.id = cfg[offset];
    offset += 1 + 1;
    // relay
    memcpy(out_scene_id.relay, &cfg[offset], RELAY_NUM_MAX);
    offset += RELAY_NUM_MAX + 1;

    // led
    memcpy(out_scene_id.led, &cfg[offset], LED_NUM_MAX);
    // APP_PRINTF_BUF("led", my_scene_id[insert].led, LED_NUM_MAX);
    offset += (LED_NUM_MAX * 2) + 1; // 实际发下来的是64路led的状态,故而这里要乘2

    // key_ctrl
    memcpy(out_scene_id.key_ctrl, &cfg[offset], PANEL_DEV_MAX);
    offset += PANEL_DEV_MAX + 1;

    // key_status
    memcpy(out_scene_id.key_status, &cfg[offset], PANEL_DEV_MAX);
    offset += PANEL_DEV_MAX + 1;

    // key_reserve
    memcpy(out_scene_id.key_reserve, &cfg[offset], PANEL_DEV_MAX);
}

// 构造面板发送数据帧
QByteArray AppProtocolSimState::BilidPanelSendFrame(const panel_frame_t &panel_frame)
{
    QByteArray buffer;

    buffer.append(reinterpret_cast<const char*>(&panel_frame.panel_tx_head), sizeof(panel_frame.panel_tx_head));
    buffer.append(reinterpret_cast<const char*>(&panel_frame.panel_tx_type), sizeof(panel_frame.panel_tx_type));
    buffer.append(reinterpret_cast<const char*>(&panel_frame.panel_tx_length), sizeof(panel_frame.panel_tx_length));

    buffer.append(reinterpret_cast<const char*>(&panel_frame.panel_info), sizeof(panel_frame.panel_info));

    uint8_t crc = app_panel_frame_crc((uint8_t *)&panel_frame.panel_info, static_cast<uint8_t>(sizeof(panel_frame.panel_info)));
    buffer.append(reinterpret_cast<const char*>(&crc), sizeof(crc));

    buffer.append(reinterpret_cast<const char*>(&panel_frame.panel_tx_tail_1), sizeof(panel_frame.panel_tx_tail_1));
    buffer.append(reinterpret_cast<const char*>(&panel_frame.panel_tx_tail_2), sizeof(panel_frame.panel_tx_tail_2));

    return buffer;
}

// 构造面板接收数据帧
const QByteArray AppProtocolSimState::BilidPanelRecvFrame()
{
    panel_tx_buf_t my_panel_tx_buf = {};
    my_panel_tx_buf.fh_1       = PANEL_FRAME_TX_HEAD_1;
    my_panel_tx_buf.fh_2       = PANEL_FRAME_TX_HEAD_2;
    my_panel_tx_buf.type       = PANEL_FRAME_TX_TYPE;
    my_panel_tx_buf.length     = sizeof(my_panel_full_status);
    my_panel_tx_buf.full_frame = my_panel_full_status;
    my_panel_tx_buf.crc        = app_panel_frame_crc((uint8_t *)my_panel_full_status.sub_frame, sizeof(my_panel_full_status.sub_frame));
    my_panel_tx_buf.ft_1       = 0x0D;
    my_panel_tx_buf.ft_2       = 0x0A;
    return QByteArray(reinterpret_cast<const char*>(&my_panel_tx_buf), sizeof(my_panel_tx_buf));
}

const QByteArray AppProtocolSimState::BuildExtendRecvFrame()
{
    extend_tx_buf_t my_extend_tx_buf;
    memset(&my_extend_tx_buf, 0, sizeof(my_extend_tx_buf));

    my_extend_tx_buf.fh   = EXTEND_FRAME_TX_HEAD;
    my_extend_tx_buf.type = EXTEND_FRAME_TX_TYPE;

    memcpy(my_extend_tx_buf.relay_sel_1, my_extend_all_status.relay_sel_1, sizeof(my_extend_all_status.relay_sel_1));   // 0~6路继电器
    memcpy(my_extend_tx_buf.tg_value, my_extend_all_status.tg_value, sizeof(my_extend_tx_buf.tg_value));                // 0~4路可控硅调光

    my_extend_tx_buf.crc_1 = app_panel_frame_sum(reinterpret_cast<uint8_t*>(&my_extend_tx_buf), 12);

    memcpy(my_extend_tx_buf.led_sel_1, my_extend_all_status.led_sel_1, sizeof(my_extend_tx_buf.led_sel_1)); // 0~4路 LED
    my_extend_tx_buf.reserve = 0x00;
    my_extend_tx_buf.crc_2   = app_panel_frame_crc(my_extend_tx_buf.led_sel_1, sizeof(my_extend_tx_buf.led_sel_1));

    memcpy(my_extend_tx_buf.led_sel_2, my_extend_all_status.led_sel_2, sizeof(my_extend_all_status.led_sel_2)); // 5~16路 LED
    my_extend_tx_buf.crc_3 = app_panel_frame_crc(my_extend_tx_buf.led_sel_2, sizeof(my_extend_tx_buf.led_sel_2) - 1);

    memcpy(my_extend_tx_buf.led_sel_3, my_extend_all_status.led_sel_3, sizeof(my_extend_tx_buf.led_sel_3));       // 17 ~24路 LED
    memcpy(my_extend_tx_buf.air_dev, my_extend_all_status.air_dev, sizeof(my_extend_tx_buf.air_dev));             // 空调模块
    memcpy(my_extend_tx_buf.relay_sel_2, my_extend_all_status.relay_sel_2, sizeof(my_extend_tx_buf.relay_sel_2)); // 7~9路继电器
    memcpy(my_extend_tx_buf.led_sel_4, my_extend_all_status.led_sel_4, sizeof(my_extend_tx_buf.led_sel_4));       // 25~32路 LED
    return QByteArray(reinterpret_cast<const char*>(&my_extend_tx_buf), sizeof(my_extend_tx_buf));
}



