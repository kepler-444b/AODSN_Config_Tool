#include "app_set_addr.h"
#include "ui_app_set_addr.h"

AppSetAddr::AppSetAddr(QWidget *parent, AppSerial* serialWidget) :
    QWidget(parent),
    ui(new Ui::AppSetAddr)
{
    ui->setupUi(this);
    ui->lineEdit->setEnabled(false);
    ui->triac_ver->setEnabled(false);
    ui->auto_ver->setEnabled(false);
    ui->mmw_ver->setEnabled(false);

    m_serialWidget = serialWidget;

    m_protocol_set_addr = new AppProtocolSetAddr(this, m_serialWidget);
    connect(m_protocol_set_addr, &AppProtocolSetAddr::sigDevInfo, this, &AppSetAddr::recvDevInfo, Qt::UniqueConnection);
    connect(m_serialWidget, &AppSerial::sigRecvData, m_protocol_set_addr, &AppProtocolSetAddr::RecvDataParse, Qt::UniqueConnection);

    m_sendTimer.setSingleShot(true);
    connect(&m_sendTimer, &QTimer::timeout, this, &AppSetAddr::onSendTimeout);

    ui->SetAddrWidget->setCurrentIndex(0); // 默认显示第0页,即灯控面板
}

AppSetAddr::~AppSetAddr()
{
    delete ui;
}

// 设备选择
void AppSetAddr::on_device_sel_activated(int index)
{
    ui->SetAddrWidget->setCurrentIndex(index);
    switch (index)
    {
    case 0: // 灯控面板
        break;

    case 1: // 4路可控硅
        break;

    case 2: // 雷达感应调光主机
        initRadarCheckBox();
        auto_crtl_enable(false);  // 雷达感应调光主机默认禁用
        break;
    case 3: // 毫米波雷达
        break;
    default:
        break;
    }
}
// ========================== 灯控面板 ==========================

// 面板设备地址更新
void AppSetAddr::on_spinBox_valueChanged(int addr)
{
    m_protocol_set_addr->AddrSet(addr);
    qDebug() << "Panel Addr:" << addr;
}

// 地址群发
void AppSetAddr::on_pushButton_clicked()
{
    m_protocol_set_addr->AddrSendAll();
}

// 获取面板设备信息
void AppSetAddr::on_dev_info_clicked()
{
    uint8_t addr = ui->spinBox->value();
    m_protocol_set_addr->GetInfo(0x00, addr);
}

// ======================== 4路可控硅调光 ========================

// 4路可控硅获取设备信息
void AppSetAddr::on_triac_get_cfg_clicked()
{
    uint8_t addr = ui->triac_addr->value();
    m_protocol_set_addr->GetInfo(0x01, addr);
}

// 4路可控硅设置设备信息
void AppSetAddr::on_triac_set_cfg_clicked()
{
    uint8_t addr = ui->triac_addr->value();
    m_protocol_set_addr->SetInfo(0x01, 0x01, addr, 0x00);
}

// 4路可控硅死区调节滑动条
void AppSetAddr::on_QSlider_triac_death_valueChanged(int value)
{
    ui->triac_death->setText(QString::number(value));
    m_TriacDeathValue = value;
    m_sendType = TRIAC_DEATH;
    m_sendTimer.start(100);
}

// 4路可控硅亮度调节滑块
void AppSetAddr::on_QSlider_triac_lum_valueChanged(int value)
{
    ui->triac_lum->setText(QString::number(value));
    m_TriacLumValue = value;
    m_sendType = TRIAC_LUM;
    m_sendTimer.start(100);
}

// 4路可控硅设置渐变时间
void AppSetAddr::on_triac_grad_valueChanged(int fade_time)
{
    uint8_t addr = ui->triac_addr->value();
    m_protocol_set_addr->SetInfo(0x01, 0x04, addr, fade_time);
}

// ======================= 雷达感应调光主机 =======================

// 获取雷达感应调光主机信息
void AppSetAddr::on_auto_get_cfg_clicked()
{
    uint8_t addr = ui->auto_addr->value();
    m_protocol_set_addr->GetInfo(0x02, addr);
}

// 保存雷达感应调光主机信息
void AppSetAddr::on_auto_set_cfg_clicked()
{
    uint8_t addr = ui->auto_addr->value();
    m_protocol_set_addr->SetInfo(0x02, 0x01, addr, 0x00);
}

