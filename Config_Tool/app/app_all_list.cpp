#include "app_all_list.h"
#include "ui_app_all_list.h"

AppAllList::AppAllList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppAllList)
{
    ui->setupUi(this);

    this->setWindowTitle("配置列表");
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(ui->scene_list);

}

AppAllList::~AppAllList()
{
    delete ui;
}


void AppAllList::setSceneData(const QVector<scene_save_t> &data)
{
    m_sceneInfo = data; // 接收外部数据

    // 删除旧控件和布局
    if (QLayout* oldLayout = ui->scene_list->layout()) {
        qDeleteAll(ui->scene_list->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));
        delete oldLayout;
    }

    // 创建新的布局
    QVBoxLayout *layout = new QVBoxLayout(ui->scene_list); // 垂直布局
    layout->setSpacing(3);  // 控件之间间距
    layout->setContentsMargins(0, 0, 0, 0);
    ui->scene_list->setLayout(layout);

    // 定义一个 Lambda 用于创建场景项
    auto createSceneItem = [this, layout](const scene_save_t &scene, int index) {
        QWidget *itemWidget = new QWidget(this);

        // 背景色 + 圆角
        QColor bgColor = (index % 2 == 0) ? QColor(230, 230, 230) : QColor(210, 210, 210);
        itemWidget->setStyleSheet(QString("QWidget {"
                                          "background-color: rgb(%1, %2, %3);"
                                          "border-radius: 4px;}").arg(bgColor.red())
                                  .arg(bgColor.green())
                                  .arg(bgColor.blue()));

        // 水平布局
        QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);
        itemLayout->setContentsMargins(4,2,4,2);
        itemLayout->setSpacing(10);

        // ID 标签
        QLabel *idLabel = new QLabel(QString("ID:%1").arg(scene.scene_id), this);
        itemLayout->addWidget(idLabel);

        // 别名
        QString alias = scene.scene_name.isEmpty() ? "NULL" : scene.scene_name;
        QLabel *aliasLabel = new QLabel(QString("别名:%1").arg(alias), this);
        aliasLabel->setAlignment(Qt::AlignLeft);
        aliasLabel->setFixedWidth(80); // 根据需要调整宽度
        itemLayout->addWidget(aliasLabel);

        // hexLine 数据
        QString hexLine;
        if (scene.scene_data.isEmpty()) {
            hexLine = "NULL";
        } else {
            for (auto b : scene.scene_data)
                hexLine += QString("%1").arg(static_cast<uint8_t>(b), 2, 16, QLatin1Char('0')).toUpper();
        }

        QLabel *dataLabel = new QLabel(hexLine, this);
        dataLabel->setAlignment(Qt::AlignLeft);
        dataLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        dataLabel->setFixedWidth(200);  // 固定宽度
        dataLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        itemLayout->addWidget(dataLabel);

        // 填充剩余空间
        itemLayout->addStretch();

        // 右键菜单
        itemWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(itemWidget, &QWidget::customContextMenuRequested, this, [this, scene, itemWidget](const QPoint &pos){
            QMenu menu;
            QAction *del = menu.addAction("删除场景");
            QAction *edit = menu.addAction("编辑场景");
            QAction *selectedAction = menu.exec(itemWidget->mapToGlobal(pos));
            if (selectedAction == del) {
                emit requestDeleteScene(scene.scene_id);
            }
            else if (selectedAction == edit) {
                emit requestEditScene(scene.scene_id);
            }
        });

        layout->addWidget(itemWidget);
    };
    int i = 0;
    for (const auto &scene : std::as_const(m_sceneInfo)) {
        createSceneItem(scene, i++);
    }

    layout->addStretch();
}

