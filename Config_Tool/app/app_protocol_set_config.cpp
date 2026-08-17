#include "app_protocol_set_config.h"

static uint8_t getKeyBitMask(int keyIndex, int keyCount)
{
    if (keyCount == 1) // 一键面板 -> 0~5 位
    {
        return 0x3F;
    }
    else if (keyCount == 3) // 三键面板特殊映射
    {
        switch (keyIndex)
        {
        case 0:
            return (1u << 0) | (1u << 1); // 0键 -> 0,1
        case 1:
            return (1u << 4) | (1u << 5); // 1键 -> 4,5
        case 2:
            return (1u << 2) | (1u << 3); // 2键 -> 2,3
        default:
            return 0;
        }
    }
    else if (keyCount == 2)
    {
        switch (keyIndex)
        {
        case 0:
            return (1u << 0) | (1u << 1);
        case 1:
            return (1u << 2) | (1u << 3);
        default:
            return 0;
        }
    }
    else // 普通按键面板
    {
        return (1u << keyIndex);
    }
}

AppProtocolSetConfig::AppProtocolSetConfig(QObject *parent, AppSerial *serialWidget)
    : QObject(parent)
{
    m_serialWidget = serialWidget;
}


bool AppProtocolSetConfig::configIsChanged()
{
    return m_isChanged;
}

void AppProtocolSetConfig::clearConfigChanged()
{
    m_isChanged = false;
}

// 接收串口数据
void AppProtocolSetConfig::recv_serial_data(const QByteArray &data)
{
    uint8_t len  = (uint8_t)data[2];
    uint8_t type = (uint8_t)data[3];

    if(type != FRAME_GET_TIMER) {
        return;
    }

    if(len != sizeof (timer_task_t) * 10) {
        qDebug() << "recv timer task data length err!";
        return;
    }

    const timer_task_t* tasks = reinterpret_cast<const timer_task_t*>(data.constData() + 4);
    emit sigUpdate(tasks);
}

// 根据设备状态组成场景数据
void AppProtocolSetConfig::recv_scene_data(const QVector<panel_data_t> &panels, const QVector<led_data_t> &leds, const QVector<relay_data_t> &relays, uint8_t scene_id, QString name)
{
    bool success = false;
    bool exists = std::any_of(m_scene_save.begin(), m_scene_save.end(), [scene_id](const scene_save_t &s)
    { return s.scene_id == scene_id; });

    if (exists)
    {
        // 弹出询问窗口，让用户选择是否覆盖替换
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr,
                                      "场景号重复",
                                      QString("场景号 %1 已经存在, 是否覆盖替换?").arg(scene_id),
                                      QMessageBox::Yes | QMessageBox::No,
                                      QMessageBox::No);

        if (reply == QMessageBox::Yes)  { // 用户选择替换:直接调用功能完善后的 deleteScene 把它全清掉
            deleteScene(scene_id);
        }
        else { // 用户选择不替换:直接退出
            success = false;
            emit recv_scene_data_result(success);
            return;
        }
    }

    for (const auto &p : panels)
    {
        panel_save_t savePanel;
        savePanel.scene_id = scene_id;
        savePanel.scene_name = name;

        savePanel.panel_addr = p.addr;
        savePanel.panel_type = p.type;
        savePanel.panel_key_num = p.key_num;
        savePanel.key_enable = p.key_enable;
        savePanel.key_state = p.key_state;

        for (int k = 0; k < 6; ++k)
        {
            if (!p.key_name[k].isEmpty())
            {
                savePanel.panel_name[k] = p.key_name[k];
                qDebug() << "  按键" << k << ":" << p.key_name[k];
            }
        }
        m_panel_save.append(savePanel);
    }

    for (const auto &p : leds)
    {
        led_save_t saveLed;
        saveLed.scene_id = scene_id;
        saveLed.scene_name = name;

        saveLed.led_addr = p.addr;
        saveLed.led_enable = p.led_enabled;
        saveLed.led_value = p.led_value;

        m_led_save.append(saveLed);
    }

    for (const auto &p : relays)
    {
        relay_save_t saveRelay;
        saveRelay.scene_id = scene_id;
        saveRelay.scene_name = name;

        saveRelay.relay_addr = p.addr;
        saveRelay.relay_enable = p.relay_enabled;
        saveRelay.relay_state = p.relay_state;
        m_relay_save.append(saveRelay);
    }

    bulidSceneData(panels, leds, relays, scene_id, name);
    success = true;
    m_isChanged = true; // 场景数据发生了变化
    emit recv_scene_data_result(success);
}

