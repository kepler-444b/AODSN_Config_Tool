#ifndef APPPROTOCOLSETNET_H
#define APPPROTOCOLSETNET_H

#include <QObject>
#include <qdebug.h>
#include "app/app_serial.h"

#define  FRAME_GET_INFO 0x01  // 获取设备信息
#define  FRAME_SET_INFO 0x02  // 设置设备信息

typedef struct wiz_NetInfo_t
{
    uint8_t mac[6];
    uint8_t ip[4];
    uint8_t sn[4];
    uint8_t gw[4];
    uint8_t dns[4];
    uint8_t dhcp;
    uint8_t reserve[5]; // 手动补齐
} wiz_NetInfo;

typedef struct
{
    wiz_NetInfo net;
    char devices[32];
    char key[128];
    char ver[16];
} dev_packet_t;


class AppProtocolSetNet : public QObject
{
    Q_OBJECT

public:
    explicit AppProtocolSetNet(QObject *parent, AppSerial* serialWidget);
    void RecvDataParse(const QByteArray &data);
    bool GetInfoData(void);
    bool SetInfoData(const dev_packet_t &info);

    QByteArray PackData(const uint8_t cmdType, const QByteArray &payload);

signals:
    void sigUpdate(const dev_packet_t &info);

private:

    AppSerial* m_serialWidget = nullptr; // 保存串口实例
    dev_packet_t m_dev_packet;
};


#endif // APPPROTOCOLSETNET_H
