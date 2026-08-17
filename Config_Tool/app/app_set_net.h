#ifndef APP_SET_NET_H
#define APP_SET_NET_H

#include <QWidget>
#include <QtGlobal>
#include <QMessageBox>
#include "app/app_serial.h"
#include "app/app_protocol_set_net.h"

namespace Ui {
class AppSetNet;
}

class AppSetNet : public QWidget
{
    Q_OBJECT

public:
    explicit AppSetNet(QWidget *parent, AppSerial* serialWidget);
    ~AppSetNet();

    void setDisplay(const dev_packet_t &info);

private slots:

    void on_set_info_clicked();
    void on_get_info_clicked();


private:
    Ui::AppSetNet *ui;
    AppProtocolSetNet *m_protocol_set_net = nullptr;
    AppSerial* m_serialWidget = nullptr; // 保存串口实例

};

#endif // APP_SET_NET_H
