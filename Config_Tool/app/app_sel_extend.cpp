#include "app_sel_extend.h"
#include "ui_app_sel_extend.h"

DialogExtend::DialogExtend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogExtend)
{
    ui->setupUi(this);
    this->setWindowTitle("选择扩展");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

DialogExtend::~DialogExtend()
{
    delete ui;
}

// 选择led扩展
void DialogExtend::on_led_ex_clicked()
{
    m_ExtendInfo.type = LED_EX;
}

// 选择继电器扩展
void DialogExtend::on_relay_ex_clicked()
{
    m_ExtendInfo.type = RELAY_EX;
}

// 确定
void DialogExtend::on_pushButton_clicked()
{
    accept();
}


ExtendInfo_t DialogExtend::GetExtendInfo() const
{
    return m_ExtendInfo;
}


void DialogExtend::on_set_addr_valueChanged(int arg1)
{
    if (arg1 > 4)
    {
        arg1 = 4;
        ui->set_addr->setValue(4); // 强制拉回最大值
        QMessageBox::warning(this, "提示", "地址不能大于4,已自动修改为4");
    }
    m_ExtendInfo.id = arg1;
}

void DialogExtend::SetExtendInfo(const ExtendInfo_t &info)
{
    m_ExtendInfo = info;
    ui->set_addr->setValue(info.id);

    ui->relay_ex->setChecked(false);
    ui->led_ex->setChecked(false);

    if (info.type == RELAY_EX)
    {
        ui->relay_ex->setChecked(true);
    }
    if (info.type == LED_EX)
    {
        ui->led_ex->setChecked(true);
    }
}
