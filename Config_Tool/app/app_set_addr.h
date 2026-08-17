#ifndef APP_SET_ADDR_H
#define APP_SET_ADDR_H

#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include "app/app_serial.h"
#include "app/app_protocol_set_addr.h"


enum SendType
{
    TRIAC_LUM = 0,
    TRIAC_DEATH,

    AUTO_DRATH,
    AUTO_NO_ONE,
    AUTO_SOME_ONE,
    AUTO_ACTIVE,
};

namespace Ui {
class AppSetAddr;
}

class AppSetAddr : public QWidget
{
    Q_OBJECT

public:
    explicit AppSetAddr(QWidget *parent, AppSerial* serialWidget);
    ~AppSetAddr();

    void recvDevInfo(const QByteArray data);


private slots:
    void onSendTimeout();
    void on_spinBox_valueChanged(int addr); // 灯控面板地址更新
    void on_pushButton_clicked();           // 灯控面板地址群发
    void on_dev_info_clicked();             // 灯控面板获取设备信息

    void on_triac_get_cfg_clicked(); // 4路可控硅获取设备信息
    void on_triac_set_cfg_clicked(); // 4路可控硅设置设备信息

    void on_triac_grad_valueChanged(int fade_time);       // 4路可控硅设置渐变时间
    void on_QSlider_triac_death_valueChanged(int value);  // 4路可控硅调节死区
    void on_QSlider_triac_lum_valueChanged(int value);    // 4路可控硅调节亮度

    void on_auto_get_cfg_clicked(); // 雷达感应调光主机获取设备信息
    void on_auto_set_cfg_clicked(); // 雷达感应调光主机设置设备信息

    void on_auto_grad_valueChanged(int fade_time);         // 雷达感应调光主机设置渐变时间
    void on_QSlider_auto_death_valueChanged(int value);    // 雷达感应调光主机调节死区
    void on_QSlider_auto_no_one_valueChanged(int value);   // 雷达感应调光主机无人亮度
    void on_QSlider_auto_some_one_valueChanged(int value); // 雷达感应调光主机有人亮度
    void on_QSlider_auto_active_valueChanged(int value);   // 雷达感应调光主机活跃亮度

    void on_auto_debug_clicked(); // 雷达感应调光主机进入调试模式
    void auto_crtl_enable(bool enable);
    void initRadarCheckBox();
    void onRadarCheckChanged(bool checked);



    void on_get_radar_info_clicked();
    void on_set_radar_info_clicked();

    void on_device_sel_activated(int index);

private:
    Ui::AppSetAddr *ui;
    AppSerial* m_serialWidget = nullptr; // 保存串口实例
    AppProtocolSetAddr * m_protocol_set_addr = nullptr;

    int m_TriacDeathValue = 0; // 4路可控硅调节死区数值
    int m_TriacLumValue = 0;   // 4路可控硅调节亮度数值

    int m_AutoDeathValue = 0;  // 雷达感应调光主机死区值
    int m_AutoNoOneValue = 0;  // 雷达感应调光主机无人亮度
    int m_AutoSomeOneValue = 0;// 雷达感应调光主机有人亮度
    int m_AutoActiveValue = 0; // 雷达感应调光主机活跃亮度

    uint8_t m_radar_map[4][8]      = {};           // 雷达感应调光主机映射表
    QCheckBox *m_radar_check[4][8] = {};      // 雷达感应调光主机指向复选框的指针
    bool m_data_echo = false; // 数据回显标志位

    QTimer m_sendTimer;
    uint8_t m_sendType = 0;

};

#endif // APP_SET_ADDR_H
