#include "app_sel_set_scene.h"
#include "ui_app_sel_set_scene.h"
#include <QRegularExpression>

DialogSetScene::DialogSetScene(const QVector<PanelInfo_t>& panels,
                               const QVector<ExtendInfo_t>& extends,
                               const uint8_t scene_id,
                               const QString scene_name,
                               QWidget *parent) :
    QDialog(parent),
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

void DialogSetScene::populatePanels()
{
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->sel_panel->layout()); // 总布局,垂直排列
    if (!layout) return;

    layout->setSpacing(10);                 // 面板之间的垂直间距
    layout->setContentsMargins(5, 5, 5, 5); // 设置该垂直布局的外边距

    for (const PanelInfo_t& panel : std::as_const(m_panels))
    {
        QGroupBox* group = new QGroupBox(QString("面板地址:%1 按键数量:%2 %3").arg(panel.addr).arg(panel.key_num).arg(panel.type == 0 ? "旋钮面板" : "灯控面板"));
        QHBoxLayout* groupLayout = new QHBoxLayout(); // 面板内部横向排列
        groupLayout->setContentsMargins(5, 0, 0, 0);
        groupLayout->setSpacing(5);

        for (int i = 0; i < panel.key_num; ++i)  // 根据面板的按键数量,逐个创建按键控件
        {
            QString name = panel.key_name[i];
            if (name.isEmpty())
                name = QString("键%1").arg(i + 1); // 如果按键名为空,则设置一个兜底名"键X"


            QWidget* groupWidget = new QWidget();                   // 创建一个组控件,包含每个按键的"使能+状态"
            QHBoxLayout* keyLayout = new QHBoxLayout(groupWidget);  // 为这个组控件创建一个内部的水平布局
            keyLayout->setContentsMargins(1, 1, 1, 1);              // 子控件紧凑
            keyLayout->setSpacing(1);                               // "使能"与"状态"之间的距离

            QCheckBox* enableBox = new QCheckBox(name);        // 创建"使能"复选框
            enableBox->setLayoutDirection(Qt::RightToLeft);    // 文字在左,复选框在右
            QCheckBox* stateBox = new QCheckBox;               // 创建"状态"复选框

            bool isEnable = false;
            if (i < panel.key_enable.size()) {   // 提取使能数据
                isEnable = panel.key_enable[i];
                enableBox->setChecked(isEnable);
            }

            bool isState = false;
            if (i < panel.key_state.size()) {  // 提取状态数据
                isState = panel.key_state[i];
                stateBox->setChecked(isState);
            }

            stateBox->setEnabled(enableBox->isChecked()); // 建立信号槽与控件挂载,如果"使能"没有勾选,则"状态"不可勾选
            QObject::connect(enableBox, &QCheckBox::toggled, stateBox, &QCheckBox::setEnabled); // 连接信号槽

            keyLayout->addWidget(enableBox);     // 将"使能"复选框放入keyLayout布局
            keyLayout->addWidget(stateBox);      // 将"状态"复选框放入keyLayout布局
            groupLayout->addWidget(groupWidget); // 将打包好的一组按键控件,放入到当前的水平布局中
        }

        groupLayout->addStretch();      // 剩余空间留空
        group->setLayout(groupLayout);  // 将布局应用到group
        layout->addWidget(group);       // 将整个面板放到最外层的垂直布局中
    }

    layout->addStretch();
}

