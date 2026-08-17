#include "app_sel_panel.h"
#include "ui_app_sel_panel.h"

DialogPanel::DialogPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPanel)
{
    ui->setupUi(this);
    this->setWindowTitle("选择面板");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

DialogPanel::~DialogPanel()
{
    delete ui;
}

// 选择面板类型
void DialogPanel::on_knob_clicked()
{
    m_PanelInfo.type = KNOB;
}

void DialogPanel::on_panel_clicked()
{
    m_PanelInfo.type = PANEL;
}


// 选择按键个数
void DialogPanel::on_key_1_clicked()
{
    m_PanelInfo.key_num = 1;
}

void DialogPanel::on_key_2_clicked()
{
    m_PanelInfo.key_num = 2;
}

void DialogPanel::on_key_3_clicked()
{
    m_PanelInfo.key_num = 3;
}

void DialogPanel::on_key_4_clicked()
{
    m_PanelInfo.key_num = 4;
}

void DialogPanel::on_key_6_clicked()
{
    m_PanelInfo.key_num = 6;
}

void DialogPanel::on_set_addr_valueChanged(int arg1)
{
    if (arg1 > 32)
    {
        arg1 = 32;
        ui->set_addr->setValue(32); // 强制拉回最大值
        QMessageBox::warning(this, "提示", "地址不能大于32,已自动修改为32");
    }
    m_PanelInfo.addr = arg1;
}

PanelInfo_t DialogPanel::GetPanelInfo() const
{
    return m_PanelInfo;
}

void DialogPanel::on_pushButton_clicked()
{
    accept();
}

void DialogPanel::SetPanelInfo(const PanelInfo_t &info)
{
    m_PanelInfo = info;

    ui->set_addr->setValue(info.addr);

    ui->knob->setChecked(false);
    ui->panel->setChecked(false);

    if (info.type == KNOB)
    {
        ui->knob->setChecked(true);
    }
    else if (info.type == PANEL)
    {
        ui->panel->setChecked(true);
    }

    ui->key_1->setChecked(false);
    ui->key_2->setChecked(false);
    ui->key_3->setChecked(false);
    ui->key_4->setChecked(false);
    ui->key_6->setChecked(false);

    switch (info.key_num)
    {
    case 1: ui->key_1->setChecked(true); break;
    case 2: ui->key_2->setChecked(true); break;
    case 3: ui->key_3->setChecked(true); break;
    case 4: ui->key_4->setChecked(true); break;
    case 6: ui->key_6->setChecked(true); break;
    default: break;
    }
}