void AppProtocolSetConfig::recv_bind_data(uint8_t panelAddr, int keyIndex, uint8_t sceneId, bool isOpen)
{
    bool exists = std::any_of(m_bind_save.begin(), m_bind_save.end(),
                              [panelAddr, keyIndex, isOpen](const bind_save_t &b) {
        if (b.bind_data.size() >= 4) {
            uint8_t panel_addr = static_cast<uint8_t>(b.bind_data.at(0));
            uint8_t key_num    = static_cast<uint8_t>(b.bind_data.at(1));
            uint8_t key_state  = static_cast<uint8_t>(b.bind_data.at(2));

            return (panel_addr == panelAddr) &&
                    (key_num == keyIndex) &&
                    (key_state == isOpen);
        }
        return false;
    }
    );

    if (exists)
    {
        QMessageBox::warning(nullptr, "绑定重复", QString("该按键绑定已经存在, 请删除或选择其他场景!"));
        return;
    }

    // 找到场景的别名
    QString sceneName = "未知场景";
    for (const auto &scene : m_scene_save)
    {
        if (scene.scene_id == sceneId)
        {
            sceneName = scene.scene_name;
            break;
        }
    }
    m_isChanged = true;  // 绑定数据发生了变化
    buildBindData(panelAddr, keyIndex, isOpen, sceneId, sceneName);
}

// 构造场景数据
void AppProtocolSetConfig::bulidSceneData(const QVector<panel_data_t> &panels, const QVector<led_data_t> &leds, const QVector<relay_data_t> &relays, uint8_t scene_id, QString scene_name)
{
    QByteArray bytes;
    // 赋值场景ID
    bytes.append(static_cast<char>(scene_id));
    bytes.append(static_cast<char>(0xFF));

    // 构造继电器扩展字段
    QByteArray relayData(18, 0x00);

    for (const auto &r : relays)
    {
        if (r.relay_enabled.isEmpty() || r.relay_state.isEmpty())
            continue;

        int startRelay = r.addr * 15;
        int count = std::min({(int)r.relay_enabled.size(), (int)r.relay_state.size(), 72 - startRelay});

        for (int i = 0; i < count; ++i)
        {
            int relayIdx = startRelay + i;
            if (relayIdx >= 72)
                break;

            int bytePair = relayIdx / 8;
            int bitPos = relayIdx % 8;

            int ctrlPos = bytePair * 2;
            int statePos = bytePair * 2 + 1;

            if (r.relay_enabled[i])
            {
                relayData[ctrlPos] = static_cast<char>(static_cast<uint8_t>(relayData[ctrlPos]) | (1u << bitPos));
            }

            if (r.relay_state[i])
            {
                relayData[statePos] = static_cast<char>(static_cast<uint8_t>(relayData[statePos]) | (1u << bitPos));
            }
        }
    }

    qDebug() << "Relay bytes:" << relayData.toHex(' ').toUpper();
    bytes.append(relayData);
    bytes.append(static_cast<char>(0xFF));

    // 构造LED扩展字段
    QByteArray ledData(64, 0x00);
    for (const auto &l : leds)
    {
        if (l.led_enabled.isEmpty() || l.led_value.isEmpty())
            continue;

        int startLed = l.addr * 8;
        int count = qMin(l.led_enabled.size(), l.led_value.size());
        for (int ch = 0; ch < count; ++ch)
        {
            int ledIdx = startLed + ch;
            if (ledIdx >= 64)
                break;

            if (l.led_enabled[ch])
            {
                uint8_t value = l.led_value[ch] & 0x7F;            // 亮度 0~100
                ledData[ledIdx] = static_cast<char>(0x80 | value); // 最高位=1表示控制
            }
        }
    }
    bytes.append(ledData);
    bytes.append(static_cast<char>(0xFF));
    qDebug() << "Led 64 bytes:" << ledData.toHex(' ').toUpper();

    // 构造面板字段
    QVector<uint8_t> ctrl(32, 0x00);
    QVector<uint8_t> status(32, 0x00);
    QVector<uint8_t> reserve(32, 0x00);

    for (const auto &p : panels)
    {
        if (p.addr >= 32)
            continue; // 防止越界

        int keyCount = qMin(p.key_enable.size(), p.key_state.size());
        keyCount = qMin(keyCount, 6); // 最多支持6个按键

        for (int k = 0; k < keyCount; ++k)
        {
            uint8_t mask = getKeyBitMask(k, keyCount);

            if (p.key_enable[k])
                ctrl[p.addr] |= mask;

            if (p.key_state[k])
                status[p.addr] |= mask;
        }
    }

    for (int i = 0; i < 32; ++i) // 写入 Ctrl 32字节 + FF
        bytes.append(static_cast<char>(ctrl[i]));
    bytes.append(static_cast<char>(0xFF));
    for (int i = 0; i < 32; ++i) // 写入 Status 32字节 + FF
        bytes.append(static_cast<char>(status[i]));
    bytes.append(static_cast<char>(0xFF));
    for (int i = 0; i < 32; ++i) // 写入 Reserve 32字节 + FF
        bytes.append(static_cast<char>(reserve[i]));

    bytes.append(static_cast<char>(0xFF));
    scene_save_t scene;
    scene.scene_name = scene_name;
    scene.scene_data = bytes; // 如果 scene_data 是 QByteArray 类型
    scene.scene_id = scene_id;

    // 使用二分查找
    auto it = std::lower_bound(
                m_scene_save.begin(),
                m_scene_save.end(),
                scene,                                             // 要插入的 scene
                [](const scene_save_t &a, const scene_save_t &b) { // 比较规则,如何比较两个 scene_save_t 的大小,只是比较scene_id
        return a.scene_id < b.scene_id;                            // 返回 true 表示 a 应该排在 b 前面
    });

    // 插入场景数据
    m_scene_save.insert(it, scene);
    emit sceneListChanged(m_scene_save);
}

