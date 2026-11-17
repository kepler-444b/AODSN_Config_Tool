#ifndef APP_SCENE_LIST_H
#define APP_SCENE_LIST_H

#include <QWidget>
#include <QtDebug>
#include <QLabel>
#include <QTextEdit>
#include <QFormLayout>
#include <QScrollArea>
#include <QMenu>
#include <QAction>
#include "app_protocol_set_config.h"

namespace Ui {
class AppAllList;
}

class AppAllList : public QWidget
{
    Q_OBJECT

public:
    explicit AppAllList(QWidget *parent = nullptr);
    ~AppAllList();

    void setSceneData(const QVector<scene_save_t> &data);
    void setBindData(const QVector<bind_save_t> &data);
    void setBindKnobData(const QVector<bind_save_knob_t> &data);

signals:
    void requestDeleteScene(int id);
    void requestEditScene(int id);

    void requsetDeleteBind(const bind_save_t &bind);
    void requsetDeleteBindKone(const bind_save_knob_t &bind);


    void requestSendSceneData();      // 请求发送扩展场景数据
    void requestSendPanelSceneData(); // 请求发送面板场景数据

    void requestSendBindData();      // 请求发送按键绑定数据
    void requestSendBindKnobData();  // 请求发送旋钮绑定数据

    void requestClearSceneData();     // 删除设备场景
    void requestClearBindData();      // 删除设备按键绑定
    void requestClearBindKnobData();  // 删除设备旋钮绑定

private slots:


    void on_send_scene_clicked();
    void on_send_bind_clicked();

    void on_del_scene_clicked();
    void on_del_bind_clicked();
    void on_del_bind_knob_clicked();

    void on_send_bind_knob_clicked();

    void on_send_panel_scene_clicked();

private:
    Ui::AppAllList *ui;
    QVector<scene_save_t> m_sceneInfo;
    QVector<bind_save_t>m_bindInfo;
    QVector<bind_save_knob_t>m_bindKnobInfo;
};

#endif // APP_SCENE_LIST_H