// 雷达感应调光主机设置渐变时间
void AppSetAddr::on_auto_grad_valueChanged(int fade_time)
{
    uint8_t addr = ui->auto_addr->value();
    m_protocol_set_addr->SetInfo(0x02, 0x04, addr, fade_time);
}

// 雷达感应调光主机死区调节滑动条
void AppSetAddr::on_QSlider_auto_death_valueChanged(int value)
{
    ui->auto_death->setText(QString::number(value));
    m_AutoDeathValue = value;
    if (m_data_echo)
    {
        return;
    }

    m_sendType = AUTO_DRATH;
    m_sendTimer.start(100); // 延迟发送
}

// 雷达感应调光主机无人亮度滑条
void AppSetAddr::on_QSlider_auto_no_one_valueChanged(int value)
{
    ui->auto_no_one->setText(QString::number(value));
    m_AutoNoOneValue = value;
    if (m_data_echo)
    {
        return;
    }
    m_sendType = AUTO_NO_ONE;
    m_sendTimer.start(100); // 延迟发送
}

// 雷达感应调光主机有人亮度滑条
void AppSetAddr::on_QSlider_auto_some_one_valueChanged(int value)
{
    ui->auto_some_one->setText(QString::number(value));
    m_AutoSomeOneValue = value;
    if (m_data_echo)
    {
        return;
    }
    m_sendType = AUTO_SOME_ONE;
    m_sendTimer.start(100); // 延迟发送
}

// 雷达感应调光主机活跃亮度滑条
void AppSetAddr::on_QSlider_auto_active_valueChanged(int value)
{
    ui->auto_active->setText(QString::number(value));
    m_AutoActiveValue = value;
    if (m_data_echo)
    {
        return;
    }
    m_sendType = AUTO_ACTIVE;
    m_sendTimer.start(100); // 延迟发送
}

// 雷达感应调光主机进入调试模式
void AppSetAddr::on_auto_debug_clicked()
{
    uint8_t addr = ui->auto_addr->value();
    if (ui->auto_debug->isChecked())
    {
        auto_crtl_enable(true);
        m_protocol_set_addr->SetInfo(0x02, 0x05, addr, true);
    }
    else
    {
        auto_crtl_enable(false);
        m_protocol_set_addr->SetInfo(0x02, 0x05, addr, false);
    }
}

// 初始化雷达通道复选框,并连接统一状态变化槽函数
void AppSetAddr::initRadarCheckBox()
{
    // 雷达1
    m_radar_check[0][0] = ui->ladar_1_pwm1;
    m_radar_check[0][1] = ui->ladar_1_pwm2;
    m_radar_check[0][2] = ui->ladar_1_pwm3;
    m_radar_check[0][3] = ui->ladar_1_pwm4;
    m_radar_check[0][4] = ui->ladar_1_vol1;
    m_radar_check[0][5] = ui->ladar_1_vol2;
    m_radar_check[0][6] = ui->ladar_1_vol3;
    m_radar_check[0][7] = ui->ladar_1_vol4;

    // 雷达2
    m_radar_check[1][0] = ui->ladar_2_pwm1;
    m_radar_check[1][1] = ui->ladar_2_pwm2;
    m_radar_check[1][2] = ui->ladar_2_pwm3;
    m_radar_check[1][3] = ui->ladar_2_pwm4;
    m_radar_check[1][4] = ui->ladar_2_vol1;
    m_radar_check[1][5] = ui->ladar_2_vol2;
    m_radar_check[1][6] = ui->ladar_2_vol3;
    m_radar_check[1][7] = ui->ladar_2_vol4;

    // 雷达3
    m_radar_check[2][0] = ui->ladar_3_pwm1;
    m_radar_check[2][1] = ui->ladar_3_pwm2;
    m_radar_check[2][2] = ui->ladar_3_pwm3;
    m_radar_check[2][3] = ui->ladar_3_pwm4;
    m_radar_check[2][4] = ui->ladar_3_vol1;
    m_radar_check[2][5] = ui->ladar_3_vol2;
    m_radar_check[2][6] = ui->ladar_3_vol3;
    m_radar_check[2][7] = ui->ladar_3_vol4;

    // 雷达4
    m_radar_check[3][0] = ui->ladar_4_pwm1;
    m_radar_check[3][1] = ui->ladar_4_pwm2;
    m_radar_check[3][2] = ui->ladar_4_pwm3;
    m_radar_check[3][3] = ui->ladar_4_pwm4;
    m_radar_check[3][4] = ui->ladar_4_vol1;
    m_radar_check[3][5] = ui->ladar_4_vol2;
    m_radar_check[3][6] = ui->ladar_4_vol3;
    m_radar_check[3][7] = ui->ladar_4_vol4;

    // 所有 Checkbox 共用一个槽函数
    for (int radar = 0; radar < 4; radar++)
    {
        for (int index = 0; index < 8; index++)
        {
            connect(m_radar_check[radar][index], &QCheckBox::toggled, this, &AppSetAddr::onRadarCheckChanged);
        }
    }
}

