#ifndef MODEL_PANEL_1KEY_H
#define MODEL_PANEL_1KEY_H

#include <QWidget>
#include <QMouseEvent>
#include <QInputDialog>
#include <QPushButton>
#include <QtDebug>
#include <QMenu>
#include <QAction>
#include "app/common_types.h"
#include "app/app_protocol_set_config.h"

namespace Ui {
class ModelPanel1Key;
}

class ModelPanel1Key : public QWidget
{
    Q_OBJECT

public:
    explicit ModelPanel1Key(QWidget *parent = nullptr);
    ~ModelPanel1Key();
    void SetPanelAddr(const uint8_t addr);
    void SetKeyNames(const QStringList &names);
    void SetPanelState(const QByteArray &data);
    void updateSceneList(const QVector<scene_save_t>& scenes) { m_sceneList = scenes; };

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void requestDelete(int id);
    void keyNameChanged(uint8_t panelId, int keyIndex, const QString& newName);
    void requestBindScene(uint8_t panel_addr, int key_num, uint8_t scene_id, bool state);
    void sendSimState(const panel_frame_t panel_data);

private slots:
    void on_key_1_clicked();

private:
    void bulid_panel_frame(const uint8_t key_num);
    Ui::ModelPanel1Key *ui;
    QList<QPushButton*> m_buttons;
    QVector<scene_save_t> m_sceneList;

    uint8_t m_addr    = 0;    // 该面板的地址
    uint8_t m_key_num = 6;    // 该面板拥有的按键个数
    uint8_t m_status  = 0x3F; // 该面板各个按键的状态 00111111 (0:开启,1:关闭)
};

#endif // MODEL_PANEL_1KEY_H
