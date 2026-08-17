#include "app_serial.h"
#include "ui_app_serial.h"

AppSerial::AppSerial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppSerial)
{
    ui->setupUi(this);
    m_frameTimer = new QTimer(this);
    m_frameTimer->setSingleShot(true);
    connect(m_frameTimer, &QTimer::timeout,  this,  &AppSerial::OnFrameTimeout);

    ui->baudrate->addItem("9600");
    ui->baudrate->addItem("115200");
    ui->baudrate->setCurrentText("115200");

    RefreshPorts();
    LoadSettings();
}

AppSerial::~AppSerial()
{
    SaveSettings();
    if (m_serial.isOpen())
        m_serial.close();
    delete ui;
}

// 发送数据
bool AppSerial::SerialSendData(const QByteArray &data)
{
    if (!m_serial.isOpen()) // 检查串口是否已经打开
    {
        QMessageBox::warning(nullptr, "错误", "串口未打开");
        return false;
    }

    qint64 len = m_serial.write(data);

    if (len == -1)
    {
        return false;
    }

    emit sigSendData(data);
    return true;
}

bool AppSerial::SerialIsOpen() const{
    return m_serial.isOpen();
}

// 检查波特率
bool AppSerial::SerialCheackBaudRate(int baudRate) const {
    if(baudRate != m_baudRate)
    {
        QMessageBox::warning(nullptr, "波特率错误", QString("预期波特率为:%1,请检查波特率与端口是否正确").arg(baudRate));
        return false;
    }
    return true;
}

// 接收数据
void AppSerial::SerialRecv()
{
    QByteArray data = m_serial.readAll();
    if (data.isEmpty())
        return;

    m_frameTimer->start(20);

    m_recvRawBuffer.append(data);
    m_recvBuffer.append(data);
    ParseBuffer();
}

// 超时发给调试窗口
void AppSerial::OnFrameTimeout()
{
    if (m_recvRawBuffer.isEmpty())
        return;

    emit sigRecvRawData(m_recvRawBuffer);

    m_recvRawBuffer.clear();
}

// 解析数据
void AppSerial::ParseBuffer()
{
    while (true) {
        int headIndex = -1;
        bool isPanelFrame = false; // 是否为面板发送的数据,其帧头为 0xAA

        for (int i = 0; i < m_recvBuffer.size() - 1; ++i) { // 查找帧头
            if ((uint8_t)m_recvBuffer[i] == FRAME_RX_FH_1 && (uint8_t)m_recvBuffer[i + 1] == FRAME_RX_FH_2) {
                headIndex = i;
                isPanelFrame = false;
                break;
            }
            if ((uint8_t)m_recvBuffer[i] == 0xAA)
            {
                headIndex = i;
                isPanelFrame = true;
                break;
            }
        }
        if (headIndex == -1) { // 没有找到帧头清除缓存(避免异常数据导致无限增长)
            if (m_recvBuffer.size() > 1024) {
                qDebug() << "Buffer too large without header,clear";
                m_recvBuffer.clear();
            }
            return; // 结束当前解析,等待更多数据
        }

        if (headIndex > 0) { //  删除帧头之前的数据(无效垃圾数据)
            qDebug() << "Removed" << headIndex << "garbage bytes before header";
            m_recvBuffer.remove(0, headIndex);
        }

        int tailIndex = -1; // 查找帧尾 0x0D 0x0A(需要从帧头后面查找,至少4字节:帧头2 + 帧尾2)
        for (int i = 2; i < m_recvBuffer.size() - 1; ++i) {
            if ((uint8_t)m_recvBuffer[i] == FRAME_TAIL_1 && (uint8_t)m_recvBuffer[i + 1] == FRAME_TAIL_2) {
                tailIndex = i;
                break;
            }
        }

        if (tailIndex == -1) { // 找到了头部,但没找到帧尾,说明半包,等待更多数据
            qDebug() << "Waiting for frame tail (0D 0A), buffer size:" << m_recvBuffer.size();
            return;
        }

        // 提取完整帧(从帧头到帧尾,+2 包含两个帧尾字节)
        QByteArray frame = m_recvBuffer.left(tailIndex + 2);

        // 验证帧最小长度(至少 FE BB xx xx 0D 0A = 6字节)
        uint8_t minLength = isPanelFrame? 12 : 6; // 验证最小长度,默认协议 6 字节, 面板发送的数据 12 字节

        if (frame.size() < minLength) {
            qDebug() << "Frame too short:" << frame.size() << "bytes, skip";
            m_recvBuffer.remove(0, frame.size());
            continue;
        }

        // 验证帧尾正确性(双重保险)
        if ((uint8_t)frame[frame.size() - 2] != FRAME_TAIL_1 || (uint8_t)frame[frame.size() - 1] != FRAME_TAIL_2) {
            qDebug() << "Frame tail mismatch, skip";
            m_recvBuffer.remove(0, frame.size());
            continue;
        }

        // 处理完整帧
        if (isPanelFrame) {
            emit sigRecvPanelData(frame); // 发送面板数据信号
        } else {
            emit sigRecvData(frame);  // 发送其他数据信号
            qDebug() << "[sigRecvData] Frame Length:" << frame.size();
        }
        // 从缓冲区中移除已经成功解析的帧数据
        m_recvBuffer.remove(0, frame.size());
    }
}

