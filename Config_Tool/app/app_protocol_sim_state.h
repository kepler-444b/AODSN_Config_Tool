#ifndef APPPROTOCOLSIMSTATE_H
#define APPPROTOCOLSIMSTATE_H
#include <QObject>
#include <QtDebug>
#include "app/app_serial.h"
#include "app/common_types.h"
#include "app/app_protocol_set_config.h"

typedef enum {
    SIM_KEY  = 0x01, // 按键数据
    SIM_KNOB_LUM = 0x02, // 旋钮亮度数据
    SIM_KNOB_CCT = 0x03, // 旋钮色温数据
} panel_type;

class AppProtocolSimState :public QObject
{
    Q_OBJECT
public:
    AppProtocolSimState(QObject *parent, AppProtocolSetConfig * config, AppSerial* serialWidget);

    void RecvSimPanelData(const panel_frame_t panel_frame);
    void RecvSimLedData(const uint8_t led_num, const uint8_t lum, const uint8_t cct);
    void RecvSimRelayData(const uint8_t num, const bool status);
    void RecvPanelFrame(const QByteArray &data);

    void ExeSceneById(const uint8_t scene_id);
    void FindPanenDataById(const QByteArray &data, scene_id_panel_t &out_scene_id);
    bool FindLedDataFromScene(const QByteArray &scene_data, QByteArray &out_led_data);
    bool FindRelayDataFromScene(const QByteArray &scene_data, QByteArray &relay_data);

    const QByteArray BilidPanelRecvFrame();  // 构造面板接收数据帧
    const QByteArray BuildExtendRecvFrame(); // 构造扩展接收数据帧
signals:
    void SendPanelData(const QByteArray &data);
    void SendExtendData(const QByteArray &data);

private:
    AppProtocolSetConfig* m_config = nullptr; // 用来保存传进来的指针
    AppSerial* m_serialWidget      = nullptr; // 保存串口实例

    panel_full_status_t my_panel_full_status = {0};
    extend_all_status_t my_extend_all_status = {0};

    // extend_all_status_t my_extend_all_status_sim = {0}; // 用于控制实际的继电器扩展,检查回路使用

    uint8_t m_knob_last_lum[32] = {0}; // 用于保存旋钮面板上次的亮度值
};

#endif // APPPROTOCOLSIMSTATE_H
