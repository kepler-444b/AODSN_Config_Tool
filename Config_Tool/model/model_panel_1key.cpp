#include "model_panel_1key.h"
#include "ui_model_panel_1key.h"

ModelPanel1Key::ModelPanel1Key(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelPanel1Key)
{
    ui->setupUi(this);
    m_buttons.clear();
    m_buttons.append(ui->key_1);
    for (auto *const btn : std::as_const(m_buttons))
    {
        btn->setCheckable(true);
        btn->installEventFilter(this);
    }
}

ModelPanel1Key::~ModelPanel1Key()
{
    delete ui;
}

void ModelPanel1Key::SetKeyNames(const QStringList &names)
{
    int count = qMin(names.size(), m_buttons.size());
    for (int i = 0; i < count; ++i)
    {
        if (!names[i].isEmpty())
            m_buttons[i]->setText(names[i]);
    }
}

void ModelPanel1Key::SetPanelState(const QByteArray &data)
{
    uint8_t sub_idx  = m_addr / PANEL_FRAME_RX_ADDR_LEN; // 在哪个 sub_frame 中
    uint8_t addr_idx = m_addr % PANEL_FRAME_RX_ADDR_LEN; // 在该 sub_frame 中的第几个地址
    uint8_t sub_start = 4 + sub_idx * PANEL_FRAME_RX_SUB_LEN; // 子帧起始地址索引

    uint8_t addr    = data[sub_start + (addr_idx * 2)];     // 每个按键的状态
    //    uint8_t reserve = data[sub_start + (addr_idx * 2) + 1]; // 保留/旋钮值

    //    uint8_t bl = data[sub_start + 16];    // 子帧背光
    //    uint8_t res_1 = data[sub_start + 17]; // 子帧保留1
    //    uint8_t res_2 = data[sub_start + 18]; // 子阵保留2

    m_status = addr ^ 0x3F;

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
}

void ModelPanel1Key::SetPanelAddr(const uint8_t addr)
{
    ui->addr->setText(QString("地址:%1").arg(addr));
    m_addr = addr;
}

bool ModelPanel1Key::eventFilter(QObject *obj, QEvent *event)
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
        // 使用 QStringView 截取从下标 4 开始的子串（无内存分配）
        int num = QStringView(objName).mid(4).toInt(&ok);
        if (ok && num >= 1 && num <= 6)
            keyIndex = num - 1;
    }
    // 3键到6键映射关系

    QList<int> hwIndices;
    switch (keyIndex) {
    case 0: hwIndices << 0 << 1 << 2 << 3 << 4 << 5; break; // 键1 -> 0, 1
    default: hwIndices << keyIndex;      // 其他 -> 保持原样
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
    if (selected == renameAction) // 修改别名
    {
        bool ok;
        QString text = QInputDialog::getText(this, "修改按键名称", "请输入新的名称：", QLineEdit::Normal, btn->text(), &ok);
        if (ok && !text.isEmpty())
        {
            btn->setText(text);
            emit keyNameChanged(m_addr, keyIndex, text);
        }
    }
    else if (selected == deleteAction) // 删除
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认删除", "确定要删除该面板吗?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            emit requestDelete(m_addr);
        }
    }
    // 绑定开场景
    // 绑定开场景
    // 绑定开场景
    else if (selected && selected->parent() == bindOpenMenu)
    {
        uint8_t scene_id = selected->data().toUInt();

        for (int idx : std::as_const(hwIndices)) {
            emit requestBindScene(m_addr, idx, scene_id, true);
        }
    }

    // 绑定关场景
    else if (selected && selected->parent() == bindCloseMenu)
    {
        uint8_t sceneId = selected->data().toUInt();

        for (int idx : std::as_const(hwIndices)) {
            emit requestBindScene(m_addr, idx, sceneId, false);
        }
    }

    return true; // 拦截事件
}

void ModelPanel1Key::on_key_1_clicked()
{
    ui->key_1->setChecked(!ui->key_1->isChecked()); // 状态回滚
    bulid_panel_frame(0);
}

void ModelPanel1Key::bulid_panel_frame(const uint8_t key_num)
{
    panel_frame_t panel_frame = {};

    panel_frame.panel_tx_head       = 0xAA;
    panel_frame.panel_tx_type       = 0x01;
    panel_frame.panel_tx_length     = 0x06;
    panel_frame.panel_info.src_addr = m_addr;
    panel_frame.panel_info.level    = 0x00;
    panel_frame.panel_info.status   = m_status;
    panel_frame.panel_info.key_num  = key_num;

    emit sendSimState(panel_frame);
}