void DialogSetScene::populateLeds()
{
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->sel_led->layout()); // 总布局,垂直排列
    if (!layout) return;

    layout->setSpacing(10);
    layout->setContentsMargins(5, 5, 5, 5);
    for (const ExtendInfo_t& ex : std::as_const(m_extends))
    {
        if (ex.type != LED_EX)
            continue;

        QGroupBox* group = new QGroupBox(QString("LED扩展地址:%1").arg(ex.id));
        QHBoxLayout* groupLayout = new QHBoxLayout(); // 面板内部横向排列
        groupLayout->setContentsMargins(5, 0, 0, 0);
        groupLayout->setSpacing(5);

        for (int i = 0; i < 8; ++i) // 每个LED扩展固定8个通道,逐个创建通道控件
        {
            QString name = QString("%1").arg(i + 1);

            QWidget* groupWidget = new QWidget();                   // 创建一个组控件,包含每个通道的"使能+亮度"
            QHBoxLayout* ledLayout = new QHBoxLayout(groupWidget);  // 为这个组控件创建一个内部的水平布局
            ledLayout->setContentsMargins(1, 1, 1, 1);              // 子控件紧凑
            ledLayout->setSpacing(1);                               // "使能"与"亮度"之间的距离

            QCheckBox* enableBox = new QCheckBox(name);        // 创建"使能"复选框
            enableBox->setLayoutDirection(Qt::RightToLeft);    // 文字在左,复选框在右
            enableBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

            QLineEdit* inputBox = new QLineEdit();             // 创建"亮度输入"文本框
            inputBox->setFixedWidth(25);                       // 固定输入框宽度
            inputBox->setValidator(new QIntValidator(0, 100, inputBox)); // 限制输入0~100的正整数
            inputBox->setAlignment(Qt::AlignCenter);           // 文字居中输入

            bool isEnable = false;
            if (i < ex.led_enable.size()) {   // 提取使能数据
                isEnable = ex.led_enable[i];
                enableBox->setChecked(isEnable);
            } else {
                enableBox->setChecked(false); // 容错兜底
            }

            int currentVal = 0;
            if (i < ex.led_value.size()) {    // 提取亮度状态数据
                currentVal = ex.led_value[i];
                inputBox->setText(QString::number(currentVal));
            } else {
                inputBox->setText("0");       // 容错兜底
            }

            inputBox->setEnabled(enableBox->isChecked()); // 建立信号槽与控件挂载,如果"使能"没有勾选,则"亮度"不可输入
            QObject::connect(enableBox, &QCheckBox::toggled, inputBox, &QLineEdit::setEnabled); // 连接信号槽

            ledLayout->addWidget(enableBox);     // 将"使能"复选框放入ledLayout布局
            ledLayout->addWidget(inputBox);      // 将"亮度"输入框放入ledLayout布局
            groupLayout->addWidget(groupWidget); // 将打包好的一组通道控件,放入到当前的水平布局中
        }

        groupLayout->addStretch();      // 剩余空间留空
        group->setLayout(groupLayout);  // 将布局应用到group
        layout->addWidget(group);       // 将整个面板放到最外层的垂直布局中
    }

    layout->addStretch(); // 底部留白
}

