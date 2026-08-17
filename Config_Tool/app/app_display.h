#ifndef APP_DISPLAY_H
#define APP_DISPLAY_H

#include <QWidget>

namespace Ui {
class AppDisplay;
}

class AppDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit AppDisplay(QWidget *parent = nullptr);
    ~AppDisplay();

    void DisplayRecv(const QByteArray &data);
    void DisplaySend(const QByteArray &data);

signals:
    void sigDisplaySendData(const QByteArray &data);

private slots:
    void on_send_clicked();



    void on_clear_clicked();

private:
    Ui::AppDisplay *ui;
};

#endif // APP_DISPLAY_H
