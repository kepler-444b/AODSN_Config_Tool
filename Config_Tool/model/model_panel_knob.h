#ifndef MODEL_PANEL_KNOB_H
#define MODEL_PANEL_KNOB_H

#include <QWidget>
#include <QMouseEvent>
#include <QInputDialog>
#include <QPushButton>
#include <QtDebug>
#include <QMenu>
#include <QAction>
#include "app/common_types.h"
#include "app/app_protocol_set_config.h"

namespace Ui
{
    class ModelPanelKnob;
}

class ModelPanelKnob : public QWidget
{
    Q_OBJECT

public:
    explicit ModelPanelKnob(QWidget *parent = nullptr);
    ~ModelPanelKnob();

    void SetPanelAddr(const uint8_t addr);
    void SetKeyNames(const QStringList &names);
    void SetPanelState(const QByteArray &data);
    void updateSceneList(const QVector<scene_save_t> &scenes)
    { m_sceneList = scenes; };
    void updateLedExList(const QVector<uint8_t> &list)
    { m_ledIdList = list; };
    void updateLedSelect(const QVector<bind_save_knob_t> &list)
    { m_ledSelect = list; };

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void requestDelete(int id);                                                 // 删除产品
    void keyNameChanged(uint8_t panelId, int keyIndex, const QString &newName); // 按键改名
    void requestBindScene(uint8_t panel_addr, int key_num, uint8_t scene_id, bool state);
    void requestBindKnobScene(uint8_t panelAddr, int openId, int closeId, uint64_t data, bool update); // bool update 用于区分是否需要跟新led数据
    void sendSimState(const panel_frame_t panel_frame);

private slots:
    uint8_t frame_crc(uint8_t *rxbuf, uint8_t len);
    void on_key_1_clicked();
    void on_key_2_clicked();
    void on_key_3_clicked();
    void on_key_4_clicked();

    void on_SliderLum_valueChanged(int value);
    void on_SliderCct_valueChanged(int value);

    void onFrameRightClicked(const QPoint &pos);
    void showLedSelectDialog();

private:
    void build_panel_frame(const uint8_t key_num);
    void build_panel_knob(const uint8_t type);

    Ui::ModelPanelKnob *ui;
    QList<QPushButton *> m_buttons;    // 存储4个按钮
    QVector<scene_save_t> m_sceneList; // 获取的场景列表
    QVector<uint8_t> m_ledIdList;      // 获取的led扩展列表

    QVector<bind_save_knob_t> m_ledSelect; // 获取的led勾选状态

    uint8_t m_addr    = 0;    // 该面板的地址
    uint8_t m_key_num = 4;    // 该面板拥有的按键个数
    uint8_t m_status  = 0x3F; // 该面板各个按键的状态 00111111 (0:开启,1:关闭)

    uint64_t m_led_select = {0}; // 用于保存旋钮所要控制的led位
    uint8_t m_lum         = 0;
    uint8_t m_cct         = 50;

    QTimer *m_lumTimer;
    QTimer *m_cctTimer;
};

#endif // MODEL_PANEL_KNOB_H
