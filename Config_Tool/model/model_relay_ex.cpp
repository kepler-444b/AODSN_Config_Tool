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
    ui->addr->setText(QString("地址:%1").arg(addr));
    m_addr = addr;
    m_type = type;
}

void ModelRelayEx::SetExtendSatae(const QByteArray &data)
{
    qDebug() << "Received Extend Data (Hex):" << data.toHex(' ').toUpper();
    const int byteIndexes[] = {2, 3, 4, 5, 6, 7, 43, 44}; // 映射你的协议字节下标, 分别对应协议中控制继电器的字节
    uint64_t all_relays = 0;

    for (int i = 0; i < 8; ++i) { // 拼接成一个连续的64位
        all_relays |= (static_cast<uint64_t>(static_cast<uint8_t>(data[byteIndexes[i]])) << (i * 8));
    }

    // 根据扩展地址平移 15 位并切片
    uint16_t current_module = (all_relays >> (m_addr * 15)) & 0x7FFF;


    for (int i = 1; i <= 15; ++i) {
        QString labelName = QString("relay_%1_state").arg(i);
        QLabel *relayLabel = this->findChild<QLabel *>(labelName);

        if (relayLabel) {
            bool isOpen = (current_module >> (i - 1)) & 0x01;

            if (isOpen) {
                relayLabel->setText("开");
                relayLabel->setStyleSheet("color: orange; font-weight: bold;");
            } else {
                relayLabel->setText("关");
                relayLabel->setStyleSheet("");
            }
        }
    }
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



