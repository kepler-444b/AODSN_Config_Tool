#ifndef APP_SERIAL_H
#define APP_SERIAL_H

#include <QWidget>
#include <QTime>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

// 上位机发送数据帧头
#define FRAME_TX_FH_1 0xFF
#define FRAME_TX_FH_2 0xAA

#define FRAME_RX_FH_1 0xFE
#define FRAME_RX_FH_2 0xBB

#define FRAME_TAIL_1 0x0D
#define FRAME_TAIL_2 0x0A



namespace Ui {
class AppSerial;
}

class AppSerial : public QWidget
{
    Q_OBJECT

public:
    explicit AppSerial(QWidget *parent = nullptr);
    ~AppSerial();

    bool SerialSendData(const QByteArray &data);
    bool SerialIsOpen() const;
    bool SerialCheackBaudRate(int baudRate) const;

signals:
    void sigRecvRawData(const QByteArray &data);
    void sigRecvData(const QByteArray &data);
    void sigRecvPanelData(const QByteArray &data);
    void sigSendData(const QByteArray &data);

private slots:

    void on_baudrate_currentIndexChanged(const QString &arg1);
    void on_com_currentIndexChanged(const QString &arg1);
    void on_refresh_com_clicked();
    void on_switch_com_clicked();

    void SerialRecv();
    void OnFrameTimeout();

private:
    void ParseBuffer();
    void RefreshPorts();
    void LoadSettings();
    void SaveSettings();
    void SetControlsEnabled(bool enabled);

private:
    int m_baudRate = 115200;
    int m_timeout = 20;
    bool m_autoFrame = true;
    bool m_isOpen = false;

    Ui::AppSerial *ui = nullptr;
    QSerialPort m_serial;
    QTimer *m_frameTimer = nullptr;
    QString m_portName;

    QByteArray m_recvRawBuffer;
    QByteArray m_recvBuffer;
};

#endif // APP_SERIAL_H
