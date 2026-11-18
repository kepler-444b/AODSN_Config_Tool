#include "model_panel_knob.h"
#include "ui_model_panel_knob.h"

ModelPanelKnob::ModelPanelKnob(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ModelPanelKnob)
{
    ui->setupUi(this);
    m_buttons.clear();
    m_buttons.append(ui->key_1);
    m_buttons.append(ui->key_2);
    m_buttons.append(ui->key_3);
    m_buttons.append(ui->key_4);

    for (auto *const btn : std::as_const(m_buttons))
    {
        btn->setCheckable(true);
        btn->installEventFilter(this);
    }

    ui->frame_2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->frame_2, &QFrame::customContextMenuRequested, this, &ModelPanelKnob::onFrameRightClicked);

    m_lumTimer = new QTimer(this);
    m_lumTimer->setSingleShot(true);

    m_cctTimer = new QTimer(this);
    m_cctTimer->setSingleShot(true);

    connect(m_lumTimer, &QTimer::timeout, this, [this]() {
        build_panel_knob(2);
    });

    connect(m_cctTimer, &QTimer::timeout, this, [this]() {
        build_panel_knob(3);
    });
}

ModelPanelKnob::~ModelPanelKnob()
{
    delete ui;
}

// 修改按键名称
void ModelPanelKnob::SetKeyNames(const QStringList &names)
{
    int count = qMin(names.size(), m_buttons.size());
    for (int i = 0; i < count; ++i)
    {
        if (!names[i].isEmpty())
            m_buttons[i]->setText(names[i]);
    }
}

// 设置按钮状态
void ModelPanelKnob::SetPanelState(const QByteArray &data)
{
    uint8_t sub_idx  = m_addr / PANEL_FRAME_RX_ADDR_LEN; // 在哪个 sub_frame 中
    uint8_t addr_idx = m_addr % PANEL_FRAME_RX_ADDR_LEN; // 在该 sub_frame 中的第几个地址
    uint8_t sub_start = 4 + sub_idx * PANEL_FRAME_RX_SUB_LEN; // 子帧起始地址索引
    uint8_t addr    = data[sub_start + (addr_idx * 3)];       // 每个按键的状态

    m_status = addr ^ 0x3F;

    // 设置按键状态
    for (int i = 0; i < m_key_num; ++i) {
        int bit_val = (m_status >> i) & 1;
        bool status = !bit_val;

        int key_num = i + 1;
        QString buttonName = QString("key_%1").arg(key_num);
        QPushButton* btn = this->findChild<QPushButton*>(buttonName);

        if (btn != nullptr) {
            btn->setChecked(status); // 刷新界面状态
        }
    }
    // 设置滑块状态

    uint8_t lum = data[sub_start + (addr_idx * 3) + 1];
    uint8_t cct = data[sub_start + (addr_idx * 3) + 2];

    if (lum & 0x80)
    {
        m_lum = lum & 0x7F;;
        ui->SliderLum->setValue(m_lum);
    }
    if (cct & 0x80)
    {
        m_cct = cct & 0x7F;
        ui->SliderCct->setValue(m_cct);
    }
}

void ModelPanelKnob::SetPanelAddr(const uint8_t addr)
{
    ui->addr->setText(QString("旋钮面板地址:%1").arg(addr));
    m_addr = addr;
}

