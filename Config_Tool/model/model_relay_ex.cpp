#include "model_relay_ex.h"
#include "ui_model_relay_ex.h"

ModelRelayEx::ModelRelayEx(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelRelayEx)
{
    ui->setupUi(this);
    this->installEventFilter(this);
}

ModelRelayEx::~ModelRelayEx()
{
    delete ui;
}

void ModelRelayEx::SetExtendAddr(const uint8_t addr, const ExtendType type)
{
    ui->addr->setText(QString("继电器扩展地址:%1").arg(addr));
    m_addr = addr;
    m_type = type;
}

// 接收设置继电器扩展状态数据帧
void ModelRelayEx::SetExtendSatae(const QByteArray &data)
{
    const QByteArray marker = "RELAY:";
    int index = data.indexOf(marker);
    if (index == -1) return;

    const uint8_t *relay_bytes = reinterpret_cast<const uint8_t*>(data.constData() + index + marker.size());

    // 没台设备占用10个bit
    int start_bit = m_addr * 10;
    int byte_offset = start_bit / 8;
    int bit_offset  = start_bit % 8;

    // 将数据拼成 16 位整数,安全跨越字节边界
    uint16_t raw_16 = 0;
    if (byte_offset + 1 < 8) {
        raw_16 = (relay_bytes[byte_offset + 1] << 8) | relay_bytes[byte_offset];
    } else {
        raw_16 = relay_bytes[byte_offset];
    }

    // 移位对齐,0x03FF 代表低 10 位全 1 提取所需要的10个bit
    uint16_t my_relay = (raw_16 >> bit_offset) & 0x03FF;

    for (int i = 1; i <= 10; ++i) {
        QPushButton *relayButton = this->findChild<QPushButton *>(
            QString("relay%1").arg(i));

        if (relayButton) {
            bool isOpen = (my_relay >> (i - 1)) & 0x01;

            setRelayState(relayButton, isOpen);
        }
    }
}

// 设置按钮状态
void ModelRelayEx::setRelayState(QPushButton *button, int state)
{
    if (!button) {
        return;
    }
    bool isOpen;

    if (state == -1) {  // 点击按钮:根据当前状态切换
        isOpen = button->text() != "开";
    } else {    // 接收设备状态: 直接设置
        isOpen = state;
    }

    button->setText(isOpen ? "开" : "关");
    button->setStyleSheet(isOpen ? "color: orange; font-weight: bold;" : "");
}

bool ModelRelayEx::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QWidget* w = qobject_cast<QWidget*>(obj);
        if (w == this)  // 如果点击的是这个 widget 本身
        {
            QMouseEvent *e = static_cast<QMouseEvent*>(event);
            if (e->button() == Qt::RightButton)
            {
                QMenu menu(this);   // 创建右键菜单
                QAction *deleteAction = menu.addAction("删除");

                QAction *selected = menu.exec(e->globalPosition().toPoint());

                if (selected == deleteAction)
                {
                    emit requestDelete(m_addr, m_type);  // 发出删除信号
                }
                return true;  // 拦截事件
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}


void ModelRelayEx::on_relay1_clicked()
{
    setRelayState(ui->relay1);
    sendSimRelayState(m_addr * 10 + 0, ui->relay1->text() == "开");
}
void ModelRelayEx::on_relay2_clicked()
{
    setRelayState(ui->relay2);
    sendSimRelayState(m_addr * 10 + 1, ui->relay2->text() == "开");
}
void ModelRelayEx::on_relay3_clicked()
{
    setRelayState(ui->relay3);
    sendSimRelayState(m_addr * 10 + 2, ui->relay3->text() == "开");
}
void ModelRelayEx::on_relay4_clicked()
{
    setRelayState(ui->relay4);
    sendSimRelayState(m_addr * 10 + 3, ui->relay4->text() == "开");
}
void ModelRelayEx::on_relay5_clicked()
{
    setRelayState(ui->relay5);
    sendSimRelayState(m_addr * 10 + 4, ui->relay5->text() == "开");
}
void ModelRelayEx::on_relay6_clicked()
{
    setRelayState(ui->relay6);
    sendSimRelayState(m_addr * 10 + 5, ui->relay6->text() == "开");
}
void ModelRelayEx::on_relay7_clicked()
{
    setRelayState(ui->relay7);
    sendSimRelayState(m_addr * 10 + 6, ui->relay7->text() == "开");
}
void ModelRelayEx::on_relay8_clicked()
{
    setRelayState(ui->relay8);
    sendSimRelayState(m_addr * 10 + 7, ui->relay8->text() == "开");
}
void ModelRelayEx::on_relay9_clicked()
{
    setRelayState(ui->relay9);
    sendSimRelayState(m_addr * 10 + 8, ui->relay9->text() == "开");
}
void ModelRelayEx::on_relay10_clicked()
{
    setRelayState(ui->relay10);
    sendSimRelayState(m_addr * 10 + 9, ui->relay10->text() == "开");
}


