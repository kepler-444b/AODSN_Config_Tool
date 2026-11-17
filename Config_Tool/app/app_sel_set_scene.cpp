#include "app_sel_set_scene.h"
#include "ui_app_sel_set_scene.h"
#include <QRegularExpression>

DialogSetScene::DialogSetScene(const QVector<PanelInfo_t> &panels,
                               const QVector<ExtendInfo_t> &extends,
                               const uint8_t scene_id,
                               const QString scene_name,
                               QWidget *parent) : QDialog(parent),
                                                  ui(new Ui::DialogSetScene),
                                                  m_panels(panels),
                                                  m_extends(extends)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    this->setWindowTitle("创建配置");
    ui->scene_name->setText(scene_name);
    ui->spinBox->setValue(scene_id);

    // 确保 scrollArea 内部有布局
    if (!ui->sel_panel->layout())
        ui->sel_panel->setLayout(new QVBoxLayout);

    if (!ui->sel_led->layout())
        ui->sel_led->setLayout(new QVBoxLayout);

    if (!ui->sel_relay->layout())
        ui->sel_relay->setLayout(new QVBoxLayout);

    populatePanels(); // 根据 m_panels 动态生成控件
    populateLeds();
    populateRelays();
}

DialogSetScene::~DialogSetScene()
{
    delete ui;
}

void DialogSetScene::editScene(int id)
{
    qDebug() << "id" << id;
}

// 设置面板
void DialogSetScene::populatePanels()
{
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(ui->sel_panel->layout());
    if (!layout)
        return;

    layout->setSpacing(2);
    layout->setContentsMargins(5, 5, 5, 5);

    for (const PanelInfo_t &panel : std::as_const(m_panels)) {
        // 一个面板对应一个GroupBox
        QGroupBox *group = new QGroupBox(ui->sel_panel);

        group->setTitle(
            QString("面板地址:%1  按键数量:%2  类型:%3")
                .arg(panel.addr)
                .arg(panel.key_num)
                .arg(panel.type == 0 ? "旋钮面板" : (panel.type == 1 ? "灯控面板" : "调光面板")));

        QHBoxLayout *groupLayout = new QHBoxLayout(group);
        groupLayout->setContentsMargins(5, 5, 5, 5);
        groupLayout->setSpacing(6);

        // 先生成基础按键
        for (int i = 0; i < panel.key_num; ++i) {
            // 一个按键一个widget
            QWidget *keyWidget     = new QWidget(group);
            QHBoxLayout *keyLayout = new QHBoxLayout(keyWidget);
            keyLayout->setContentsMargins(0, 0, 0, 0);
            keyLayout->setSpacing(2);
            QString name = panel.key_name[i];

            if (name.isEmpty())
                name = QString("键%1").arg(i + 1);
            // 使能
            QCheckBox *enableBox = new QCheckBox(name, keyWidget);
            enableBox->setFixedWidth(70);
            enableBox->setLayoutDirection(Qt::RightToLeft);
            // 状态
            QCheckBox *stateBox = new QCheckBox(keyWidget);
            bool isEnable       = (i < panel.key_enable.size()) ? panel.key_enable[i] : false;
            bool isState        = (i < panel.key_state.size()) ? panel.key_state[i] : false;

            enableBox->setChecked(isEnable);
            stateBox->setChecked(isState);
            stateBox->setEnabled(isEnable);
            connect(enableBox, &QCheckBox::toggled, stateBox, &QCheckBox::setEnabled);

            // 加入按键自己的布局
            keyLayout->addWidget(enableBox);
            keyLayout->addWidget(stateBox);
            // 加入面板布局
            groupLayout->addWidget(keyWidget);
        }

        if (panel.type == KNOB) // 如果是旋钮面板的话,需要增加亮度和色温
        {
            // 追加亮度
            QWidget *briWidget     = new QWidget(group);
            QHBoxLayout *briLayout = new QHBoxLayout(briWidget);
            briLayout->setContentsMargins(0, 0, 0, 0);
            briLayout->setSpacing(2);

            QCheckBox *briEnableBox = new QCheckBox("亮度", briWidget);
            briEnableBox->setLayoutDirection(Qt::RightToLeft);

            QSpinBox *briSpinBox = new QSpinBox(briWidget);
            briSpinBox->setRange(0, 100);

            // 直接使用 PanelInfo_t 中的新字段
            briEnableBox->setChecked(panel.lum_enable);
            briSpinBox->setValue(panel.lum_value);
            briSpinBox->setEnabled(panel.lum_enable);
            connect(briEnableBox, &QCheckBox::toggled, briSpinBox, &QSpinBox::setEnabled);

            briLayout->addWidget(briEnableBox);
            briLayout->addWidget(briSpinBox);
            groupLayout->addWidget(briWidget);

            // 追加色温
            QWidget *ctWidget     = new QWidget(group);
            QHBoxLayout *ctLayout = new QHBoxLayout(ctWidget);
            ctLayout->setContentsMargins(0, 0, 0, 0);
            ctLayout->setSpacing(2);

            QCheckBox *ctEnableBox = new QCheckBox("色温", ctWidget);
            ctEnableBox->setLayoutDirection(Qt::RightToLeft);

            QSpinBox *ctSpinBox = new QSpinBox(ctWidget);
            ctSpinBox->setRange(0, 100); // 若需支持2700~6500K，需将结构体中的 uint8_t cct_value 改为 uint16_t

            // 直接使用 PanelInfo_t 中的新字段
            ctEnableBox->setChecked(panel.cct_enable);
            ctSpinBox->setValue(panel.cct_value);
            ctSpinBox->setEnabled(panel.cct_enable);
            connect(ctEnableBox, &QCheckBox::toggled, ctSpinBox, &QSpinBox::setEnabled);

            ctLayout->addWidget(ctEnableBox);
            ctLayout->addWidget(ctSpinBox);
            groupLayout->addWidget(ctWidget);
        }
        groupLayout->addStretch();
        layout->addWidget(group);
    }
    layout->addStretch();
}