void DialogSetScene::populateRelays()
{
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->sel_relay->layout()); // 总布局,垂直排列
    if (!layout) return;

    layout->setSpacing(10);
    layout->setContentsMargins(5, 5, 5, 5); // 设置该垂直布局的外边距

    for (const ExtendInfo_t& ex : std::as_const(m_extends))
    {
        if (ex.type != RELAY_EX)
            continue;

        QGroupBox* group = new QGroupBox(QString("继电器扩展地址:%1").arg(ex.id));
        QHBoxLayout* groupLayout = new QHBoxLayout(); // 面板内部横向排列
        groupLayout->setContentsMargins(5, 0, 0, 0);
        groupLayout->setSpacing(4);                   // 每一个继电器单元之间的水平间距

        for (int i = 0; i < 15; ++i) // 每个继电器扩展固定15个通道,逐个创建通道控件
        {
            QString name = QString("%1").arg(i + 1);

            QWidget* groupWidget = new QWidget();                    // 创建一个组控件,包含每个通道的"使能+状态"
            QHBoxLayout* relayLayout = new QHBoxLayout(groupWidget); // 为这个组控件创建一个内部的水平布局
            relayLayout->setContentsMargins(1, 1, 1, 1);             // 子控件紧凑
            relayLayout->setSpacing(1);                              // "使能"与"状态"之间的距离

            QCheckBox* enableBox = new QCheckBox(name);        // 创建"使能"复选框
            enableBox->setLayoutDirection(Qt::RightToLeft);    // 文字在左,复选框在右
            enableBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

            QCheckBox* stateBox = new QCheckBox;               // 创建"状态"复选框
            stateBox->setLayoutDirection(Qt::RightToLeft);     // 文字在左,复选框在右

            bool isEnable = false;
            if (i < ex.relay_enable.size()) {
                isEnable = ex.relay_enable[i];
                enableBox->setChecked(isEnable);
            } else {
                enableBox->setChecked(false); // 容错兜底
            }

            bool isState = false;
            if (i < ex.relay_state.size()) {
                isState = ex.relay_state[i];
                stateBox->setChecked(isState);
            } else {
                stateBox->setChecked(false); // 容错兜底
            }

            stateBox->setEnabled(enableBox->isChecked()); // 建立信号槽与控件挂载,如果"使能"没有勾选,则"状态"不可勾选
            QObject::connect(enableBox, &QCheckBox::toggled, stateBox, &QCheckBox::setEnabled); // 连接信号槽

            relayLayout->addWidget(enableBox);     // 将"使能"复选框放入relayLayout布局
            relayLayout->addWidget(stateBox);      // 将"状态"复选框放入relayLayout布局
            groupLayout->addWidget(groupWidget);   // 将打包好的一组通道控件,放入到当前的水平布局中
        }

        groupLayout->addStretch();      // 剩余空间留空
        group->setLayout(groupLayout);  // 将布局应用到group
        layout->addWidget(group);       // 将整个面板放到最外层的垂直布局中
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
    QVector<led_data_t>   ledsResult;
    QVector<relay_data_t> relayResult;

    uint8_t scene_id   = static_cast<uint8_t>(ui->spinBox->value()); // 获取UI上的场景id
    QString scene_name = ui->scene_name->text();                     // 获取UI上的场景别名

    QVBoxLayout* panelLayout = qobject_cast<QVBoxLayout*>(ui->sel_panel->layout()); // 取得UI上存放面板的布局
    if (panelLayout)
    {
        int panelIdx = 0;
        for (int i = 0; i < panelLayout->count(); ++i)  // 遍历布局里的每一项
        {
            QLayoutItem* item = panelLayout->itemAt(i); // 取出垂直布局中的第i个条目
            if (!item) continue;
            QGroupBox* group = qobject_cast<QGroupBox*>(item->widget()); // 将这个条目转换为QGroupBox
            if (!group) continue;

            panel_data_t pdata; // 新建一个面板结构体
            parseGroupBoxInfo(group, pdata.addr, pdata.key_num, pdata.type);


            QHBoxLayout* groupLayout = qobject_cast<QHBoxLayout*>(group->layout()); // 获取group内部布局
            if (!groupLayout) continue;

            for (int j = 0; j < groupLayout->count(); ++j)     // 遍历内部的每一个条目
            {
                QLayoutItem* keyItem = groupLayout->itemAt(j); // 取出第j个条目
                if (!keyItem) continue;
                QWidget* keyWidget = keyItem->widget();        // 返回控件指针
                if (!keyWidget) continue;

                QHBoxLayout* keyLayout = qobject_cast<QHBoxLayout*>(keyWidget->layout()); // 每个keyWidget都是 按键+状态的组合
                if (!keyLayout) continue;

                QCheckBox* enable = qobject_cast<QCheckBox*>(keyLayout->itemAt(0)->widget());   // 取出按键使能
                QCheckBox* state  = qobject_cast<QCheckBox*>(keyLayout->itemAt(1)->widget());   // 取出按键状态
                pdata.key_name[j] = enable->text();

                if (enable) pdata.key_enable.append(enable->isChecked()); // 保存按键使能
                if (state) pdata.key_state.append(state->isChecked());    // 保存按键状态
            }
            panelsResult.append(pdata); // 将此面板的数据放入panelsResult
            panelIdx++;
        }
    }

    // LED扩展数据
    QVBoxLayout* ledLayout = qobject_cast<QVBoxLayout*>(ui->sel_led->layout());
    if (ledLayout)
    {
        int ledIdx = 0;
        for (int i = 0; i < ledLayout->count(); ++i)    // 遍历布局里的每一项
        {
            QLayoutItem* item = ledLayout->itemAt(i);   // 取出垂直布局中的第i个条目
            if (!item) continue;
            QGroupBox* group = qobject_cast<QGroupBox*>(item->widget());    // 将这个条目转换为QGroupBox
            if (!group) continue;

            led_data_t ldata;   // 新建一个led扩展结构体
            ldata.addr = getAddrFromGroup(group); // 填充产品地址

            QHBoxLayout* groupLayout = qobject_cast<QHBoxLayout*>(group->layout()); // 获取group内部布局
            if (!groupLayout) continue;

            for (int j = 0; j < groupLayout->count(); ++j)      // 遍历内部的每一个条目
            {
                QLayoutItem* chItem = groupLayout->itemAt(j);   // 取出第j个条目
                if (!chItem) continue;
                QWidget* chWidget = chItem->widget();           // 返回控件指针
                if (!chWidget) continue;
                QHBoxLayout* chLayout = qobject_cast<QHBoxLayout*>(chWidget->layout()); // 每个chLayout都是 使能+亮度的组合
                if (!chLayout) continue;

                QCheckBox* enable = qobject_cast<QCheckBox*>(chLayout->itemAt(0)->widget());
                QLineEdit* value = qobject_cast<QLineEdit*>(chLayout->itemAt(1)->widget());

                if (enable) ldata.led_enabled.append(enable->isChecked()); // 保存led使能
                if (value) ldata.led_value.append(value->text().toInt());  // 保存led亮度
            }

            ledsResult.append(ldata);
            ledIdx++;
        }
    }
    // 继电器扩展数据
    QVBoxLayout* relayLayout = qobject_cast<QVBoxLayout*>(ui->sel_relay->layout());
    if (relayLayout)
    {
        int relayIdx = 0;
        for (int i = 0; i < relayLayout->count(); ++i)    // 遍历布局里的每一项
        {
            QLayoutItem* item = relayLayout->itemAt(i);   // 取出垂直布局中的第i个条目
            if (!item) continue;
            QGroupBox* group = qobject_cast<QGroupBox*>(item->widget());    // 将这个条目转换为QGroupBox
            if (!group) continue;

            relay_data_t rdata;   // 新建一个继电器扩展结构体
            rdata.addr = getAddrFromGroup(group); // 填充产品地址

            QHBoxLayout* groupLayout = qobject_cast<QHBoxLayout*>(group->layout()); // 获取group内部布局
            if (!groupLayout) continue;

            for (int j = 0; j < groupLayout->count(); ++j)      // 遍历内部的每一个条目
            {
                QLayoutItem* chItem = groupLayout->itemAt(j);   // 取出第j个条目
                if (!chItem) continue;
                QWidget* chWidget = chItem->widget();           // 返回控件指针
                if (!chWidget) continue;
                QHBoxLayout* chLayout = qobject_cast<QHBoxLayout*>(chWidget->layout()); // 每个chLayout都是 使能+状态
                if (!chLayout) continue;

                QCheckBox* enable = qobject_cast<QCheckBox*>(chLayout->itemAt(0)->widget());
                QCheckBox* state = qobject_cast<QCheckBox*>(chLayout->itemAt(1)->widget());

                if (enable) rdata.relay_enabled.append(enable->isChecked()); // 保存继电器使能
                if (state) rdata.relay_state.append(state->isChecked());     // 保存继电器状态
            }

            relayResult.append(rdata);
            relayIdx++;
        }
    }

    emit send_config(panelsResult, ledsResult, relayResult, scene_id, scene_name); // 通过信号发送数据

    // 根据外部槽函数修改后的结果,决定是否关闭本窗口
    if (m_sendSuccess)
    {
        qDebug() << "m_sendSuccess" << m_sendSuccess;
        accept(); //  只有外部真正保存成功了(或同意替换)，下一层窗口才关闭
    }
    else
    {
        qDebug() << "m_sendSuccess" << m_sendSuccess;
        // 外部拒绝了(用户点了“否”)，本窗口什么都不做，继续保持打开状态，让用户修改
    }
}

