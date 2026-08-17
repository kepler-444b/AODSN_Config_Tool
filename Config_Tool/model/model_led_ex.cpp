#include "model_led_ex.h"
#include "ui_model_led_ex.h"

ModelLedEx::ModelLedEx(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelLedEx)
{
    ui->setupUi(this);
    this->installEventFilter(this);
}

ModelLedEx::~ModelLedEx()
{
    delete ui;
}

void ModelLedEx::SetExtendAddr(const uint8_t addr, const ExtendType type)
{
    ui->addr->setText(QString("地址:%1").arg(addr));
    m_addr = addr;
    m_type = type;
}

// 设置该led扩展状态
void ModelLedEx::SetExtendSatae(const QByteArray &data)
{
    const int byteIndexes[] = {13, 19, 23, 27, 32, 36, 46, 50};  // 映射协议的字节下标, 分别对应协议中控制led的字节(每4个一组)

    uint8_t all_leds[4][8] = {}; // 用于接收所有led扩展的数据

    for (int addr = 0; addr < 4; addr++) { // 填充所有 led 扩展数据
        memcpy(&all_leds[addr][0], data.constData() + byteIndexes[addr * 2], 4);     // 前4个通道
        memcpy(&all_leds[addr][4], data.constData() + byteIndexes[addr * 2 + 1], 4); // 后4个通道
    }

    memcpy(m_led_status, &all_leds[m_addr][0], 8);

    for (int i = 0; i < 8; ++i)
    {
        QString labelName = QString("led_%1_lum").arg(i + 1);
        QLabel* lumLabel = this->findChild<QLabel*>(labelName);

        if (lumLabel)
        {
            uint8_t lumValue = m_led_status[i];
            lumLabel->setText(QString::number(lumValue));

            bool isOpen = (lumValue > 0);

            if (isOpen) {
                lumLabel->setStyleSheet("color: orange; font-weight: bold;");
            } else {
                lumLabel->setStyleSheet("");
            }
        }
    }
}

bool ModelLedEx::eventFilter(QObject *obj, QEvent *event)
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

                // QAction *selected = menu.exec(e->globalPos()); // 弹出菜单
                QAction *selected = menu.exec(e->globalPosition().toPoint()); // 弹出菜单
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