// 设置led
void DialogSetScene::populateLeds()
{
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(ui->sel_led->layout());
    if (!layout) return;

    layout->setSpacing(2);
    layout->setContentsMargins(5, 5, 5, 5);

    for (const ExtendInfo_t &ex : std::as_const(m_extends)) {
        if (ex.type != LED_EX) continue;

        QGroupBox *group         = new QGroupBox(QString("LED扩展地址:%1").arg(ex.id));
        QHBoxLayout *groupLayout = new QHBoxLayout(group); // 直接绑定父控件
        groupLayout->setContentsMargins(5, 5, 5, 5);
        groupLayout->setSpacing(2); // 设置使能框,亮度框,色温框之间的微小间距

        for (int i = 0; i < 8; ++i) {
            QCheckBox *enableBox = new QCheckBox(QString("%1").arg(ex.id * 8 + i), group);
            enableBox->setFixedWidth(35);
            enableBox->setLayoutDirection(Qt::RightToLeft);

            QLineEdit *input_lum = new QLineEdit(group);
            input_lum->setFixedWidth(25);
            input_lum->setValidator(new QIntValidator(0, 100, input_lum));
            input_lum->setAlignment(Qt::AlignCenter);

            QLineEdit *input_cct = new QLineEdit(group);
            input_cct->setFixedWidth(25);
            input_cct->setValidator(new QIntValidator(0, 100, input_cct));
            input_cct->setAlignment(Qt::AlignCenter);

            // 提取与填充数据
            bool isEnable = (i < ex.led_enable.size()) ? ex.led_enable[i] : false;
            int lumValue  = (i < ex.led_lum.size()) ? ex.led_lum[i] : 0;  // 亮度提起
            int cctValue  = (i < ex.led_cct.size()) ? ex.led_cct[i] : 50; // 色温提取(默认50)

            enableBox->setChecked(isEnable);
            input_lum->setText(QString::number(lumValue));
            input_cct->setText(QString::number(cctValue));

            // 联动状态设置
            input_lum->setEnabled(isEnable);
            input_cct->setEnabled(isEnable);
            QObject::connect(enableBox, &QCheckBox::toggled, input_lum, &QLineEdit::setEnabled);
            QObject::connect(enableBox, &QCheckBox::toggled, input_cct, &QLineEdit::setEnabled);

            // 直接按顺序加入组布局，去除内部 QWidget 包装
            groupLayout->addWidget(enableBox);
            groupLayout->addWidget(input_lum);
            groupLayout->addWidget(input_cct);

            // 通道与通道之间留出 8px 的隔离间距(最后一个通道除外)
            if (i < 7) {
                groupLayout->addSpacing(6);
            }
        }
        groupLayout->addStretch(); // 尾部加弹簧靠左对齐
        layout->addWidget(group);
    }
    layout->addStretch();
}