bool ModelPanelKnob::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() != QEvent::MouseButtonPress)
        return QWidget::eventFilter(obj, event);

    auto btn = qobject_cast<QPushButton*>(obj);
    if (!btn || !m_buttons.contains(btn))
        return QWidget::eventFilter(obj, event);

    auto e = static_cast<QMouseEvent*>(event);
    if (e->button() != Qt::RightButton)
        return QWidget::eventFilter(obj, event);

    int keyIndex = 0;
    QString objName = btn->objectName();
    if (objName.startsWith("key_"))
    {
        bool ok = false;
        // 使用 QStringView 截取从下标 4 开始的子串(无内存分配)
        int num = QStringView(objName).mid(4).toInt(&ok);
        if (ok && num >= 1 && num <= 6)
            keyIndex = num - 1;
    }

    QMenu menu(this);
    QAction *deleteAction = menu.addAction("删除该面板");
    QAction *renameAction = menu.addAction("修改按键别名");

    auto addSceneActions = [this](QMenu* parentMenu) {
        for (const auto &scene : std::as_const(m_sceneList))
        {
            QString text = QString("%1: %2").arg(scene.scene_id).arg(scene.scene_name);
            QAction *action = parentMenu->addAction(text);
            action->setData(QVariant::fromValue(scene.scene_id));
        }
    };

    QMenu *bindOpenMenu = menu.addMenu("绑定开场景");
    addSceneActions(bindOpenMenu);

    QMenu *bindCloseMenu = menu.addMenu("绑定关场景");
    addSceneActions(bindCloseMenu);

    // 弹出菜单并处理选择
    QAction *selected = menu.exec(e->globalPosition().toPoint());
    if (selected == renameAction)
    {
        bool ok;
        QString text = QInputDialog::getText(this, "修改按键名称", "请输入新的名称：", QLineEdit::Normal, btn->text(), &ok);
        if (ok && !text.isEmpty())
        {
            btn->setText(text);
            emit keyNameChanged(m_addr, keyIndex, text);
        }
    }
    else if (selected == deleteAction) // 删除面板
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认删除", "确定要删除该面板吗?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            emit requestDelete(m_addr);
        }
    }
    // 绑定开场景
    else if (selected && selected->parent() == bindOpenMenu)
    {
        uint8_t scene_id = selected->data().toUInt();
        // 4 键直接对应 keyIndex,无需遍历循环
        emit requestBindScene(m_addr, keyIndex, scene_id, true);
    }

    // 绑定关场景
    else if (selected && selected->parent() == bindCloseMenu)
    {
        uint8_t sceneId = selected->data().toUInt();
        emit requestBindScene(m_addr, keyIndex, sceneId, false);
    }
    return true; // 拦截事件
}


uint8_t ModelPanelKnob::frame_crc(uint8_t *rxbuf, uint8_t len)
{
    uint8_t i, sum = 0;
    for (i = 0; i < len; i++) sum = sum + rxbuf[i];
    return (0xff - sum + 1);
}


void ModelPanelKnob::on_key_1_clicked()
{
    ui->key_1->setChecked(!ui->key_1->isChecked()); // 状态回滚
    build_panel_frame(0);
}

void ModelPanelKnob::on_key_2_clicked()
{
    ui->key_2->setChecked(!ui->key_2->isChecked()); // 状态回滚
    build_panel_frame(1);
}

void ModelPanelKnob::on_key_3_clicked()
{
    ui->key_3->setChecked(!ui->key_3->isChecked()); // 状态回滚
    build_panel_frame(2);
}

void ModelPanelKnob::on_key_4_clicked()
{
    ui->key_4->setChecked(!ui->key_4->isChecked()); // 状态回滚
    build_panel_frame(3);
}

// 旋钮右键菜单
void ModelPanelKnob::onFrameRightClicked(const QPoint &pos)
{
    QMenu menu(this);

    auto addSceneActions = [this](QMenu* parentMenu) {
        for (const auto &scene : std::as_const(m_sceneList))
        {
            QString text = QString("%1: %2")
            .arg(scene.scene_id)
                .arg(scene.scene_name);

            QAction *action = parentMenu->addAction(text);
            action->setData(QVariant::fromValue(scene.scene_id));
        }
    };

    QAction *ctelLedsAction = menu.addAction("选择被控LED");

    QMenu *bindOpenMenu = menu.addMenu("绑定开场景");
    addSceneActions(bindOpenMenu);

    QMenu *bindCloseMenu = menu.addMenu("绑定关场景");
    addSceneActions(bindCloseMenu);

    QPoint globalPos = QCursor::pos();
    QAction *selected = menu.exec(globalPos);

    if (selected && selected->parent() == bindOpenMenu) // 旋钮绑定开场景
    {
        uint8_t scene_id = selected->data().toUInt();
        emit requestBindKnobScene(m_addr, scene_id, -1, 0, false);
    }
    else if (selected && selected->parent() == bindCloseMenu) // 旋钮绑定关场景
    {
        uint8_t scene_id = selected->data().toUInt();
        emit requestBindKnobScene(m_addr, -1, scene_id, 0, false);
    } else if(selected == ctelLedsAction)
    {
        showLedSelectDialog();
    }
}