void AppAllList::setBindData(const QVector<bind_save_t> &data)
{
    m_bindInfo = data; // 接收外部数据

    // 删除旧控件和布局
    if (QLayout* oldLayout = ui->bind_list->layout()) {
        qDeleteAll(ui->bind_list->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));
        delete oldLayout;
    }

    // 创建新的布局
    QVBoxLayout *layout = new QVBoxLayout(ui->bind_list);
    layout->setSpacing(3);
    layout->setContentsMargins(0, 0, 0, 0);
    ui->bind_list->setLayout(layout);

    // Lambda 用于创建绑定项
    auto createBindItem = [this, layout](const bind_save_t &bind, int index) {
        QWidget *itemWidget = new QWidget(this);

        // 背景色交替
        QColor bgColor = (index % 2 == 0) ? QColor(230, 230, 230) : QColor(210, 210, 210);
        itemWidget->setStyleSheet(QString("QWidget {"
                                          "background-color: rgb(%1,%2,%3);"
                                          "border-radius: 4px;}").arg(bgColor.red())
                                  .arg(bgColor.green())
                                  .arg(bgColor.blue()));

        // 水平布局
        QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);
        itemLayout->setContentsMargins(4,2,4,2);
        itemLayout->setSpacing(10);

        // 从 bind_data 解析
        uint8_t addr = 0;
        uint8_t key_num = 0;
        uint8_t scene_id = 0;
        uint8_t key_state = false;

        if (bind.bind_data.size() >= 4) {
            addr      = static_cast<uint8_t>(bind.bind_data[0]);
            key_num   = static_cast<uint8_t>(bind.bind_data[1]);
            key_state = static_cast<uint8_t>(bind.bind_data[2]);
            scene_id  = static_cast<uint8_t>(bind.bind_data[3]);
        }

        // 面板地址
        QLabel *panelAddr = new QLabel(QString("设备地址:%1").arg(addr), this);
        itemLayout->addWidget(panelAddr);

        // 按键号
        QLabel *keyIdx = new QLabel(QString("按键号:%1").arg(key_num), this);
        itemLayout->addWidget(keyIdx);

        // 按键状态
        QString keyStateText = QString("按键状态:%1").arg(key_state ? "开启" : "关闭");
        QLabel *keyStateLabel = new QLabel(keyStateText, this);
        keyStateLabel->setFixedWidth(80);
        itemLayout->addWidget(keyStateLabel);

        // 场景ID
        QLabel *sceneIdLabel = new QLabel(QString("ID:%1").arg(scene_id), this);
        itemLayout->addWidget(sceneIdLabel);

        // 场景别名
        QString sceneText = bind.scene_name.isEmpty() ? "NULL" : bind.scene_name;
        QLabel *sceneLabel = new QLabel(QString("别名:%1").arg(sceneText), this);
        sceneLabel->setAlignment(Qt::AlignLeft);
        sceneLabel->setFixedWidth(80);
        itemLayout->addWidget(sceneLabel);

        itemLayout->addStretch();

        // 右键菜单
        itemWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(itemWidget, &QWidget::customContextMenuRequested, this, [this, bind, itemWidget](const QPoint &pos){
            QMenu menu;
            QAction *del = menu.addAction("删除绑定");
            if (menu.exec(itemWidget->mapToGlobal(pos)) == del) {
                emit requsetDeleteBind(bind);
            }
        });
        layout->addWidget(itemWidget);
    };

    int i = 0;
    for (const auto &bind : m_bindInfo) {
        createBindItem(bind, i++);
    }

    layout->addStretch();
}