// 雷达感应调光主机复选框映射
void AppSetAddr::onRadarCheckChanged(bool checked)
{
    uint8_t addr = ui->auto_addr->value();
    if (m_data_echo) // 如果是回显的,不触发
    {
        return;
    }

    QCheckBox *checkBox = qobject_cast<QCheckBox *>(sender());

    if (checkBox == nullptr)
    {
        return;
    }

    for (int radar = 0; radar < 4; radar++)
    {
        for (int index = 0; index < 8; index++)
        {
            if (m_radar_check[radar][index] == checkBox)
            {
                // 保存当前复选框状态
                m_radar_map[radar][index] = checked ? 1 : 0;
                QByteArray radar_map(reinterpret_cast<const char *>(m_radar_map), sizeof(m_radar_map));
                m_protocol_set_addr->SetInfo(0x02, 0x09, addr, radar_map);

                return;
            }
        }
    }
}

// 雷达感应调光主机禁用控件
void AppSetAddr::auto_crtl_enable(bool enable)
{
    // 雷达感应调光主机,在没有进入调试模式的时候,禁用若干控件

    ui->QSlider_auto_death->setEnabled(enable);       // 死区调节滑块
    ui->auto_death->setEnabled(enable);               // 死区调节数值

    ui->QSlider_auto_no_one->setEnabled(enable);      // 无人亮度滑块
    ui->auto_no_one->setEnabled(enable);              // 无人亮度数值

    ui->QSlider_auto_some_one->setEnabled(enable);    // 有人亮度滑块
    ui->auto_some_one->setEnabled(enable);            // 有人亮度数值

    ui->QSlider_auto_active->setEnabled(enable);      // 活跃亮度滑块
    ui->auto_active->setEnabled(enable);              // 活跃亮度数值

    ui->auto_grad->setEnabled(enable);                // 渐变设置

    // 雷达 PWM / VOL 控件
    for (int radar = 0; radar < 4; radar++)
    {
        for (int index = 0; index < 8; index++)
        {
            m_radar_check[radar][index]->setEnabled(enable);
        }
    }
}

// ========================== 毫米波雷达 =========================
// 获取毫米波雷达设备信息
void AppSetAddr::on_get_radar_info_clicked()
{
    uint8_t addr = ui->mmw_radar->value();
    m_protocol_set_addr->GetInfo(0x03, addr);
}

// 设置毫米波雷达设备信息
void AppSetAddr::on_set_radar_info_clicked()
{
    uint8_t addr = ui->mmw_radar->value();
    uint8_t value = ui->mmw_radar_new_addr->text().toInt();

    m_protocol_set_addr->MmwRadarSetInfo(value, addr);

}