// 设置继电器扩展
void DialogSetScene::populateRelays()
{
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(ui->sel_relay->layout());
    if (!layout) return;

    layout->setSpacing(2);
    layout->setContentsMargins(5, 5, 5, 5);

    for (const ExtendInfo_t &ex : std::as_const(m_extends)) {
        if (ex.type != RELAY_EX) continue;

        QGroupBox *group         = new QGroupBox(QString("继电器扩展地址:%1").arg(ex.id));
        QHBoxLayout *groupLayout = new QHBoxLayout(group); // 直接绑定父控件
        groupLayout->setContentsMargins(5, 5, 5, 5);
        groupLayout->setSpacing(2); // "使能"与"状态"框之间的紧凑间距

        for (int i = 0; i < 10; ++i) // 固定 15 通道
        {
            QCheckBox *enableBox = new QCheckBox(QString("%1").arg(ex.id * 10 + i), group);
            // QCheckBox *enableBox = new QCheckBox(QString("%1").arg(i + 1), group);
            enableBox->setFixedWidth(35);
            enableBox->setLayoutDirection(Qt::RightToLeft);
            QCheckBox *stateBox = new QCheckBox(group);

            bool isEnable = (i < ex.relay_enable.size()) ? ex.relay_enable[i] : false;
            bool isState  = (i < ex.relay_state.size()) ? ex.relay_state[i] : false;

            enableBox->setChecked(isEnable);
            stateBox->setChecked(isState);
            stateBox->setEnabled(isEnable);

            QObject::connect(enableBox, &QCheckBox::toggled, stateBox, &QCheckBox::setEnabled);

            groupLayout->addWidget(enableBox);
            groupLayout->addWidget(stateBox);

            // 15 个通道每个通道组合之间设置 6px 隔离间隔(最后一个除外)
            if (i < 14) {
                groupLayout->addSpacing(6);
            }
        }
        groupLayout->addStretch(); // 尾部加弹簧靠左对齐
        layout->addWidget(group);
    }

    layout->addStretch(); // 底部留白
}

void DialogSetScene::on_spinBox_valueChanged(int arg1)
{
    m_scene_info.scene_id = arg1; // 场景号
}

