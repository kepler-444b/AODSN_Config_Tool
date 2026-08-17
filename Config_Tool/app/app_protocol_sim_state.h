#ifndef APPPROTOCOLSIMSTATE_H
#define APPPROTOCOLSIMSTATE_H
#include <QObject>
#include <QtDebug>
#include "app/app_serial.h"
#include "app/common_types.h"
#include "app/app_protocol_set_config.h"

typedef enum {
    SIM_KEY  = 0x01, // 按键数据
    SIM_KNOB = 0x02, // 旋钮数据
} panel_type;

class AppProtocolSimState :public QObject
{
    Q_OBJECT
public:
    AppProtocolSimState(QObject *parent, AppProtocolSetConfig * config, AppSerial* serialWidget);

    void RecvSimPanelData(const panel_frame_t panel_frame);
    void RecvPanelFrame(const QByteArray &data);

    void ExeSceneById(const uint8_t scene_id);
    void UnpackSceneData(const QByteArray &data, scene_id_t &out_scene_id); // 解包场景数据

    QByteArray BilidPanelSendFrame(const panel_frame_t &panel_frame); // 构造面板发送数据帧
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
};

#endif // APPPROTOCOLSIMSTATE_H