// 选择被控LED
void ModelPanelKnob::showLedSelectDialog()
{
    int64_t ledData = 0;
    for (const auto &bind : std::as_const(m_ledSelect))
    {
        if (bind.bind_data.size() < 11) continue;
        if (static_cast<uint8_t>(bind.bind_data[0]) == m_addr)
        {
            memcpy(&ledData, bind.bind_data.constData() + 3, sizeof(ledData));
            break;
        }
    }

    QDialog dialog(this);
    dialog.setWindowTitle("选择被控LED");
    dialog.setFixedSize(350, 500);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(10);

    QVector<QVector<QCheckBox*>> checkList;
    QVBoxLayout *listLayout = new QVBoxLayout();
    listLayout->setSpacing(8);

    for (auto ledId : std::as_const(m_ledIdList))
    {
        QGroupBox *group =
            new QGroupBox(QString("LED扩展地址:%1").arg(ledId), &dialog);

        QHBoxLayout *groupLayout = new QHBoxLayout(group);
        groupLayout->setContentsMargins(5, 5, 5, 5);
        groupLayout->setSpacing(4);

        QVector<QCheckBox*> rowCheck;

        for (int ch = 0; ch < 8; ch++)
        {
            int bit = ledId * 8 + ch;

            QCheckBox *check = new QCheckBox(QString("%1").arg(bit), group);
            check->setLayoutDirection(Qt::RightToLeft);
            check->setFixedWidth(35);
            check->setChecked((static_cast<uint64_t>(ledData) & (uint64_t(1) << bit)) != 0);

            groupLayout->addWidget(check);
            rowCheck.append(check);
        }

        groupLayout->addStretch();
        checkList.append(rowCheck);
        listLayout->addWidget(group);
    }

    mainLayout->addLayout(listLayout);
    mainLayout->addStretch(1);

    // 居中的确定按钮
    QPushButton *okBtn = new QPushButton("确定", &dialog);
    okBtn->setFixedWidth(90);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(okBtn);
    btnLayout->addStretch();

    mainLayout->addLayout(btnLayout);

    // 点击确定,保存LED选择状态
    connect(okBtn, &QPushButton::clicked, &dialog, [&]()
            {
                // 清空原来的选择
                m_led_select = 0;

                // 根据LED扩展地址和通道保存选择状态
                for (int i = 0; i < m_ledIdList.size(); ++i)
                {
                    uint8_t ledId = m_ledIdList[i];
                    if (ledId >= 8)
                        continue;
                    for (int ch = 0; ch < 8; ++ch)
                    {
                        if (checkList[i][ch]->isChecked())
                        {
                            int bit = ledId * 8 + ch;

                            m_led_select |= (int64_t(1) << bit);
                        }
                    }
                }
                dialog.accept();
            });

    dialog.exec();
    emit requestBindKnobScene(m_addr, -1, -1, m_led_select, true);
}


void ModelPanelKnob::on_SliderLum_valueChanged(int value)
{
    ui->lum->setValue(value);
    m_lum = value;
    m_lumTimer->start(100);
}

void ModelPanelKnob::on_SliderCct_valueChanged(int value)
{
    ui->cct->setValue(value);
    m_cct = value;
    m_cctTimer->start(100);
}

// 构造面板通讯帧
void ModelPanelKnob::build_panel_frame(const uint8_t key_num)
{
    panel_frame_t panel_frame = {};

    panel_frame.panel_tx_head       = 0xAA;
    panel_frame.panel_tx_type       = 0x01;  // 0x01 按键上报数据
    panel_frame.panel_tx_length     = 0x06;
    panel_frame.panel_info.src_addr = m_addr;
    panel_frame.panel_info.level    = 0x00;
    panel_frame.panel_info.status   = m_status;
    panel_frame.panel_info.key_num  = key_num;
    panel_frame.panel_tx_crc = frame_crc(reinterpret_cast<uint8_t *>(&panel_frame.panel_info), 6);

    panel_frame.panel_tx_tail_1 = 0x0D;
    panel_frame.panel_tx_tail_2 = 0x0A;
    emit sendSimState(panel_frame);
}

// 构造面板通讯帧(旋钮)
void ModelPanelKnob::build_panel_knob(const uint8_t type)
{
    panel_frame_t panel_frame = {};

    panel_frame.panel_tx_head       = 0xAA;
    panel_frame.panel_tx_type       = type;  // 0x01 按键上报数据
    panel_frame.panel_tx_length     = 0x06;
    panel_frame.panel_info.src_addr = m_addr;
    panel_frame.panel_info.level    = 0x00;
    panel_frame.panel_info.status   = m_status;
    panel_frame.panel_info.key_num  = 0x00;
    panel_frame.panel_info.reserve_1  = m_lum;
    panel_frame.panel_info.reserve_2  = m_cct;
    panel_frame.panel_tx_crc = frame_crc(reinterpret_cast<uint8_t *>(&panel_frame.panel_info), 6);

    panel_frame.panel_tx_tail_1 = 0x0D;
    panel_frame.panel_tx_tail_2 = 0x0A;

    emit sendSimState(panel_frame);
}