// 回显设备信息
void AppSetAddr::recvDevInfo(const QByteArray data)
{
    //    uint8_t data_len = data[2];
    uint8_t cmd_type = data[3];
    uint8_t dev_type = data[4];
    uint8_t dev_ver  = data[5];

    if (cmd_type == 0x05) // 获取设备信息
    {
        m_data_echo = true; // 标志为回显数据
        if (dev_type == 0x00) // 面板类设备
        {
            if (dev_ver > 99)
            {
                dev_ver = 99;
            }
            double version_num = dev_ver / 10.0;
            QString version_str = QString("V %1").arg(version_num, 0, 'f', 1);
            ui->lineEdit->setText(version_str);
        }
        if (dev_type == 0x01) // 可控硅调光
        {
            if (dev_ver > 99)
            {
                dev_ver = 99;
            }
            double version_num = dev_ver / 10.0;
            QString version_str = QString("V %1").arg(version_num, 0, 'f', 1);
            ui->triac_ver->setText(version_str);

            uint8_t fade_time   = data[7];
            uint8_t death_value = data[8];

            ui->triac_grad->setValue(fade_time);                     // 设置渐变时间
            ui->triac_death->setText(QString::number(death_value));  // 设置死区数值
            ui->QSlider_triac_death->setValue(death_value);
        }
        if(dev_type == 0x02) // 雷达感应调光主机
        {
            if (dev_ver > 99)
            {
                dev_ver = 99;
            }
            double version_num = dev_ver / 10.0;
            QString version_str = QString("V %1").arg(version_num, 0, 'f', 1);
            ui->auto_ver->setText(version_str);

            uint8_t fade_time   = data[7];
            uint8_t death_value = data[8];

            uint8_t no_one_value   = data[9];
            uint8_t some_one_value = data[10];
            uint8_t active_value   = data[11];

            ui->auto_grad->setValue(fade_time);                     // 设置渐变时间
            ui->auto_death->setText(QString::number(death_value));  // 设置死区数值
            ui->QSlider_auto_death->setValue(death_value);

            ui->auto_no_one->setText(QString::number(no_one_value)); // 设置无人数值
            ui->QSlider_auto_no_one->setValue(no_one_value);

            ui->auto_some_one->setText(QString::number(some_one_value)); // 设置有人数值
            ui->QSlider_auto_some_one->setValue(some_one_value);

            ui->auto_active->setText(QString::number(active_value)); // 设置活跃数值
            ui->QSlider_auto_active->setValue(active_value);

            // 雷达映射勾选框回显
            uint8_t radar_1[8];
            uint8_t radar_2[8];
            uint8_t radar_3[8];
            uint8_t radar_4[8];

            memcpy(radar_1, data.constData() + 12, sizeof(radar_1));
            memcpy(radar_2, data.constData() + 20, sizeof(radar_2));
            memcpy(radar_3, data.constData() + 28, sizeof(radar_3));
            memcpy(radar_4, data.constData() + 36, sizeof(radar_4));

            for (int radar = 0; radar < 4; radar++)
            {
                for (int index = 0; index < 8; index++)
                {
                    m_radar_map[radar][index] = data[12 + radar * 8 + index] ? 1 : 0;        // 保存雷达映射数据
                    m_radar_check[radar][index]->setChecked(m_radar_map[radar][index] != 0); // 回显到 Checkbox
                }
            }
        }
        if(dev_type == 0x03) // 毫米波雷达
        {
            if (dev_ver > 99)
            {
                dev_ver = 99;
            }
            double version_num = dev_ver / 10.0;
            QString version_str = QString("V %1").arg(version_num, 0, 'f', 1);
            ui->mmw_ver->setText(version_str);
        }
        m_data_echo = false;
    }
}

// 滑块延时发送
void AppSetAddr::onSendTimeout()
{
    switch(m_sendType)
    {
    case TRIAC_DEATH:
    {
        uint8_t addr = ui->triac_addr->value();
        m_protocol_set_addr->SetInfo(0x01, 0x02, addr, m_TriacDeathValue);
    }
    break;
    case TRIAC_LUM:
    {
        uint8_t addr = ui->triac_addr->value();
        m_protocol_set_addr->SetInfo(0x01, 0x03, addr, m_TriacLumValue);
    }
    break;
    case AUTO_DRATH:
    {
        uint8_t addr = ui->auto_addr->value();
        m_protocol_set_addr->SetInfo(0x02, 0x02, addr, m_AutoDeathValue);
    }
    break;
    case AUTO_NO_ONE:
    {
        uint8_t addr = ui->auto_addr->value();
        m_protocol_set_addr->SetInfo(0x02, 0x06, addr, m_AutoNoOneValue);
    }
    break;
    case AUTO_SOME_ONE:
    {
        uint8_t addr = ui->auto_addr->value();
        m_protocol_set_addr->SetInfo(0x02, 0x07, addr, m_AutoSomeOneValue);
    }
    break;
    case AUTO_ACTIVE:
    {
        uint8_t addr = ui->auto_addr->value();
        m_protocol_set_addr->SetInfo(0x02, 0x08, addr, m_AutoActiveValue);
    }
    break;
    default:
        break;
    }
}













