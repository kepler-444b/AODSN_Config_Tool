#ifndef APP_SEL_TIMER_H
#define APP_SEL_TIMER_H

#include <QDialog>

#include "app_protocol_set_config.h"
namespace Ui {
class DialogTimer;
}

class DialogTimer : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTimer(QWidget *parent = nullptr);
    ~DialogTimer();

    void setDisplay(const timer_task_t* tasks);

signals:
    void sigGetTimerTask();  // 发送获取定时器任务的信号
    void sigSetTimerTask(const QByteArray &data);

private slots:
    void on_get_timer_task_clicked();
    void on_set_timer_task_clicked();

private:

    Ui::DialogTimer *ui;
    timer_task_t m_tasks[TIMER_TASK_MAX];
};

#endif // APP_SEL_TIMER_H
