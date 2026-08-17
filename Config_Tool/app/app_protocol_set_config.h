#ifndef APPPROTOCOLSETCONFIG_H
#define APPPROTOCOLSETCONFIG_H

#include <QObject>
#include <QVector>
#include <QtDebug>
#include <QEventLoop>

#include <QProgressDialog>
#include <QApplication>
#include <QTimer>
#include <QMessageBox>

#include "app_sel_set_scene.h"
#include "app/app_serial.h"

#define FRAME_SET_CFG   0x03  // 上位机发送服务类数据
#define FRAME_GET_TIMER 0x04  // 上位机发送获取定时任务数据
#define FRAME_SET_TIMER 0x05  // 上位机发送设置定时任务数据
#define FRAME_CAL_TIMR  0x06  // 上位机发送校准时间

#define TIMER_TASK_MAX  10    // 定时任务最多10条

// 定时任务数据
typedef struct
{
    uint8_t id;
    uint8_t scene_id;
    uint8_t enable;
    uint8_t hour;
    uint8_t min;
    uint8_t reserve;

} timer_task_t;


// 场景数据
typedef struct
{
    QString scene_name;
    QByteArray scene_data;
    uint8_t scene_id;
} scene_save_t;

// 面板状态
typedef struct
{
    uint8_t scene_id;           // 场景id
    QString scene_name;         // 场景别名

    uint8_t panel_addr;         // 面板地址
    uint8_t panel_type;         // 面板类型
    uint8_t panel_key_num;      // 按键数量
    QString panel_name[6];      // 按键别名
    QVector<bool> key_enable;   // 按键勾选状态
    QVector<bool> key_state;    // 对应状态勾选状态
} panel_save_t;

// led扩展状态
typedef struct
{
    uint8_t scene_id;              // 场景id
    QString scene_name;            // 场景别名

    uint8_t led_addr;              // 扩展地址
    QVector<bool> led_enable;      // 通道是否勾选
    QVector<int>  led_value;       // 输入的亮度值 (0-100)
} led_save_t;

// 继电器扩展状态
typedef struct
{
    uint8_t scene_id;
    QString scene_name;
    uint8_t relay_addr;

    QVector<bool> relay_enable;
    QVector<bool> relay_state;
} relay_save_t;

typedef struct
{
    QVector<scene_save_t> scene;
    QVector<panel_save_t> panel;
    QVector<led_save_t>   led_ex;
    QVector<relay_save_t> relay_ex;
} config_data_t;

typedef struct
{
    QString scene_name;
    QByteArray bind_data; // addr, key_num, status, scene_id, reserve, reserve
} bind_save_t;

typedef struct
{
    QVector<bind_save_t> bind_data;
} bind_data_t;

class AppProtocolSetConfig : public QObject
{
    Q_OBJECT

public:
    explicit AppProtocolSetConfig(QObject *parent, AppSerial* serialWidget);

public slots:

    // 接收串口数据
    void recv_serial_data(const QByteArray &data);

    // 接收场景数据
    void recv_scene_data(const QVector<panel_data_t>& panels, const QVector<led_data_t>& leds, const QVector<relay_data_t>& relays, uint8_t scene_id, QString name);
    // 接收绑定数据
    void recv_bind_data(uint8_t panelAddr, int keyIndex, uint8_t sceneId, bool isOpen);

    // 构造场景数据
    void bulidSceneData(const QVector<panel_data_t>& panels, const QVector<led_data_t>& leds, const QVector<relay_data_t>& relays, uint8_t scene_id, QString name);

    // 构造绑定数据
    void buildBindData(uint8_t addr, uint8_t key_num, uint8_t state, uint8_t scene_id, QString scene_name);

    void deleteScene(uint8_t scene_id);        // 删除场景
    void deleteBind(const bind_save_t &bind);  // 删除绑定

    config_data_t getAllConfigData() const;
    bind_data_t getAllBindData() const;
    config_data_t getSceneConfigDataById(uint8_t scene_id) const;

    void setAllConfigData(const config_data_t& data);
    void setAllBindData(const bind_data_t& binds);

    void sendSceneData(void); // 下发场景数据
    void sendBindData(void);  // 下发绑定信息

    void sendClearSceneData(void); // 下发删除场景信息
    void sendClearBindData(void);  // 下发删除绑定信息

    void sendGetTimerTask(void);
    void sendSetTimerTask(const QByteArray &data);

    void sendCalTime(const uint64_t &time);      // 校准时间

    bool configIsChanged();
    void clearConfigChanged();

    QByteArray packFrame(const QByteArray &payload, const uint8_t cmdType); // 打包函数

signals:
    void recv_scene_data_result(bool success);                // 返回添加场景的结果
    void sceneListChanged(const QVector<scene_save_t>& data); // 场景列表发生变化
    void bindListChanged(const QVector<bind_save_t>& data);   // 绑定列表发生变化

    void sigUpdate(const timer_task_t* tasks);

private:

    AppSerial* m_serialWidget = nullptr; // 保存串口实例
    bool m_isChanged = false;

    QVector<scene_save_t> m_scene_save;  // 保存场景数据
    QVector<bind_save_t> m_bind_save;    // 保存绑定数据

    QVector<panel_save_t> m_panel_save;  // 保存面板结构
    QVector<led_save_t> m_led_save;      // 保存led扩展结构
    QVector<relay_save_t> m_relay_save;  // 保存relay扩展结构

    timer_task_t m_timer_task[TIMER_TASK_MAX]; // 保存定时任务数据
};


#endif // APPPROTOCOLSETCONFIG_H
