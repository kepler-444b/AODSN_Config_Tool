#ifndef APP_PROTOCOL_H
#define APP_PROTOCOL_H

#include <QObject>
#include <QByteArray>
#include <QDebug>

#include "app/app_serial.h"

#define SET_ADDR_SINGLE          0x02 // 单发地址
#define SET_ADDR_BATCH           0x03 // 群发地址
#define GET_DEV_INFO             0x05 // 获取设备信息
#define SET_DEV_INFO             0x06 // 设置设备信息

class AppProtocolSetAddr : public QObject
{
    Q_OBJECT

public:
    explicit AppProtocolSetAddr(QObject *parent, AppSerial* serialWidget);

    // 接收原始数据
    void RecvDataParse(const QByteArray &data);
    void AddrSet(uint8_t addr); // 面板设备设置地址
    void AddrSendAll();         // 面板设备地址群发

    void TriacDeathValue(uint8_t value, uint8_t addr); // 4路可控硅调节死区值
    void TriacLumValue(uint8_t value,uint8_t addr);    // 4路可控硅调节亮度值
    void TriacSetInfo(uint8_t addr, uint8_t fade_time, uint8_t death_value);

    void AutoEnableDebug(bool enable, uint8_t addr);   // 雷达感应调光主机进入调试模式
    void AutoDeathValue(uint8_t value, uint8_t addr);  // 雷达感应调光主机调节死区值
    void AutoLumValue(uint8_t value, uint8_t addr);    // 雷达感应调光主机调节亮度值
    void AutoNoOneValue(uint8_t value, uint8_t addr);  // 雷达感应调光主机调节无人亮度

    void SetInfo(uint8_t dev_type, uint8_t set_type, uint8_t addr, const QByteArray &value);
    void SetInfo(uint8_t dev_type, uint8_t set_type, uint8_t addr, const uint8_t value);

    void MmwRadarSetInfo(uint8_t value, uint8_t addr); // 毫米波雷达设置地址

    void GetInfo(uint8_t dev_type, uint8_t addr);

    QByteArray BuildFrameAddr(uint8_t addr, uint8_t cmd_type);  // 面板设备构造数据帧
    QByteArray BuildFrame(const QByteArray &data);              // 通用数据帧构建

signals:
    void sigDevInfo(const QByteArray data);

private:
    bool SendDataBaudRateCheck(const QByteArray &frame, qint32 baudRate = 9600);
    QByteArray BuildDevInfoData(uint8_t dev_type, uint8_t set_type, uint8_t addr, const QByteArray &value);

    int m_panelAddr = 0;
    AppSerial* m_serialWidget = nullptr; // 保存串口实例
};

#endif // APP_PROTOCOL_H