// 确定按钮
void DialogSetScene::on_pushButton_clicked()
{
    QVector<panel_data_t> panelsResult;
    QVector<led_data_t> ledsResult;
    QVector<relay_data_t> relayResult;

    uint8_t scene_id   = static_cast<uint8_t>(ui->spinBox->value()); // 获取UI上的场景id
    QString scene_name = ui->scene_name->text();                     // 获取UI上的场景别名

    QVBoxLayout *panelLayout = qobject_cast<QVBoxLayout *>(ui->sel_panel->layout());

    // panel 数据
    if (panelLayout) {
        for (int i = 0; i < panelLayout->count(); ++i) {
            QGroupBox *group = qobject_cast<QGroupBox *>(panelLayout->itemAt(i)->widget());
            if (!group) continue;

            panel_data_t pdata;
            parseGroupBoxInfo(group, pdata.addr, pdata.key_num, pdata.type);

            QHBoxLayout *groupLayout = qobject_cast<QHBoxLayout *>(group->layout());
            if (!groupLayout) continue;

            // 只遍历前 pdata.key_num 个按键 Widget
            int keyCount = 0;
            for (int j = 0; j < groupLayout->count(); ++j) {
                QWidget *widget = groupLayout->itemAt(j)->widget();
                if (!widget) continue;

                QHBoxLayout *keyLayout = qobject_cast<QHBoxLayout *>(widget->layout());
                if (!keyLayout) continue;

                // 只要收集到了足够的按键数量,就停止解析按键
                if (keyCount >= pdata.key_num)
                    break;

                QCheckBox *enable = qobject_cast<QCheckBox *>(keyLayout->itemAt(0)->widget());
                QCheckBox *state  = qobject_cast<QCheckBox *>(keyLayout->itemAt(1)->widget());

                if (enable) {
                    pdata.key_name[keyCount] = enable->text();
                    pdata.key_enable.append(enable->isChecked());
                }

                if (state) {
                    pdata.key_state.append(state->isChecked());
                }
                keyCount++;
            }

            // 如果是旋钮面板 (type == 0),按键解析完后,去获取末尾追加的亮度和色温
            if (pdata.type == KNOB) {
                // 按键占用了前 pdata.key_num 个位置 (索引 0 ~ key_num-1)
                // 亮度 Widget 在索引 key_num，色温 Widget 在索引 key_num + 1
                int briIndex = pdata.key_num;
                int ctIndex  = pdata.key_num + 1;

                // 解析亮度 Widget
                if (briIndex < groupLayout->count()) {
                    QWidget *briWidget = groupLayout->itemAt(briIndex)->widget();
                    if (briWidget && briWidget->layout()) {
                        QCheckBox *lumEnable = qobject_cast<QCheckBox *>(briWidget->layout()->itemAt(0)->widget());
                        QSpinBox *lumValue   = qobject_cast<QSpinBox *>(briWidget->layout()->itemAt(1)->widget());
                        if (lumEnable) pdata.lum_enable = lumEnable->isChecked();
                        if (lumValue) pdata.lum_value = static_cast<uint8_t>(lumValue->value());
                    }
                }
                // 解析色温 Widget
                if (ctIndex < groupLayout->count()) {
                    QWidget *ctWidget = groupLayout->itemAt(ctIndex)->widget();
                    if (ctWidget && ctWidget->layout()) {
                        QCheckBox *cctEnable = qobject_cast<QCheckBox *>(ctWidget->layout()->itemAt(0)->widget());
                        QSpinBox *cctValue   = qobject_cast<QSpinBox *>(ctWidget->layout()->itemAt(1)->widget());
                        if (cctEnable) pdata.cct_enable = cctEnable->isChecked();
                        if (cctValue) pdata.cct_value = static_cast<uint8_t>(cctValue->value());
                    }
                }
            }

            panelsResult.append(pdata);
        }
    }

    // LED扩展数据
    QVBoxLayout *ledLayout = qobject_cast<QVBoxLayout *>(ui->sel_led->layout());

    if (ledLayout) {
        for (int i = 0; i < ledLayout->count(); ++i) {
            QGroupBox *group = qobject_cast<QGroupBox *>(ledLayout->itemAt(i)->widget());
            if (!group)
                continue;
            led_data_t ldata;

            ldata.addr               = getAddrFromGroup(group);
            QHBoxLayout *groupLayout = qobject_cast<QHBoxLayout *>(group->layout());

            if (!groupLayout)
                continue;

            for (int ch = 0; ch < 8; ++ch) {
                int index         = ch * 4;
                QCheckBox *enable = qobject_cast<QCheckBox *>(groupLayout->itemAt(index)->widget());
                QLineEdit *lum    = qobject_cast<QLineEdit *>(groupLayout->itemAt(index + 1)->widget());
                QLineEdit *cct    = qobject_cast<QLineEdit *>(groupLayout->itemAt(index + 2)->widget());

                if (enable)
                    ldata.led_enabled.append(enable->isChecked());
                if (lum)
                    ldata.led_lum.append(lum->text().toInt());
                if (cct)
                    ldata.led_cct.append(cct->text().toInt());
            }
            ledsResult.append(ldata);
        }
    }

    // 继电器扩展数据
    QVBoxLayout *relayLayout = qobject_cast<QVBoxLayout *>(ui->sel_relay->layout());

    if (relayLayout) {
        for (int i = 0; i < relayLayout->count(); ++i) {
            QGroupBox *group =
                qobject_cast<QGroupBox *>(relayLayout->itemAt(i)->widget());

            if (!group)
                continue;
            relay_data_t rdata;
            rdata.addr = getAddrFromGroup(group);

            QHBoxLayout *groupLayout = qobject_cast<QHBoxLayout *>(group->layout());
            if (!groupLayout)
                continue;

            for (int ch = 0; ch < 10; ++ch) {
                int index         = ch * 3;
                QCheckBox *enable = qobject_cast<QCheckBox *>(groupLayout->itemAt(index)->widget());
                QCheckBox *state  = qobject_cast<QCheckBox *>(groupLayout->itemAt(index + 1)->widget());

                if (enable)
                    rdata.relay_enabled.append(enable->isChecked());
                if (state)
                    rdata.relay_state.append(state->isChecked());
            }
            relayResult.append(rdata);
        }
    }

    emit send_config(panelsResult, ledsResult, relayResult, scene_id, scene_name); // 通过信号发送数据

    // 根据外部槽函数修改后的结果,决定是否关闭本窗口
    if (m_sendSuccess) {
        qDebug() << "m_sendSuccess" << m_sendSuccess;
        accept(); //  只有外部真正保存成功了(或同意替换)，下一层窗口才关闭
    } else {
        qDebug() << "m_sendSuccess" << m_sendSuccess;
        // 外部拒绝了(用户点了“否”)，本窗口什么都不做，继续保持打开状态，让用户修改
    }
}

