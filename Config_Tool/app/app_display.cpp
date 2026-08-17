#include "app_display.h"
#include "ui_app_display.h"

AppDisplay::AppDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppDisplay)
{
    ui->setupUi(this);

}

AppDisplay::~AppDisplay()
{
    delete ui;
}

void AppDisplay::DisplayRecv(const QByteArray &data)
{
    QString text = data.toHex(' ').toUpper();
    ui->display->append("RX:" + text);
}

void AppDisplay::DisplaySend(const QByteArray &data)
{
    QString text = data.toHex(' ').toUpper();
    ui->display->append("TX:" + text);
}

// 发送按钮
void AppDisplay::on_send_clicked()
{
    QString text = ui->send_input->toPlainText();

    if (text.isEmpty())
        return;

    QByteArray data = text.toUtf8();
    emit sigDisplaySendData(data);
}

// 清空按钮
void AppDisplay::on_clear_clicked()
{
    ui->display->clear();
}
