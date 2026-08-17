#ifndef APP_SEL_SET_SCENE_H
#define APP_SEL_SET_SCENE_H

#include <QtDebug>
#include <QDialog>
#include <QGroupBox>
#include <QCheckBox>
#include <QLineEdit>
#include "app/app_sel_panel.h"
#include "app/app_sel_extend.h"

typedef struct
{
    uint8_t scene_id;
    uint8_t relay_state[9];
    uint8_t led_state[64];
    uint8_t panel_status[96];
} scene_info_t;

typedef struct
{
    uint8_t addr;
    QVector<bool> led_enabled;     // 通道是否勾选
    QVector<int>  led_value;       // 输入的亮度值 (0-100)
} led_data_t;

typedef struct
{
    uint8_t addr;
    QVector<bool> relay_enabled;
    QVector<bool> relay_state;

} relay_data_t;

typedef struct
{
    uint8_t addr;
    uint8_t type;
    uint8_t key_num;
    QString key_name[6];        // 按键别名
    QVector<bool> key_enable;   // 按键勾选状态
    QVector<bool> key_state;    // 对应状态勾选状态
} panel_data_t;


namespace Ui {
class DialogSetScene;
}

class DialogSetScene : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSetScene(const QVector<PanelInfo_t>& panels, const QVector<ExtendInfo_t>& extends, const uint8_t scene_id,  const QString scene_name, QWidget *parent = nullptr);
    ~DialogSetScene();

    void editScene(int id);

public slots:
    void on_send_config_result(bool success); // 用于接收 set_config 构造场景的结果

signals:
    // 发送配置给 set_config 构造场景
    void send_config(const QVector<panel_data_t>& panels, const QVector<led_data_t>& leds, const QVector<relay_data_t>& relays,uint8_t scene_id, QString name);

private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_pushButton_clicked();

private:
    void populatePanels();
    void populateLeds();
    void populateRelays();

    uint8_t getAddrFromGroup(QGroupBox* group);
    void parseGroupBoxInfo(QGroupBox* group, uint8_t &addr, uint8_t &key_num, uint8_t &type);

private:
    Ui::DialogSetScene *ui;
    bool m_sendSuccess = false;
    QVector<PanelInfo_t> m_panels;
    QVector<ExtendInfo_t> m_extends;
    scene_info_t m_scene_info;

};

#endif // APP_SEL_SET_SCENE_H
