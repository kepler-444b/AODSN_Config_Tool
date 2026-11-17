#include "model_led_ex.h"
#include "ui_model_led_ex.h"
#include <qlabel.h>

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
    ui->addr->setText(QString("LED扩展地址:%1").arg(addr));
    m_addr = addr;
    m_type = type;
}

// 设置该led扩展状态
void ModelLedEx::SetExtendSatae(const QByteArray &data)
{
    const QByteArray marker = "LED:";
    int index = data.indexOf(marker);
    if (index == -1 || m_addr >= 8) return;

    // 找到 LED 的数据段
    const char *led_data = data.constData() + index + marker.size();

    // 找到该 LED 模块需要的数据段 (每个模块占 16 字节: 8 通道 * 2 字节)
    const uint8_t *my_led = reinterpret_cast<const uint8_t*>(led_data + (m_addr * 16));

    // 根据数据段更新 UI
    for (int i = 1; i <= 8; ++i) {
        uint8_t lumValue = my_led[(i - 1) * 2];     // 偶数字节为亮度
        uint8_t cctValue = my_led[(i - 1) * 2 + 1]; // 奇数字节为色温

        // 更新亮度输入框
        QLineEdit *lumEdit = this->findChild<QLineEdit *>(QString("lum_%1").arg(i));
        if (lumEdit) {
            lumEdit->setText(QString::number(lumValue));
        }

        // 更新色温输入框
        QLineEdit *cctEdit = this->findChild<QLineEdit *>(QString("cct_%1").arg(i));
        if (cctEdit) {
            cctEdit->setText(QString::number(cctValue));
        }

        // 更新按钮状态
        QPushButton *btn = this->findChild<QPushButton *>(QString("led_%1").arg(i));
        if (btn) {
            setLedState(btn, cctValue, lumValue, true);
        }
    }
}