// 构造绑定数据
void AppProtocolSetConfig::buildBindData(uint8_t addr, uint8_t key_num, uint8_t state, uint8_t scene_id, QString scene_name)
{
    QByteArray bindData;
    bindData.resize(6); // 6 字节

    bindData[0] = static_cast<char>(addr);     // byte0: addr
    bindData[1] = static_cast<char>(key_num);  // byte1: key_num
    bindData[2] = static_cast<char>(state);    // byte2: status
    bindData[3] = static_cast<char>(scene_id); // byte3: scene_id
    bindData[4] = 0;                           // byte4: reserve
    bindData[5] = 0;                           // byte5: reserve

    bind_save_t save;
    save.scene_name = scene_name;
    save.bind_data = bindData;

    //    m_bind_save.append(save);
    //    emit bindListChanged(m_bind_save);

    auto it = std::lower_bound(
                m_bind_save.begin(),
                m_bind_save.end(),
                save,
                [](const bind_save_t &a, const bind_save_t &b) {
        // 从 bind_data 中提取出需要对比的字段 (注意：char 转换为 uint8_t 避免符号问题)

        uint8_t a_addr    = static_cast<uint8_t>(a.bind_data[0]);
        uint8_t b_addr    = static_cast<uint8_t>(b.bind_data[0]);
        uint8_t a_key_num = static_cast<uint8_t>(a.bind_data[1]);
        uint8_t b_key_num = static_cast<uint8_t>(b.bind_data[1]);
        uint8_t a_status  = static_cast<uint8_t>(a.bind_data[2]);
        uint8_t b_status  = static_cast<uint8_t>(b.bind_data[2]);

        if (a_addr != b_addr) {       // 面板地址由小到大
            return a_addr < b_addr;
        }
        if (a_key_num != b_key_num) { // 按键号由小到大
            return a_key_num < b_key_num;
        }
        return a_status > b_status;   // 按键状态 真在前,假在后
    }
    );

    m_bind_save.insert(it, save);

    emit bindListChanged(m_bind_save);
}

config_data_t AppProtocolSetConfig::getAllConfigData() const
{
    config_data_t data;
    data.scene = m_scene_save;
    data.panel = m_panel_save;
    data.led_ex = m_led_save;
    data.relay_ex = m_relay_save;
    return data;
}

