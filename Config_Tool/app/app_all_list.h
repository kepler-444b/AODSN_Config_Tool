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

signals:
    void requestDeleteScene(int id);
    void requestEditScene(int id);

    void requsetDeleteBind(const bind_save_t &bind);


    void requestSendSceneData();  // 请求发送场景数据
    void requestSendBindData();   // 请求发送绑定数据

    void requestClearSceneData(); // 删除设备场景
    void requestClearBindData();  // 删除设备绑定

private slots:


    void on_send_scene_clicked();
    void on_send_bind_clicked();

    void on_del_scene_clicked();
    void on_del_bind_clicked();

private:
    Ui::AppAllList *ui;
    QVector<scene_save_t> m_sceneInfo;
    QVector<bind_save_t>m_bindInfo;
};

#endif // APP_SCENE_LIST_H
