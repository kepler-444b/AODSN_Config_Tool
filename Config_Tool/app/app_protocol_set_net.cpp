#include "app_protocol_set_net.h"

AppProtocolSetNet::AppProtocolSetNet(QObject *parent, AppSerial* serialWidget)
    : QObject(parent)
{
    m_serialWidget = serialWidget;
}

void AppProtocolSetNet::RecvDataParse(const QByteArray &data)
{
    uint8_t len  = (uint8_t)data[2];
    uint8_t type = (uint8_t)data[3];
    if(type != FRAME_GET_INFO) {
        return;
    }

    if(len != sizeof(m_dev_packet)) {
        qDebug() << "recv nw data length err!";
        return;
    }

    memcpy(&m_dev_packet, data.constData() + 4, len);
    emit sigUpdate(m_dev_packet);
}

// 获取设备信息
bool AppProtocolSetNet::GetInfoData(void)
{
    QByteArray payload;
    QByteArray packet = PackData(FRAME_GET_INFO, payload);

    if (m_serialWidget) {
        if (!m_serialWidget->SerialCheackBaudRate(115200))
        {
            return false;
        }
        return m_serialWidget->SerialSendData(packet);
    }
    return false;
}

// 下发设备信息
bool AppProtocolSetNet::SetInfoData(const dev_packet_t &info)
{
    QByteArray payload(reinterpret_cast<const char*>(&info), sizeof(info));
    QByteArray packet = PackData(FRAME_SET_INFO, payload);

    if (m_serialWidget) {
        if (!m_serialWidget->SerialCheackBaudRate(115200))
        {
            return false;
        }
        return m_serialWidget->SerialSendData(packet);
    }
    return false;
}

// 打包函数
QByteArray AppProtocolSetNet::PackData(const uint8_t cmdType, const QByteArray &payload)
{
    QByteArray packet;
    packet.reserve(2 + 1 + 1 + payload.size() + 2); // 帧头 + 长度 + 类型 + 数据 + 帧尾

    packet.append(static_cast<char>(FRAME_TX_FH_1));
    packet.append(static_cast<char>(FRAME_TX_FH_2));

    uint8_t length = static_cast<uint8_t>(payload.size());
    packet.append(static_cast<char>(length)); // 添加长度
    packet.append(static_cast<char>(cmdType));// 添加类型
    packet.append(payload); // 添加数据

    packet.append(static_cast<char>(FRAME_TAIL_1));
    packet.append(static_cast<char>(FRAME_TAIL_2));

    return packet;
}