config_data_t AppProtocolSetConfig::getSceneConfigDataById(uint8_t scene_id) const
{
    config_data_t singleData;

    // 捞出对应的场景原始字节数据 (通常只有1条,因为 ID 唯一)
    for (const auto &s : m_scene_save)
    {
        if (s.scene_id == scene_id)
        {
            singleData.scene.append(s);
            break; // 找到即可退出
        }
    }

    // 如果连核心场景数据都没找到,说明该场景不存在,直接返回空结构体
    if (singleData.scene.isEmpty())
    {
        qWarning() << "未找到场景 ID:" << scene_id << " 的配置信息";
        return singleData;
    }

    // 过滤出属于该场景的所有面板配置 (可能有多个面板)
    for (const auto &p : m_panel_save)
    {
        if (p.scene_id == scene_id)
        {
            singleData.panel.append(p);
        }
    }

    // 过滤出属于该场景的所有 LED 扩展配置
    for (const auto &l : m_led_save)
    {
        if (l.scene_id == scene_id)
        {
            singleData.led_ex.append(l);
        }
    }

    // 过滤出属于该场景的所有 继电器 扩展配置
    for (const auto &r : m_relay_save)
    {
        if (r.scene_id == scene_id)
        {
            singleData.relay_ex.append(r);
        }
    }
    return singleData;
}

bind_data_t AppProtocolSetConfig::getAllBindData() const
{
    bind_data_t data;
    data.bind_data = m_bind_save;
    return data;
}

void AppProtocolSetConfig::setAllConfigData(const config_data_t &data)
{
    // 先清空
    m_scene_save.clear();
    m_panel_save.clear();
    m_led_save.clear();
    m_relay_save.clear();
    // 再赋值
    m_scene_save = data.scene;
    m_panel_save = data.panel;
    m_led_save = data.led_ex;
    m_relay_save = data.relay_ex;
    // 通知 UI 更新界面上的场景列表
    emit sceneListChanged(m_scene_save);
}

void AppProtocolSetConfig::setAllBindData(const bind_data_t &binds)
{
    m_bind_save.clear();
    m_bind_save = binds.bind_data;

    emit bindListChanged(m_bind_save);
}

void AppProtocolSetConfig::deleteScene(uint8_t scene_id)
{
    // 删除场景数据
    auto sceneIt = std::find_if(m_scene_save.begin(), m_scene_save.end(),
                                [scene_id](const scene_save_t &s)
    { return s.scene_id == scene_id; });

    if (sceneIt != m_scene_save.end())
    {
        m_scene_save.erase(sceneIt);
    }

    // 删除对应面板数据
    m_panel_save.erase(std::remove_if(m_panel_save.begin(), m_panel_save.end(), [scene_id](const panel_save_t &p)
    { return p.scene_id == scene_id; }),
                       m_panel_save.end());

    // 删除对应LED扩展数据
    m_led_save.erase(std::remove_if(m_led_save.begin(), m_led_save.end(), [scene_id](const led_save_t &l)
    { return l.scene_id == scene_id; }),
                     m_led_save.end());

    m_relay_save.erase(std::remove_if(m_relay_save.begin(), m_relay_save.end(), [scene_id](const relay_save_t &r)
    { return r.scene_id == scene_id; }),
                       m_relay_save.end());

    // 通知 UI 刷新
    emit sceneListChanged(m_scene_save);
}

void AppProtocolSetConfig::deleteBind(const bind_save_t &bind)
{
    m_bind_save.erase(std::remove_if(m_bind_save.begin(), m_bind_save.end(), [&](const bind_save_t &item)
    {
        // 判定条件：二进制数据 bind_data 和 场景名称 scene_name 都要匹配
        return (item.bind_data == bind.bind_data && item.scene_name == bind.scene_name); }),
                      m_bind_save.end());
    emit bindListChanged(m_bind_save);

    qDebug() << "绑定项已删除，当前剩余数量:" << m_bind_save.size();
}