void AppAllList::setBindKnobData(const QVector<bind_save_knob_t> &data)
{
    m_bindKnobInfo = data; // 接收外部数据

    // 删除旧控件和布局
    if (QLayout *oldLayout = ui->bind_knob_list->layout())
    {
        qDeleteAll(ui->bind_knob_list->findChildren<QWidget*>(
            QString(), Qt::FindDirectChildrenOnly));
        delete oldLayout;
    }

    // 创建新的布局
    QVBoxLayout *layout = new QVBoxLayout(ui->bind_knob_list);
    layout->setSpacing(3);
    layout->setContentsMargins(0, 0, 0, 0);
    ui->bind_knob_list->setLayout(layout);

    // Lambda 用于创建绑定项
    auto createBindItem = [this, layout](const bind_save_knob_t &bind, int index)
    {
        QWidget *itemWidget = new QWidget(this);

        // 背景色交替
        QColor bgColor = (index % 2 == 0)
                             ? QColor(230, 230, 230)
                             : QColor(210, 210, 210);

        itemWidget->setStyleSheet(
            QString("QWidget {"
                    "background-color: rgb(%1,%2,%3);"
                    "border-radius: 4px;}")
                .arg(bgColor.red())
                .arg(bgColor.green())
                .arg(bgColor.blue()));

        // 水平布局
        QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);
        itemLayout->setContentsMargins(4, 2, 4, 2);
        itemLayout->setSpacing(10);

        // 从 bind_data 解析
        uint8_t addr = 0;
        uint8_t open_id = 0xFF;
        uint8_t close_id = 0xFF;
        int64_t led_select = 0;

        if (bind.bind_data.size() >= 11)
        {
            addr = static_cast<uint8_t>(bind.bind_data[0]);
            open_id = static_cast<uint8_t>(bind.bind_data[1]);
            close_id = static_cast<uint8_t>(bind.bind_data[2]);

            memcpy(&led_select,
                   bind.bind_data.constData() + 3,
                   sizeof(led_select));
        }

        // 面板地址
        QLabel *panelAddr = new QLabel(
            QString("设备地址:%1").arg(addr),
            this);
        itemLayout->addWidget(panelAddr);

        // 开场景
        QString openSceneText = bind.open_scene_name.isEmpty()
                                    ? "NULL"
                                    : bind.open_scene_name;

        QLabel *openScene = new QLabel(
            QString("开场景:%1").arg(
                open_id == 0xFF
                    ? "FF"
                    : QString::number(open_id)),
            this);
        openScene->setFixedWidth(55);
        itemLayout->addWidget(openScene);

        // 开场景别名
        QLabel *openSceneLabel = new QLabel(
            QString("%1").arg(openSceneText),
            this);
        openSceneLabel->setAlignment(Qt::AlignLeft);
        openSceneLabel->setFixedWidth(50);
        itemLayout->addWidget(openSceneLabel);

        // 关场景
        QLabel *closeScene = new QLabel(
            QString("关场景:%1").arg(
                close_id == 0xFF
                    ? "FF"
                    : QString::number(close_id)),
            this);
        closeScene->setFixedWidth(55);
        itemLayout->addWidget(closeScene);

        // 关场景别名
        QString closeSceneText = bind.close_scene_name.isEmpty()
                                     ? "NULL"
                                     : bind.close_scene_name;

        QLabel *closeSceneLabel = new QLabel(
            QString("%1").arg(closeSceneText),
            this);
        closeSceneLabel->setAlignment(Qt::AlignLeft);
        closeSceneLabel->setFixedWidth(50);
        itemLayout->addWidget(closeSceneLabel);

        // LED选择
        QString ledText = "LED:";

        for (int i = 0; i < 8; ++i)
        {
            uint8_t byte = static_cast<uint8_t>(
                (static_cast<uint64_t>(led_select) >> (i * 8)) & 0xFF);

            ledText += QString("%1").arg(byte, 2, 16, QLatin1Char('0')).toUpper();
        }

        QLabel *ledSelect = new QLabel(ledText.trimmed(), this);
        ledSelect->setFixedWidth(180);
        itemLayout->addWidget(ledSelect);
        itemLayout->addStretch();

        // 右键菜单
        itemWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(itemWidget, &QWidget::customContextMenuRequested, this, [this, bind, itemWidget](const QPoint &pos){
            QMenu menu;
            QAction *del = menu.addAction("删除绑定");
            if (menu.exec(itemWidget->mapToGlobal(pos)) == del) {
                emit requsetDeleteBindKone(bind);
            }
        });
        layout->addWidget(itemWidget);
    };

    int i = 0;

    for (const auto &bind : m_bindKnobInfo)
    {
        createBindItem(bind, i++);
    }

    layout->addStretch();
}

// 下发扩展场景
void AppAllList::on_send_scene_clicked()
{
    emit requestSendSceneData();
}

// 下发面板场景
void AppAllList::on_send_panel_scene_clicked()
{
    emit requestSendPanelSceneData();
}

// 下发按键绑定
void AppAllList::on_send_bind_clicked()
{
    emit requestSendBindData();
}

// 下发旋钮绑定
void AppAllList::on_send_bind_knob_clicked()
{
    emit requestSendBindKnobData();
}

// 删除场景
void AppAllList::on_del_scene_clicked()
{
    emit requestClearSceneData();
}

// 删除按键绑定
void AppAllList::on_del_bind_clicked()
{
    emit requestClearBindData();
}

// 删除旋钮绑定
void AppAllList::on_del_bind_knob_clicked()
{
    emit requestClearBindKnobData();
}






