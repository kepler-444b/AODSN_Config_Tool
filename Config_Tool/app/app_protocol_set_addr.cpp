#include "app_protocol_set_addr.h"

AppProtocolSetAddr::AppProtocolSetAddr(QObject *parent, AppSerial* serialWidget)
    : QObject(parent), m_serialWidget(serialWidget)
{
}

// 检查波特率并发送数据帧
bool AppProtocolSetAddr::SendDataBaudRateCheck(const QByteArray &frame, qint32 baudRate)
{
    if (!m_serialWidget || !m_serialWidget->SerialCheackBaudRate(baudRate))
    {
        return false;
    }
    m_serialWidget->SerialSendData(frame);
    return true;
}

// 通用设备设置数据包构建器
QByteArray AppProtocolSetAddr::BuildDevInfoData(uint8_t dev_type, uint8_t set_type, uint8_t addr, const QByteArray &value)
{
    QByteArray data;

    // 命令类型
    data.append(static_cast<char>(0x06));

    // 设备类型
    data.append(static_cast<char>(dev_type));

    // 保留字节
    data.append(static_cast<char>(0x00));

    // 设备地址
    data.append(static_cast<char>(addr));

    // 设置类型
    if (set_type != 0x00)
    {
        data.append(static_cast<char>(set_type));
    }

    // 附加数据
    data.append(value);

    return data;
}

// 接收原始数据
void AppProtocolSetAddr::RecvDataParse(const QByteArray &data)
{
    if (data.size() < 3)
        return;

    if (static_cast<quint8>(data[0]) != 0xFE || static_cast<quint8>(data[1]) != 0xBB)
        return;

    uint8_t cmd_type = static_cast<quint8>(data[3]);
    if (cmd_type == 0x02) // 面板设备请求地址
    {
        QByteArray frame = BuildFrameAddr(m_panelAddr, SET_ADDR_SINGLE); // 单发地址
        SendDataBaudRateCheck(frame);
    }
    else if (cmd_type == 0x05) // 设备信息
    {
        emit sigDevInfo(data);
    }
}

void AppProtocolSetAddr::AddrSet(uint8_t addr)
{
    m_panelAddr = addr;
}

// 面板设备群发地址
void AppProtocolSetAddr::AddrSendAll()
{
    QByteArray frame = BuildFrameAddr(m_panelAddr, SET_ADDR_BATCH); // 群发地址
    SendDataBaudRateCheck(frame);
}

// 毫米波雷达 - 设置信息
void AppProtocolSetAddr::MmwRadarSetInfo(uint8_t value, uint8_t addr)
{
    // QByteArray data = BuildDevInfoData(0x03, 0x03, value, addr, 0x00);
    // SendDataBaudRateCheck(BuildFrame(data));
}

// 设置设备信息
void AppProtocolSetAddr::SetInfo(uint8_t dev_type, uint8_t set_type, uint8_t addr, const QByteArray &value)
{
    QByteArray data = BuildDevInfoData( dev_type,  set_type,   addr,   value);

    SendDataBaudRateCheck(BuildFrame(data));
}
void AppProtocolSetAddr::SetInfo(uint8_t dev_type, uint8_t set_type,  uint8_t addr, uint8_t value)
{
    QByteArray data;
    data.append(static_cast<char>(value));
    SetInfo(dev_type, set_type, addr, data);
}

// 获取设备信息
void AppProtocolSetAddr::GetInfo(uint8_t dev_type, uint8_t addr)
{
    QByteArray data;

    data.append(static_cast<char>(0x05));     // 命令类型
    data.append(static_cast<char>(dev_type)); // 设备类型
    data.append(static_cast<char>(0x00));     // reserve
    data.append(static_cast<char>(addr));     // 设备地址

    SendDataBaudRateCheck(BuildFrame(data));
}

// 面板设备设置地址帧构建
QByteArray AppProtocolSetAddr::BuildFrameAddr(uint8_t addr, uint8_t cmd_type)
{
    QByteArray frame;
    frame.resize(9);

    frame[0] = static_cast<char>(FRAME_TX_FH_1);
    frame[1] = static_cast<char>(FRAME_TX_FH_2);
    frame[2] = static_cast<char>(0x03); // 有效数据固定4个字节
    frame[3] = static_cast<char>(cmd_type);

    frame[4] = static_cast<char>(0x1B);
    frame[5] = static_cast<char>(0x2C);
    frame[6] = static_cast<char>(addr);

    frame[7] = static_cast<char>(FRAME_TAIL_1);
    frame[8] = static_cast<char>(FRAME_TAIL_2);

    return frame;
}

// 通用数据帧构建
QByteArray AppProtocolSetAddr::BuildFrame(const QByteArray &data)
{
    QByteArray frame;

    if (data.isEmpty())
    {
        return frame;
    }

    uint8_t len = static_cast<uint8_t>(data.size());

    frame.append(static_cast<char>(FRAME_TX_FH_1));
    frame.append(static_cast<char>(FRAME_TX_FH_2));

    frame.append(static_cast<char>(len));  // 长度
    frame.append(data);                    // 有效数据

    frame.append(static_cast<char>(FRAME_TAIL_1));
    frame.append(static_cast<char>(FRAME_TAIL_2));

    return frame;
}