// 下发场景数据
void AppProtocolSetConfig::sendSceneData(void)
{
    if (m_scene_save.isEmpty())
    { // 没有场景数据可以下发
        return;
    }

    QProgressDialog progress("正在下发场景数据", "取消", 0, m_scene_save.size());

    progress.setWindowTitle("场景下发");
    progress.setWindowModality(Qt::ApplicationModal);
    progress.setWindowFlags(progress.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    progress.show();

    int current = 0;

    for (const auto &scene : m_scene_save)
    {
        if (progress.wasCanceled())
        {
            return;
        }

        QByteArray frame = packFrame(QByteArray("SetScene") + scene.scene_data, FRAME_SET_CFG);

        if (!m_serialWidget->SerialCheackBaudRate(115200))
        {
            return;
        }
        if (!m_serialWidget->SerialSendData(frame))
        {
            return;
        }

        current++;

        progress.setLabelText(QString("正在下发场景数据\n当前 %1 总共 %2").arg(current).arg(m_scene_save.size()));

        progress.setValue(current);

        QApplication::processEvents();

        QEventLoop loop;
        QTimer::singleShot(500, &loop, &QEventLoop::quit);
        loop.exec();
    }

    QMessageBox::information(nullptr, "完成", "场景下发完成");
}

// 下发绑定数据
void AppProtocolSetConfig::sendBindData(void)
{
    if (m_bind_save.isEmpty())
    {
        return;
    }

    QProgressDialog progress("正在下发绑定数据", "取消", 0, m_bind_save.size());
    progress.setWindowTitle("绑定下发");
    progress.setWindowModality(Qt::ApplicationModal);
    progress.setWindowFlags(progress.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    progress.show();

    int current = 0;

    for (const auto &bind : m_bind_save)
    {
        if (progress.wasCanceled())
        {
            return;
        }

        QByteArray frame = packFrame(QByteArray("BindScene") + bind.bind_data, FRAME_SET_CFG);

        if (!m_serialWidget->SerialCheackBaudRate(115200))
        {
            return;
        }
        if (!m_serialWidget->SerialSendData(frame))
        {
            return;
        }

        current++;
        progress.setLabelText(QString("正在下发绑定数据\n当前 %1 总共 %2").arg(current).arg(m_bind_save.size()));
        progress.setValue(current);
        QApplication::processEvents();

        QEventLoop loop;
        QTimer::singleShot(500, &loop, &QEventLoop::quit);
        loop.exec();
    }

    QMessageBox::information(nullptr, "完成", "绑定数据下发完成");
}

// 下发删除场景信息
void AppProtocolSetConfig::sendClearSceneData(void)
{
    QByteArray frame = packFrame("DelScene", FRAME_SET_CFG);
    if (!m_serialWidget->SerialCheackBaudRate(115200))
    {
        return;
    }
    m_serialWidget->SerialSendData(frame);
}

// 下发删除绑定信息
void AppProtocolSetConfig::sendClearBindData(void)
{
    QByteArray frame = packFrame("DelBind", FRAME_SET_CFG);
    if (!m_serialWidget->SerialCheackBaudRate(115200))
    {
        return;
    }
    m_serialWidget->SerialSendData(frame);

}

// 下发获取定时任务
void AppProtocolSetConfig::sendGetTimerTask(void)
{
    QByteArray frame = packFrame(QByteArray(), FRAME_GET_TIMER);
    if (!m_serialWidget->SerialCheackBaudRate(115200))
    {
        return;
    }
    m_serialWidget->SerialSendData(frame);
}

// 下发设置定时任务
void AppProtocolSetConfig::sendSetTimerTask(const QByteArray &data)
{
    QByteArray frame = packFrame(data, FRAME_SET_TIMER);
    if (!m_serialWidget->SerialCheackBaudRate(115200))
    {
        return;
    }
    m_serialWidget->SerialSendData(frame);
}

// 校准时间
void AppProtocolSetConfig::sendCalTime(const uint64_t &time)
{
    QByteArray time_data = QByteArray::number(time);
    QByteArray frame = packFrame(time_data, FRAME_CAL_TIMR);
    if (!m_serialWidget->SerialCheackBaudRate(115200))
    {
        return;
    }
    m_serialWidget->SerialSendData(frame);
}

QByteArray AppProtocolSetConfig::packFrame(const QByteArray &payload, const uint8_t cmdType)
{
    QByteArray frame;

    frame.reserve(2 + 1 + 1 + payload.size() + 2); // 帧头 + 长度 + 类型 + 数据 + 帧尾
    frame.append(static_cast<char>(FRAME_TX_FH_1));
    frame.append(static_cast<char>(FRAME_TX_FH_2));

    uint8_t length = static_cast<uint8_t>(payload.size());
    frame.append(static_cast<char>(length)); // 添加长度
    frame.append(static_cast<char>(cmdType));// 添加类型
    frame.append(payload);

    frame.append(static_cast<char>(FRAME_TAIL_1));
    frame.append(static_cast<char>(FRAME_TAIL_2));

    return frame;
}