void ModelLedEx::setLedState(QPushButton *button, uint8_t cct, uint8_t lum, int state)
{
    if (!button) {
        return;
    }

    QString indexStr = button->objectName().section('_', 1, 1);
    int index = indexStr.toInt() - 1;

    if (index < 0 || index >= 8) {
        return;
    }
    bool isOpen;
    if (state == -1) {  // 点击按钮:根据当前状态切换
        isOpen = button->text() != "开";
        lum = isOpen ? 100 : 0;
        cct = 50;
    } else {
        if (lum > 0) {
            isOpen = true;
        } else {
            isOpen = false;
        }
    }
    m_led_status[index].led = isOpen;
    m_led_status[index].lum = lum;
    m_led_status[index].cct = cct;

    QLineEdit *lumEdit = findChild<QLineEdit *>(QString("lum_%1").arg(index + 1));
    QLineEdit *cctEdit = findChild<QLineEdit *>(QString("cct_%1").arg(index + 1));

    if (lumEdit) {
        lumEdit->setText(QString::number(m_led_status[index].lum));
    }

    if (cctEdit) {
        cctEdit->setText(QString::number(m_led_status[index].cct));
    }

    button->setText(isOpen ? "开" : "关");
    button->setStyleSheet(isOpen ? "color: orange; font-weight: bold;" : "");
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

// 开关改变
void ModelLedEx::on_led_1_clicked()
{
    setLedState(ui->led_1, 0, 0);
    uint8_t num = m_addr * 8 + 0;
    sendSimLedState(num, m_led_status[0].lum, m_led_status[0].cct);
}
void ModelLedEx::on_led_2_clicked()
{
    setLedState(ui->led_2, 0, 0);
    uint8_t num = m_addr * 8 + 1;
    sendSimLedState(num, m_led_status[1].lum, m_led_status[1].cct);
}
void ModelLedEx::on_led_3_clicked()
{
    setLedState(ui->led_3, 0, 0);
    uint8_t num = m_addr * 8 + 2;
    sendSimLedState(num, m_led_status[2].lum, m_led_status[2].cct);
}
void ModelLedEx::on_led_4_clicked()
{
    setLedState(ui->led_4, 0, 0);
    uint8_t num = m_addr * 8 + 3;
    sendSimLedState(num, m_led_status[3].lum, m_led_status[3].cct);
}
void ModelLedEx::on_led_5_clicked()
{
    setLedState(ui->led_5, 0, 0);
    uint8_t num = m_addr * 8 + 4;
    sendSimLedState(num, m_led_status[4].lum, m_led_status[4].cct);
}
void ModelLedEx::on_led_6_clicked()
{
    setLedState(ui->led_6, 0, 0);
    uint8_t num = m_addr * 8 + 5;
    sendSimLedState(num, m_led_status[5].lum, m_led_status[5].cct);
}
void ModelLedEx::on_led_7_clicked()
{
    setLedState(ui->led_7, 0, 0);
    uint8_t num = m_addr * 8 + 6;
    sendSimLedState(num, m_led_status[6].lum, m_led_status[6].cct);
}
void ModelLedEx::on_led_8_clicked()
{
    setLedState(ui->led_8, 0, 0);
    uint8_t num = m_addr * 8 + 7;
    sendSimLedState(num, m_led_status[7].lum, m_led_status[7].cct);
}

// 亮度改变
void ModelLedEx::on_lum_1_editingFinished()
{
    uint8_t lum = ui->lum_1->text().toUInt();
    setLedState(ui->led_1, m_led_status[0].cct, lum, lum > 0);

    uint8_t num = m_addr * 8 + 0;
    sendSimLedState(num, m_led_status[0].lum, m_led_status[0].cct);

}
void ModelLedEx::on_lum_2_editingFinished()
{
    uint8_t lum = ui->lum_2->text().toUInt();
    setLedState(ui->led_2, m_led_status[1].cct, lum, lum > 0);

    uint8_t num = m_addr * 8 + 1;
    sendSimLedState(num, m_led_status[1].lum, m_led_status[1].cct);
}
void ModelLedEx::on_lum_3_editingFinished()
{
    uint8_t lum = ui->lum_3->text().toUInt();
    setLedState(ui->led_3, m_led_status[2].cct, lum, lum > 0);

    uint8_t num = m_addr * 8 + 2;
    sendSimLedState(num, m_led_status[2].lum, m_led_status[2].cct);
}
void ModelLedEx::on_lum_4_editingFinished()
{
    uint8_t lum = ui->lum_4->text().toUInt();
    setLedState(ui->led_4, m_led_status[3].cct, lum, lum > 0);

    uint8_t num = m_addr * 8 + 3;
    sendSimLedState(num, m_led_status[3].lum, m_led_status[3].cct);
}
void ModelLedEx::on_lum_5_editingFinished()
{
    uint8_t lum = ui->lum_5->text().toUInt();
    setLedState(ui->led_5, m_led_status[4].cct, lum, lum > 0);

    uint8_t num = m_addr * 8 + 4;
    sendSimLedState(num, m_led_status[4].lum, m_led_status[4].cct);
}
void ModelLedEx::on_lum_6_editingFinished()
{
    uint8_t lum = ui->lum_6->text().toUInt();
    setLedState(ui->led_6, m_led_status[5].cct, lum, lum > 0);

    uint8_t num = m_addr * 8 + 5;
    sendSimLedState(num, m_led_status[5].lum, m_led_status[5].cct);
}
void ModelLedEx::on_lum_7_editingFinished()
{
    uint8_t lum = ui->lum_7->text().toUInt();
    setLedState(ui->led_7, m_led_status[6].cct, lum, lum > 0);

    uint8_t num = m_addr * 8 + 6;
    sendSimLedState(num, m_led_status[6].lum, m_led_status[6].cct);
}
void ModelLedEx::on_lum_8_editingFinished()
{
    uint8_t lum = ui->lum_8->text().toUInt();
    setLedState(ui->led_8, m_led_status[7].cct, lum, lum > 0);

    uint8_t num = m_addr * 8 + 7;
    sendSimLedState(num, m_led_status[7].lum, m_led_status[7].cct);
}

// 色温改变
void ModelLedEx::on_cct_1_editingFinished()
{
    uint8_t cct = ui->cct_1->text().toUInt();
    setLedState(ui->led_1, cct, m_led_status[0].lum, m_led_status[0].led);

    uint8_t num = m_addr * 8 + 0;
    sendSimLedState(num, m_led_status[0].lum, m_led_status[0].cct);
}
void ModelLedEx::on_cct_2_editingFinished()
{
    uint8_t cct = ui->cct_2->text().toUInt();
    setLedState(ui->led_2, cct, m_led_status[1].lum, m_led_status[1].led);

    uint8_t num = m_addr * 8 + 1;
    sendSimLedState(num, m_led_status[1].lum, m_led_status[1].cct);
}
void ModelLedEx::on_cct_3_editingFinished()
{
    uint8_t cct = ui->cct_3->text().toUInt();
    setLedState(ui->led_3, cct, m_led_status[2].lum, m_led_status[2].led);

    uint8_t num = m_addr * 8 + 2;
    sendSimLedState(num, m_led_status[2].lum, m_led_status[2].cct);
}
void ModelLedEx::on_cct_4_editingFinished()
{
    uint8_t cct = ui->cct_4->text().toUInt();
    setLedState(ui->led_4, cct, m_led_status[3].lum, m_led_status[3].led);

    uint8_t num = m_addr * 8 + 3;
    sendSimLedState(num, m_led_status[3].lum, m_led_status[3].cct);
}
void ModelLedEx::on_cct_5_editingFinished()
{
    uint8_t cct = ui->cct_5->text().toUInt();
    setLedState(ui->led_5, cct, m_led_status[4].lum, m_led_status[4].led);

    uint8_t num = m_addr * 8 + 4;
    sendSimLedState(num, m_led_status[4].lum, m_led_status[4].cct);
}
void ModelLedEx::on_cct_6_editingFinished()
{
    uint8_t cct = ui->cct_6->text().toUInt();
    setLedState(ui->led_6, cct, m_led_status[5].lum, m_led_status[5].led);

    uint8_t num = m_addr * 8 + 5;
    sendSimLedState(num, m_led_status[5].lum, m_led_status[5].cct);
}
void ModelLedEx::on_cct_7_editingFinished()
{
    uint8_t cct = ui->cct_7->text().toUInt();
    setLedState(ui->led_7, cct, m_led_status[6].lum, m_led_status[6].led);

    uint8_t num = m_addr * 8 + 6;
    sendSimLedState(num, m_led_status[6].lum, m_led_status[6].cct);
}
void ModelLedEx::on_cct_8_editingFinished()
{
    uint8_t cct = ui->cct_8->text().toUInt();
    setLedState(ui->led_8, cct, m_led_status[7].lum, m_led_status[7].led);

    uint8_t num = m_addr * 8 + 7;
    sendSimLedState(num, m_led_status[7].lum, m_led_status[7].cct);
}

