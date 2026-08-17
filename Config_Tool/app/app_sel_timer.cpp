#include "app_sel_timer.h"
#include "ui_app_sel_timer.h"

DialogTimer::DialogTimer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTimer)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

DialogTimer::~DialogTimer()
{
    delete ui;
}

// 获取任务
void DialogTimer::on_get_timer_task_clicked()
{
    emit sigGetTimerTask();
}

// 设置任务
void DialogTimer::on_set_timer_task_clicked()
{
    QByteArray payload(sizeof(timer_task_t) * TIMER_TASK_MAX, 0);

    timer_task_t* tasks = reinterpret_cast<timer_task_t*>(payload.data());

    for (int i = 0; i < TIMER_TASK_MAX; i++) {

        QString sceneIdName = QString("scene_id_%1").arg(i + 1);
        QString hourName    = QString("hour_%1").arg(i + 1);
        QString minName     = QString("min_%1").arg(i + 1);
        QString checkName   = QString("checkBox_%1").arg(i + 1);

        auto sceneIdEdit = findChild<QLineEdit*>(sceneIdName);
        auto hourEdit    = findChild<QLineEdit*>(hourName);
        auto minEdit     = findChild<QLineEdit*>(minName);
        auto checkBox    = findChild<QCheckBox*>(checkName);

        tasks[i].id       = i;
        tasks[i].scene_id = sceneIdEdit ? sceneIdEdit->text().toUInt() : 0xFF;
        tasks[i].hour     = hourEdit ? hourEdit->text().toUInt() : 0xFF;
        tasks[i].min      = minEdit ? minEdit->text().toUInt() : 0xFF;
        tasks[i].enable   = (checkBox && checkBox->isChecked()) ? 1 : 0;
        tasks[i].reserve  = 0;
    }

    for (int i = 0; i < TIMER_TASK_MAX; i++) {
        if (tasks[i].enable == 0) { // 如果当前任务没有使能,则跳过
            continue;
        }

        // 拿当前任务与后面的任务进行对比
        for (int j = i + 1; j < TIMER_TASK_MAX; j++) {
            // 如果后面的任务也使能了
            if (tasks[j].enable == 1) {
                // 判断小时和分钟是否完全相同
                if (tasks[i].hour == tasks[j].hour && tasks[i].min == tasks[j].min) {
                    // 弹出警告提示框
                    QMessageBox::warning(
                                this,
                                tr("错误"),
                                QString(tr("任务 %1 与 任务 %2 的时间冲突(%3:%4),请重新设置!"))
                                .arg(i + 1)
                                .arg(j + 1)
                                .arg(tasks[i].hour, 2, 10, QChar('0'))
                                .arg(tasks[i].min, 2, 10, QChar('0'))
                                );
                    return; // 发现冲突,直接终止函数,不发送信号
                }
            }
        }
    }

    emit sigSetTimerTask(payload);
}

void DialogTimer::setDisplay(const timer_task_t* tasks)
{
    for(int i = 0; i < TIMER_TASK_MAX; i++) {

        QString sceneIdName = QString("scene_id_%1").arg(i + 1);
        QString hourName = QString("hour_%1").arg(i + 1);
        QString minName = QString("min_%1").arg(i + 1);
        QString checkBoxName = QString("checkBox_%1").arg(i + 1);

        // 查找对应的控件
        QLineEdit* sceneIdEdit = findChild<QLineEdit*>(sceneIdName);
        QLineEdit* hourEdit = findChild<QLineEdit*>(hourName);
        QLineEdit* minEdit = findChild<QLineEdit*>(minName);
        QCheckBox* enableCheckBox = findChild<QCheckBox*>(checkBoxName);

        // 处理Flash中的0xFF值,转换为0（所有字段都是uint8_t）
        uint8_t scene_id = (tasks[i].scene_id == 0xFF) ? 0 : tasks[i].scene_id;
        uint8_t hour = (tasks[i].hour == 0xFF) ? 0 : tasks[i].hour;
        uint8_t min = (tasks[i].min == 0xFF) ? 0 : tasks[i].min;
        uint8_t enable = (tasks[i].enable == 0xFF) ? 0 : tasks[i].enable;

        // 设置数值到控件
        if (sceneIdEdit) {
            if (scene_id <= 127) {
                sceneIdEdit->setText(QString::number(scene_id));
            } else {
                sceneIdEdit->clear();
            }
        }

        if (hourEdit) {
            if (hour <= 23) {
                hourEdit->setText(QString::number(hour).rightJustified(2, '0'));
            } else {
                hourEdit->clear();
            }
        }

        if (minEdit) {
            if (min <= 59) {
                minEdit->setText(QString::number(min).rightJustified(2, '0'));
            } else {
                minEdit->clear();
            }
        }

        if (enableCheckBox) {
            enableCheckBox->setChecked(enable != 0);
        }
    }
}