void DialogSetScene::send_config_result(bool success)
{
    m_sendSuccess = success;
}

uint8_t DialogSetScene::getAddrFromGroup(QGroupBox *group)
{
    if (!group)
        return 0; // 或者其他默认值/错误码

    QString title   = group->title(); // 获取标题
    QString addrStr = title.section(':', 1, 1).section(' ', 0, 0);
    bool ok         = false;
    int addr        = addrStr.toInt(&ok);
    if (!ok) return 0; // 转换失败返回默认值

    return static_cast<uint8_t>(addr);
}

void DialogSetScene::parseGroupBoxInfo(QGroupBox *group, uint8_t &addr, uint8_t &key_num, uint8_t &type)
{
    addr    = 0;
    key_num = 0;
    type    = 1; // 默认灯控面板

    if (!group) return;

    QString title = group->title(); // 获取标题

    // 正则匹配 "面板地址:1 按键数量:6 旋钮面板"
    const QRegularExpression rx("面板地址:(\\d+)\\s+按键数量:(\\d+)\\s+(.*)");
    const QRegularExpressionMatch match = rx.match(title);
    if (match.hasMatch()) {
        addr            = static_cast<uint8_t>(match.captured(1).toUInt());
        key_num         = static_cast<uint8_t>(match.captured(2).toUInt());
        QString typeStr = match.captured(3).trimmed();

        qDebug() << "typeStr" << typeStr;
        if (typeStr.contains("旋钮")) {
            type = KNOB; // 0
        } else if (typeStr.contains("灯控")) {
            type = PANEL; // 1
        }
    } else {
        qDebug() << "解析QGroupBox标题失败:" << title;
    }
}