// 刷新串口
void AppSerial::RefreshPorts()
{
    ui->com->clear();

    const auto ports = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &info : ports)
    {
        // 创建一个临时的串口对象来测试它是否被占用
        QSerialPort testPort(info);

        // 尝试以读写模式打开串口
        if (testPort.open(QIODevice::ReadWrite))
        {
            // 如果成功打开,说明串口真正可用,加入下拉菜单
            ui->com->addItem(info.portName());
            // 测试完毕后记得关闭它,否则后面你的程序自己也用不了
            testPort.close();
        }
        else
        {
            // 如果打开失败,说明串口可能被其他程序占用了,或者权限不足
            qDebug() << "串口" << info.portName() << "正忙或无法打开,已跳过";
        }
    }

    if (ui->com->count() > 0)
    {
        ui->com->setCurrentIndex(0);
        m_portName = ui->com->currentText();
        qDebug() << "默认选择串口：" << m_portName;
    }
    else
    {
        m_portName.clear();
        qDebug() << "没有检测到任何当前闲置的可打开串口";
    }
}

// 波特率改变
void AppSerial::on_baudrate_currentIndexChanged(const QString &arg1)
{
    bool ok = false;
    int baud = arg1.toInt(&ok);
    if (!ok) return;
    m_baudRate = baud;
}

// 串口选择
void AppSerial::on_com_currentIndexChanged(const QString &arg1)
{
    m_portName = arg1;
    qDebug() << "当前选择串口：" << m_portName;
}

void AppSerial::on_refresh_com_clicked()
{
    RefreshPorts();
}

// 打开串口
void AppSerial::on_switch_com_clicked()
{
    if (!m_isOpen)
    {
        m_baudRate = ui->baudrate->currentText().toInt(); // 从ui界面取到波特率
        m_serial.setPortName(m_portName);
        m_serial.setBaudRate(m_baudRate);
        m_serial.setDataBits(QSerialPort::Data8);
        m_serial.setParity(QSerialPort::NoParity);
        m_serial.setStopBits(QSerialPort::OneStop);
        m_serial.setFlowControl(QSerialPort::NoFlowControl);
        qDebug() << "串口已打开：" << "端口=" << m_portName << "波特率=" << m_baudRate;

        if (!m_serial.open(QIODevice::ReadWrite))
        {
            QString err = m_serial.errorString();
            QMessageBox::warning(this, "错误\n",  err);
            return;
        }

        m_isOpen = true;
        ui->switch_com->setText("关闭");
        SetControlsEnabled(false); // 锁定控件
        connect(&m_serial, &QSerialPort::readyRead, this, &AppSerial::SerialRecv, Qt::UniqueConnection);
    }
    else
    {
        m_serial.close();
        m_isOpen = false;
        disconnect(&m_serial, &QSerialPort::readyRead, this, &AppSerial::SerialRecv);
        ui->switch_com->setText("打开");

        SetControlsEnabled(true); // 解锁控件
    }
}

void AppSerial::SaveSettings()
{
    QSettings settings("MyCompany", "MySerialApp");

    settings.setValue("portName", m_portName);
    settings.setValue("baudRate", m_baudRate);
    settings.setValue("autoFrame", m_autoFrame);
    settings.setValue("timeout", m_timeout);
}

void AppSerial::LoadSettings()
{
    QSettings settings("MyCompany", "MySerialApp");
    m_portName = settings.value("portName", m_portName).toString();
    m_timeout = settings.value("timeout", m_timeout).toInt();
    m_baudRate = settings.value("baudRate", m_baudRate).toInt();
    m_autoFrame = settings.value("autoFrame", m_autoFrame).toBool();

    if (ui->com->findText(m_portName) >= 0) // 恢复串口
        ui->com->setCurrentText(m_portName);
    else if (ui->com->count() > 0)
        ui->com->setCurrentIndex(0);

    if (ui->baudrate->findText(QString::number(m_baudRate)) >= 0) // 恢复波特率
        ui->baudrate->setCurrentText(QString::number(m_baudRate));
}

void AppSerial::SetControlsEnabled(bool enabled)
{
    ui->com->setEnabled(enabled);
    ui->baudrate->setEnabled(enabled);
    ui->refresh_com->setEnabled(enabled);
}

