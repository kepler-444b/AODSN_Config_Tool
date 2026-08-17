#include "app_set_net.h"
#include "ui_app_set_net.h"

AppSetNet::AppSetNet(QWidget *parent,  AppSerial* serialWidget) :
    QWidget(parent),
    ui(new Ui::AppSetNet)
{
    ui->setupUi(this);
    ui->dns->setEnabled(false);
    ui->mac->setEnabled(false);
    ui->sn->setEnabled(false);
    ui->ver->setEnabled(false);

    m_serialWidget = serialWidget;
    m_protocol_set_net = new AppProtocolSetNet(this, m_serialWidget);   // 创建协议数据实例

    connect(m_serialWidget, &AppSerial::sigRecvData, m_protocol_set_net, &AppProtocolSetNet::RecvDataParse, Qt::UniqueConnection);
    connect(m_protocol_set_net, &AppProtocolSetNet::sigUpdate, this, &AppSetNet::setDisplay, Qt::UniqueConnection);
}

AppSetNet::~AppSetNet()
{
    delete ui;
}

// 下发信息
void AppSetNet::on_set_info_clicked()
{
    dev_packet_t packet; // 构建下发数据包

    // 1. IP
    QStringList ipList = ui->ip->text().split('.');
    for (int i = 0; i < 4 && i < ipList.size(); i++) {
        packet.net.ip[i] = ipList[i].toUInt();
    }

    // 2. 子网掩码
    QStringList snList = ui->sn->text().split('.');
    for (int i = 0; i < 4 && i < snList.size(); i++) {
        packet.net.sn[i] = snList[i].toUInt();
    }

    // 3. 网关
    QStringList gwList = ui->gw->text().split('.');
    for (int i = 0; i < 4 && i < gwList.size(); i++) {
        packet.net.gw[i] = gwList[i].toUInt();
    }

    // 4. DNS
    QStringList dnsList = ui->dns->text().split('.');
    for (int i = 0; i < 4 && i < dnsList.size(); i++) {
        packet.net.dns[i] = dnsList[i].toUInt();
    }

    // 5. DHCP
    QString dhcpText = ui->ip_type->currentText();
    if (dhcpText == "静态IP") {
        packet.net.dhcp = 1;
    } else if (dhcpText == "动态IP") {
        packet.net.dhcp = 2;
    }

    // 6. MAC
    QStringList macList = ui->mac->text().split(':');
    for (int i = 0; i < 6 && i < macList.size(); i++) {
        packet.net.mac[i] = macList[i].toUInt(nullptr, 16);
    }

    // 7. devices
    QByteArray devBytes = ui->dev_name->text().toUtf8();
    memset(packet.devices, 0, sizeof(packet.devices));
    memcpy(packet.devices, devBytes.constData(),
           std::min(devBytes.size(), static_cast<qsizetype>(sizeof(packet.devices))));

    QByteArray verBytes = ui->ver->text().toUtf8();
    memset(packet.ver, 0, sizeof(packet.ver));
    memcpy(packet.ver, devBytes.constData(),
           std::min(devBytes.size(), static_cast<qsizetype>(sizeof(packet.ver))));

    // 8. key
    QByteArray keyBytes = ui->dev_key->text().toUtf8();
    memset(packet.key, 0, sizeof(packet.key));
    memcpy(packet.key, keyBytes.constData(),
           std::min(keyBytes.size(), static_cast<qsizetype>(sizeof(packet.key))));

    if(m_protocol_set_net->SetInfoData(packet))
    {
        QMessageBox::information(this, "提示", "下发信息成功");
    }
}

// 获取信息
void AppSetNet::on_get_info_clicked()
{
    m_protocol_set_net->GetInfoData();
}

// 设置显示信息
void AppSetNet::setDisplay(const dev_packet_t &info)
{
    ui->ip->setText(QString("%1.%2.%3.%4").arg(info.net.ip[0]) .arg(info.net.ip[1]) .arg(info.net.ip[2]) .arg(info.net.ip[3]));

    // 子网掩码
    ui->sn->setText(QString("%1.%2.%3.%4") .arg(info.net.sn[0]) .arg(info.net.sn[1]) .arg(info.net.sn[2]) .arg(info.net.sn[3]));

    // 网关
    ui->gw->setText(QString("%1.%2.%3.%4") .arg(info.net.gw[0]) .arg(info.net.gw[1]) .arg(info.net.gw[2]) .arg(info.net.gw[3]));

    // DNS
    ui->dns->setText(QString("%1.%2.%3.%4") .arg(info.net.dns[0]) .arg(info.net.dns[1]) .arg(info.net.dns[2]) .arg(info.net.dns[3]));

    // DHCP
    if (info.net.dhcp == 1)
    {
        ui->ip_type->setCurrentIndex(ui->ip_type->findText("静态IP"));
    }
    else if (info.net.dhcp == 2)
    {
        ui->ip_type->setCurrentIndex(ui->ip_type->findText("动态IP"));
    }

    // MAC
    QString macStr;
    for (int i = 0; i < 6; i++) {
        macStr += QString("%1").arg(info.net.mac[i], 2, 16, QLatin1Char('0')).toUpper();
        if (i != 5) macStr += ":";
    }
    ui->mac->setText(macStr);

    QString devicesStr = QString::fromUtf8(info.devices, strnlen(info.devices, 32));
    ui->dev_name->setText(devicesStr);

    // key
    QString keyStr = QString::fromUtf8(info.key, strnlen(info.key, 128));
    ui->dev_key->setText(keyStr);

    // ver
    QString verStr = QString::fromUtf8(info.ver, strnlen(info.ver, 16));
    ui->ver->setText(verStr);

    QMessageBox::information(this, "提示", "设备信息获取成功");
}