void DialogSetScene::on_send_config_result(bool success)
{
    m_sendSuccess = success;
}

uint8_t  DialogSetScene::getAddrFromGroup(QGroupBox* group)
{
    if (!group)
        return 0; // 或者其他默认值/错误码

    QString title = group->title(); // 获取标题
    QString addrStr = title.section(':', 1, 1).section(' ', 0, 0);
    bool ok = false;
    int addr = addrStr.toInt(&ok);
    if (!ok) return 0; // 转换失败返回默认值

    return static_cast<uint8_t>(addr);
}

void DialogSetScene::parseGroupBoxInfo(QGroupBox* group, uint8_t &addr, uint8_t &key_num, uint8_t &type)
{
    addr = 0;
    key_num = 0;
    type =1; // 默认灯控面板

    if (!group) return;

    QString title = group->title(); // 获取标题

    // 正则匹配 "面板地址:1 按键数量:6 旋钮面板"
    const QRegularExpression rx("面板地址:(\\d+)\\s+按键数量:(\\d+)\\s+(.*)");
    const QRegularExpressionMatch match = rx.match(title);
    if (match.hasMatch())
    {
        addr = match.captured(1).toInt();
        key_num = match.captured(2).toInt();
        QString typeStr = match.captured(3).trimmed();

        if (typeStr == "旋钮面板") {
            type = 0;
        } else {
            type = 1; // 默认为灯控面板
        }
    }
    else
    {
        qDebug() << "解析QGroupBox标题失败:" << title;
    }
}
