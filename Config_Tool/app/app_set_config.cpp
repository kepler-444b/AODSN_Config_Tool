#include "app_set_config.h"
#include "ui_app_set_config.h"
#include "model/model_panel_1key.h"
#include "model/model_panel_2key.h"
#include "model/model_panel_3key.h"
#include "model/model_panel_4key.h"
#include "model/model_panel_6key.h"
#include "model/model_led_ex.h"
#include "model/model_relay_ex.h"


AppSetConfig::AppSetConfig(QWidget *parent, AppSerial* serialWidget) :
    QWidget(parent),
    ui(new Ui::AppSetConfig)
{
    ui->setupUi(this);                                                       // 将 .ui 文件中设计的控件部署到当前类上
    m_serialWidget = serialWidget;

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);     // 设置伸缩策略
    ui->scrollArea->setWidgetResizable(true);                                // 设置滚动区域
    m_flowLayout = new FlowLayout(ui->scrollAreaWidgetContents, 10, 10, 10); // 初始化流式布局管理器

    m_protocol_set_config = new AppProtocolSetConfig(this, m_serialWidget);   // 创建协议数据实例
    m_protocol_sim_state  = new AppProtocolSimState(this, m_protocol_set_config, m_serialWidget);

    CreateListWindow(); // 创建场景列表
    connect(m_serialWidget, &AppSerial::sigRecvPanelData, m_protocol_sim_state, &AppProtocolSimState::RecvPanelFrame, Qt::UniqueConnection);
    connect(m_serialWidget, &AppSerial::sigRecvData, m_protocol_set_config, &AppProtocolSetConfig::recv_serial_data, Qt::UniqueConnection);
    connect(m_sceneListWidget, &AppAllList::requestDeleteScene, m_protocol_set_config, &AppProtocolSetConfig::deleteScene);
    connect(m_sceneListWidget, &AppAllList::requsetDeleteBind, m_protocol_set_config, &AppProtocolSetConfig::deleteBind);

    QTimer::singleShot(100, this, &AppSetConfig::autoLoadAllData);         // 加载上次保存的配置
    QShortcut* shortcutSave = new QShortcut(QKeySequence("Ctrl+S"), this); // ctrl + s 触发保存快捷键
    connect(shortcutSave, &QShortcut::activated, this, &AppSetConfig::on_save_data_clicked);
}

AppSetConfig::~AppSetConfig()
{
    delete ui;
}

// 添加面板
void AppSetConfig::on_add_panel_clicked()
{
    if (!m_panelSelDialog)
    {
        m_panelSelDialog = new DialogPanel(this);
    }

    m_panelSelDialog->SetPanelInfo(m_lastPanelInfo);

    if (m_panelSelDialog->exec() != QDialog::Accepted)
        return;

    PanelInfo_t info = m_panelSelDialog->GetPanelInfo();

    if (IsPanelIdExist(info.addr))
    {
        QMessageBox::warning(this, "警告", "地址已存在,请重新设置");
        return;
    }

    if (m_panelCount >= MAX_PANEL)
    {
        qDebug() << "数组已满";
        return;
    }

    QWidget* panelWidget = CreatePanelWidget(info);
    if (!panelWidget)
        return;

    AddToLayout(panelWidget);

    // 保存数据
    m_panelArray[m_panelCount] = info;
    m_panelCount++;
    m_lastPanelInfo = info;
    m_ui_Changed = true;
}

// 添加扩展
void AppSetConfig::on_add_extend_clicked()
{
    if (!m_extendSelDialog)
    {
        m_extendSelDialog = new DialogExtend(this);
    }
    m_extendSelDialog->SetExtendInfo(m_lastExtendInfo);
    if (m_extendSelDialog->exec() != QDialog::Accepted)
        return;

    ExtendInfo_t info = m_extendSelDialog->GetExtendInfo();
    if (IsExtendLedExist(&info))
    {
        QMessageBox::warning(this, "警告", "地址已存在,请重新设置");
        return;
    }

    if (info.type == LED_EX) {
        if (m_ledCount >= MAX_LED) return;
        m_ledArray[m_ledCount++] = info;
    }
    else if (info.type == RELAY_EX) {
        if (m_relayCount >= MAX_RELAY) return;
        m_relayArray[m_relayCount++] = info;
    }

    QWidget* extendWidget = CreateExtendWidget(info);
    if (!extendWidget) return;

    AddToLayout(extendWidget);

    m_lastExtendInfo = info;
    m_ui_Changed = true;
}

// 点击"创建场景"按钮
void AppSetConfig::on_set_scene_clicked()
{
    create_scene(-1);
}

// 创建场景
void AppSetConfig::create_scene(int id)
{
    bool is_edit = (id != -1);

    QString scene_name = "NULL";

    QVector<PanelInfo_t> panelList;
    QVector<ExtendInfo_t> extendlist;

    uint8_t scene_id = m_protocol_set_config->getAllConfigData().scene.size(); // 获取场景数量,场景ID自动递增

    for (int i = 0; i < m_panelCount; ++i)
        panelList.append(m_panelArray[i]);

    for (int i = 0; i < m_ledCount; i++)
    {
        if (m_ledArray[i].type == LED_EX)
            extendlist.append(m_ledArray[i]);
    }
    for (int i = 0; i <m_relayCount; i++)
    {
        if (m_relayArray[i].type == RELAY_EX)
            extendlist.append(m_relayArray[i]);
    }

    if (is_edit) // 是编辑场景
    {
        config_data_t temp = m_protocol_set_config->getSceneConfigDataById(id);

        scene_id   = temp.scene[0].scene_id;
        scene_name = temp.scene[0].scene_name;

        for (auto& panel : panelList)
        {
            auto it = std::find_if(temp.panel.begin(), temp.panel.end(), [&panel](const panel_save_t& savedPanel) {
                return panel.addr == savedPanel.panel_addr;
            });

            if (it != temp.panel.end())
            {
                panel.key_enable = it->key_enable;
                panel.key_state  = it->key_state;
            }
        }
        for (auto& extend : extendlist)
        {
            if (extend.type == ExtendType::LED_EX)
            {
                auto it = std::find_if(temp.led_ex.begin(), temp.led_ex.end(), [&extend](const led_save_t& savedLed) {
                    return extend.id == savedLed.led_addr;
                });

                if (it != temp.led_ex.end())
                {
                    extend.led_enable = it->led_enable;
                    extend.led_value  = it->led_value;
                }
            }
            else if (extend.type == ExtendType::RELAY_EX)
            {
                auto it = std::find_if(temp.relay_ex.begin(), temp.relay_ex.end(), [&extend](const relay_save_t& savedRelay) {
                    return extend.id == savedRelay.relay_addr;
                });

                if (it != temp.relay_ex.end())
                {
                    extend.relay_enable = it->relay_enable;
                    extend.relay_state  = it->relay_state;
                }
            }
        }
    }

    if (m_set_sceneDialog)
    {
        delete m_set_sceneDialog;
        m_set_sceneDialog = nullptr;
    }

    m_set_sceneDialog = new DialogSetScene(panelList, extendlist, scene_id, scene_name, nullptr);
    connect(m_set_sceneDialog, &DialogSetScene::send_config, m_protocol_set_config, &AppProtocolSetConfig::recv_scene_data);                  // 连接信号,到prorocol_set_config中处理
    connect(m_protocol_set_config, &AppProtocolSetConfig::recv_scene_data_result, m_set_sceneDialog, &DialogSetScene::on_send_config_result); // 连接信号,到prorocol_set_config中处理
    m_set_sceneDialog->show();
}

template<typename PanelBase>
QWidget* AppSetConfig::CreateSetupPanel(const PanelInfo_t& info)
{
    auto panel = new PanelBase(this); // 根据传入的类型创建对象
    panel->SetPanelAddr(info.addr);

    // 连接信号
    connect(panel, &PanelBase::requestDelete, this, &AppSetConfig::RemovePanel);
    connect(panel, &PanelBase::keyNameChanged, this, &AppSetConfig::UpdatePanelKeyName);
    connect(panel, &PanelBase::requestBindScene, m_protocol_set_config, &AppProtocolSetConfig::recv_bind_data);      // 连接信号,处理绑定信息
    connect(m_protocol_set_config, &AppProtocolSetConfig::sceneListChanged, panel, &PanelBase::updateSceneList);      // 连接信号,当场景更新时,发送给PanelBase
    panel->updateSceneList(m_protocol_set_config->getAllConfigData().scene);                                          // PanelBase在创建时,主动获取场景列表

    connect(panel, &PanelBase::sendSimState ,m_protocol_sim_state, &AppProtocolSimState::RecvSimPanelData);
    connect(m_protocol_sim_state, &AppProtocolSimState::SendPanelData, panel, &PanelBase::SetPanelState);


    // 设置按键名称
    QStringList names;
    for (int i = 0; i < 6; ++i) {
        names.append(info.key_name[i]);
    }
    panel->SetKeyNames(names);
    return panel;
}


// 创建 panel
QWidget* AppSetConfig::CreatePanelWidget(const PanelInfo_t& info)
{
    switch (info.key_num)
    {
    case 1: return CreateSetupPanel<ModelPanel1Key>(info);
    case 2: return CreateSetupPanel<ModelPanel2Key>(info);
    case 3: return CreateSetupPanel<ModelPanel3Key>(info);
    case 4: return CreateSetupPanel<ModelPanel4Key>(info);
    case 6: return CreateSetupPanel<ModelPanel6Key>(info);
    default:
        qDebug() << "不支持的按键数量:" << info.key_num;
        return nullptr;
    }
}


// 创建扩展
QWidget* AppSetConfig::CreateExtendWidget(const ExtendInfo_t& info)
{

    if (info.type == LED_EX)
    {
        auto extend = new ModelLedEx(this);
        extend->SetExtendAddr(info.id, info.type);
        connect(extend, &ModelLedEx::requestDelete, this, &AppSetConfig::RemoveExtend);
        connect(m_protocol_sim_state, &AppProtocolSimState::SendExtendData, extend, &ModelLedEx::SetExtendSatae);
        return extend;
    }
    else if (info.type == RELAY_EX)
    {
        auto extend = new ModelRelayEx(this);
        extend->SetExtendAddr(info.id, info.type);
        connect(extend, &ModelRelayEx::requestDelete, this, &AppSetConfig::RemoveExtend);
        connect(m_protocol_sim_state, &AppProtocolSimState::SendExtendData, extend, &ModelRelayEx::SetExtendSatae);
        return extend;
    }
    return nullptr;
}


// 添加到布局
void AppSetConfig::AddToLayout(QWidget* Widget)
{
    if (!Widget)
        return;
    m_flowLayout->addWidget(Widget);
}

// 删除 panel
void AppSetConfig::RemovePanel(uint8_t id)
{
    // 利用 Qt 的信号发送者机制,直接拿到触发删除的那个 Widget 指针
    QWidget* w = qobject_cast<QWidget*>(sender());
    if (!w) return;
    m_ui_Changed = true;
    // 从布局中移除并销毁
    m_flowLayout->removeWidget(w);
    w->deleteLater();

    // 同步清理底层数据数组
    for (int i = 0; i < m_panelCount; i++)
    {
        if (m_panelArray[i].addr == id)
        {
            for (int j = i; j < m_panelCount - 1; j++)
                m_panelArray[j] = m_panelArray[j + 1];
            m_panelCount--;
            break;
        }
    }
    qDebug() << "删除panel id:" << id;
}

// 删除扩展
void AppSetConfig::RemoveExtend(uint8_t id, ExtendType type)
{
    QWidget* w = qobject_cast<QWidget*>(sender());
    if (!w) return;
    m_ui_Changed = true;
    m_flowLayout->removeWidget(w);
    w->deleteLater();

    if (type == LED_EX) {
        for (int i = 0; i < m_ledCount; i++) {
            if (m_ledArray[i].id == id) {
                for (int j = i; j < m_ledCount - 1; j++) m_ledArray[j] = m_ledArray[j + 1];
                m_ledCount--; break;
            }
        }
    }
    else if (type == RELAY_EX) {
        for (int i = 0; i < m_relayCount; i++) {
            if (m_relayArray[i].id == id) {
                for (int j = i; j < m_relayCount - 1; j++) m_relayArray[j] = m_relayArray[j + 1];
                m_relayCount--; break;
            }
        }
    }
}

// 修改别名
void AppSetConfig::UpdatePanelKeyName(uint8_t panelId, int keyIndex, const QString& newAlias)
{
    if (keyIndex < 0 || keyIndex >= 6)
        return;

    // 更新 m_panelArray 中的数据
    for (int i = 0; i < m_panelCount; ++i)
    {
        if (m_panelArray[i].addr == panelId)
        {
            m_panelArray[i].key_name[keyIndex] = newAlias;
            m_ui_Changed = true;
            qDebug() << QString("更新面板 %1 的按键 %2 别名: %3").arg(panelId).arg(keyIndex+1).arg(newAlias);
            return;
        }
    }
    qDebug() << "未找到面板ID:" << panelId;
}

// id是否存在
bool AppSetConfig::IsPanelIdExist(uint8_t id) const
{
    for (int i = 0; i < m_panelCount; ++i) {
        if (m_panelArray[i].addr == id) {
            return true;
        }
    }
    return false;
}

bool AppSetConfig::IsExtendLedExist(ExtendInfo_t *info) const
{
    if (info->type == LED_EX) {
        for (int i = 0; i < m_ledCount; ++i) {
            if (m_ledArray[i].id == info->id) return true;
        }
    }
    else if (info->type == RELAY_EX) {
        for (int i = 0; i < m_relayCount; ++i) {
            if (m_relayArray[i].id == info->id) return true;
        }
    }
    return false;
}


// 创建场景列表
void AppSetConfig::CreateListWindow()
{
    if (!m_sceneListWidget)
    {
        m_sceneListWidget = new AppAllList(nullptr);

        connect(m_sceneListWidget, &QWidget::destroyed, this, [this]() {m_sceneListWidget = nullptr;}); // 当窗口关闭时,将指针置空
        connect(m_sceneListWidget, &AppAllList::requestSendSceneData,  m_protocol_set_config, &AppProtocolSetConfig::sendSceneData);    // 下发设备场景
        connect(m_sceneListWidget, &AppAllList::requestSendBindData, m_protocol_set_config, &AppProtocolSetConfig::sendBindData);       // 下发设备绑定

        connect(m_sceneListWidget, &AppAllList::requestClearSceneData,  m_protocol_set_config, &AppProtocolSetConfig::sendClearSceneData); // 删除设备场景
        connect(m_sceneListWidget, &AppAllList::requestClearBindData, m_protocol_set_config, &AppProtocolSetConfig::sendClearBindData);    // 删除设备绑定

        connect(m_sceneListWidget, &AppAllList::requestEditScene, this, &AppSetConfig::create_scene);

        connect(m_protocol_set_config, &AppProtocolSetConfig::sceneListChanged, m_sceneListWidget, &AppAllList::setSceneData); // 连接场景数据
        connect(m_protocol_set_config, &AppProtocolSetConfig::bindListChanged,m_sceneListWidget, &AppAllList::setBindData);    // 连接绑定数据
    }
}

// 打开场景列表
void AppSetConfig::on_scene_list_clicked()
{
    CreateListWindow();
    if (m_sceneListWidget)
    {
        m_sceneListWidget->show();
        m_sceneListWidget->raise();
        m_sceneListWidget->activateWindow();
    }
}

// 打开定时任务
void AppSetConfig::on_timer_task_clicked()
{
    if (!m_timerSelDialog)
    {
        m_timerSelDialog = new DialogTimer(this);
        connect(m_timerSelDialog, &DialogTimer::sigGetTimerTask,  m_protocol_set_config, &AppProtocolSetConfig::sendGetTimerTask);    // 获取定时任务
        connect(m_timerSelDialog, &DialogTimer::sigSetTimerTask, m_protocol_set_config, &AppProtocolSetConfig::sendSetTimerTask);     // 下发定时任务
        connect(m_protocol_set_config, &AppProtocolSetConfig::sigUpdate, m_timerSelDialog, &DialogTimer::setDisplay);                 // 更新控件显示
    }
    if (m_timerSelDialog->exec() != QDialog::Accepted)
        return;
}

// 校准时间
void AppSetConfig::on_time_cal_clicked()
{
    bool ok = false;
    // 每次点击按钮进来，都获取最新的系统时间作为初始值
    QString input_text = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    while (true) {
        input_text = QInputDialog::getText(
                    this,
                    tr("校准时间"),
                    tr("请输入时间 yyyy-MM-dd HH:mm:ss"),
                    QLineEdit::Normal,
                    input_text, // 如果输错循环了，这里会保留用户输错的文本
                    &ok
                    );

        if (!ok) {
            break; // 点取消,直接退出函数
        }

        QDateTime select_time = QDateTime::fromString(input_text, "yyyy-MM-dd HH:mm:ss");

        if (select_time.isValid()) {
            uint64_t unix_time_secs = select_time.toSecsSinceEpoch();
            m_protocol_set_config->sendCalTime(unix_time_secs);
            return; // 成功发送，大功告成
        } else {
            QMessageBox::warning(this, tr("错误"), tr("时间格式输入有误，请严格按照 yyyy-MM-dd HH:mm:ss 格式输入!"));
        }
    }
}

// 关闭场景列表
void AppSetConfig::CloseListWidget()
{
    if (m_sceneListWidget) {
        m_sceneListWidget->close();
        m_sceneListWidget = nullptr;
    }
}

void AppSetConfig::CloseSceneDialog()
{
    if (m_set_sceneDialog){
        m_set_sceneDialog->close();
        m_set_sceneDialog = nullptr;
    }
}

bool AppSetConfig::ConfigIsChanged()
{
    bool ok = false;
    if(m_ui_Changed == true) { // UI 界面发生变化
        ok = true;
    }
    if (m_protocol_set_config && m_protocol_set_config->configIsChanged())
    {
        ok = true;
    }
    return ok;
}

// 新建配置信息
void AppSetConfig::on_new_data_clicked()
{
    QSettings settings("AODSN", "ConfigTool");
    QString defaultPath = settings.value("lastSavePath", "data.json").toString();

    // 让用户选择“新文件路径 + 文件名”
    QString filePath = QFileDialog::getSaveFileName(this, "新建配置文件", defaultPath, "JSON Files (*.json);;All Files (*.*)");

    if (filePath.isEmpty())
        return;

    // 自动补后缀
    if (!filePath.endsWith(".json"))
        filePath += ".json";

    // 创建一个基础空结构 JSON
    QJsonObject root;
    root["config"] = QJsonObject();
    root["protocol"] = QJsonObject();

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "失败", "无法创建文件,请检查路径权限");
        return;
    }

    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    file.close();

    // 清UI
    QLayoutItem *child;
    while ((child = m_flowLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    // 清数据
    m_panelCount = 0;
    m_ledCount = 0;
    m_relayCount = 0;

    // 清协议数据
    if (m_protocol_set_config) {
        m_protocol_set_config->setAllConfigData({});
        m_protocol_set_config->setAllBindData({});
    }
    settings.setValue("lastSavePath", filePath);
    QMessageBox::information(this, "新建成功", "已创建并清空当前工程");
}

// 导入配置信息
void AppSetConfig::on_load_data_clicked()
{
    QSettings settings("AODSN", "ConfigTool");
    QString defaultPath = settings.value("lastSavePath", "data.json").toString(); // 默认路径使用上次保存的路径

    QString filePath = QFileDialog::getOpenFileName(this, "加载配置信息", defaultPath, "JSON Files (*.json);;All Files (*.*)");
    if (filePath.isEmpty()) return;

    // 加载3部分数据 UI数据,场景数据,绑定数据
    bool ok = loadWidgets(filePath) && loadSceneDatas(filePath)  && loadBindDatas(filePath);

    if(ok) {
        settings.setValue("lastSavePath", filePath); // 保存到 QSettings,确保下次可用
        QMessageBox::information(this, "加载成功", QString("配置已成功加载!\n%1个面板,%2个LED扩展,%3个继电器扩展").arg(m_panelCount).arg(m_ledCount).arg(m_relayCount));
    } else {
        QMessageBox::warning(this, "加载失败", "配置文件加载失败，请检查文件格式或路径");
    }
}

// 保存配置信息
void AppSetConfig::on_save_data_clicked()
{
    QSettings settings("AODSN", "ConfigTool");
    QString defaultPath = settings.value("lastSavePath", "data.json").toString();

    QString filePath = QFileDialog::getSaveFileName(this, "保存配置信息", defaultPath, "JSON Files (*.json);;All Files (*.*)");
    if (filePath.isEmpty()) return;

    bool ok = saveWidgets(filePath) && saveSceneDatas(filePath)  && saveBindDatas(filePath);

    if (ok) {
        settings.setValue("lastSavePath", filePath); // 保存到 QSettings,确保下次可用
        QMessageBox::information(this, "保存成功", QString("配置已成功保存！\n文件路径：%1\n共保存 %2 个面板").arg(filePath).arg(m_panelCount));

        // 保存成功后,清除改变标志位
        m_ui_Changed = false;
        if(m_protocol_set_config) {
            m_protocol_set_config->clearConfigChanged();
        }
    } else {
        QMessageBox::warning(this, "保存失败", "配置文件保存失败，请检查文件是否被占用或磁盘是否可写");
    }
}

// 保存界面文件
bool AppSetConfig::saveWidgets(const QString& filePath)
{
    QFile file(filePath);
    QJsonObject root; // 创建一个空的 json 对象

    // 如果文件存在,先读取
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        if (doc.isObject()) {
            root = doc.object(); // 把文件里的 JSON 复制到 root 变量里
        }
    }

    // 构造配置数据对象
    QJsonObject configObj;

    // panel
    QJsonArray panelArray;
    for (int i = 0; i < m_panelCount; ++i) {
        const auto& p = m_panelArray[i];
        QJsonObject obj{{"id", p.addr}, {"type", static_cast<int>(p.type)}, {"key_num", p.key_num}};
        QJsonArray keyNames;

        for (const auto& name : p.key_name) {
            keyNames.append(name);
        }
        obj["key_name"] = keyNames;
        panelArray.append(obj);
    }
    configObj["panel"] = panelArray;

    // led_ex
    QJsonArray ledArray;
    for (int i = 0; i < m_ledCount; ++i) {
        const auto& led = m_ledArray[i];
        QJsonObject obj{{"id", led.id}, {"type", static_cast<int>(led.type)}};
        ledArray.append(obj);
    }
    configObj["led_ex"] = ledArray;

    // relay_ex
    QJsonArray relayArray;
    for (int i = 0; i < m_relayCount; ++i) {
        const auto& relay = m_relayArray[i];
        QJsonObject obj{{"id", relay.id}, {"type", static_cast<int>(relay.type)}};
        relayArray.append(obj);
    }

    configObj["relay_ex"] = relayArray;
    configObj["panel_count"] = m_panelCount;
    configObj["led_ex_count"] = m_ledCount;
    configObj["relay_ex_count"] = m_relayCount;

    root["config"] = configObj; // 放到顶层 config 对象下

    // 写回文件
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
        file.close();
        return true;
    } else {
        return false;
    }
}

// 自动加载布局
void AppSetConfig::autoLoadAllData(void)
{
    QSettings settings("AODSN", "ConfigTool");
    QString lastFilePath = settings.value("lastSavePath").toString();

    if (lastFilePath.isEmpty() || !QFile::exists(lastFilePath)) return;

    // 加载 UI 布局数据
    if (loadWidgets(lastFilePath))
    {
        loadSceneDatas(lastFilePath);
        loadBindDatas(lastFilePath);
    }
    else
    {
        qWarning() << "自动加载失败：" << lastFilePath;
        settings.remove("lastSavePath");
    }
}

// 加界面载文件
bool AppSetConfig::loadWidgets(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "配置文件不存在：" << filePath;
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isObject()) {
        qWarning() << "JSON格式错误：" << filePath;
        return false;
    }

    auto root = doc.object();

    // 取 config 对象
    if (!root.contains("config") || !root["config"].isObject()) {
        qWarning() << "JSON里没有 config 对象";
        return false;
    }

    auto config = root["config"].toObject();
    // 彻底销毁旧的面板控件
    QLayoutItem *child;
    while ((child = m_flowLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    // 清空原有计数数据
    m_panelCount = 0;
    m_ledCount = 0;
    m_relayCount = 0;

    // panel
    for (const auto& val : config["panel"].toArray()) {
        if (m_panelCount >= MAX_PANEL) break;

        auto obj = val.toObject();
        PanelInfo_t p{};
        p.addr      = static_cast<uint8_t>(obj["id"].toInt());
        p.type    = static_cast<PanelType>(obj["type"].toInt());
        p.key_num = static_cast<uint8_t>(obj["key_num"].toInt());

        auto names = obj["key_name"].toArray();
        for (int k = 0; k < names.size() && k < 6; ++k)
            p.key_name[k] = names[k].toString();

        m_panelArray[m_panelCount] = p;
        if (auto widget = CreatePanelWidget(p)) {
            AddToLayout(widget);
            m_panelCount++;
        }
    }

    // led_ex
    for (const auto& val : config["led_ex"].toArray()) {
        if (m_ledCount >= MAX_LED) break;
        auto obj = val.toObject();
        ExtendInfo_t led{};
        led.id = static_cast<uint8_t>(obj["id"].toInt());
        led.type = static_cast<ExtendType>(obj["type"].toInt());
        m_ledArray[m_ledCount++] = led;

        if (auto widget = CreateExtendWidget(led)) {
            AddToLayout(widget);
        }
    }

    // relay_ex
    for (const auto& val : config["relay_ex"].toArray()) {
        if (m_relayCount >= MAX_RELAY) break;
        auto obj = val.toObject();
        ExtendInfo_t relay{};
        relay.id = static_cast<uint8_t>(obj["id"].toInt());
        relay.type = static_cast<ExtendType>(obj["type"].toInt());
        m_relayArray[m_relayCount++] = relay;

        if (auto widget = CreateExtendWidget(relay)) {
            AddToLayout(widget);
        }
    }

    return true;
}

// 保存场景数据
bool AppSetConfig::saveSceneDatas(const QString &filePath)
{
    QFile file(filePath);
    QJsonObject root;

    // 读取原文件 JSON
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        if (doc.isObject()) root = doc.object();
    }

    // 获取 AppProtocolSetConfig 的数据
    config_data_t data = m_protocol_set_config->getAllConfigData();
    QJsonObject protocolObj;

    // panel
    QJsonArray panelArray;
    for (const auto &p :std::as_const(data.panel)) {
        QJsonObject obj;
        obj["scene_id"]      = p.scene_id;
        obj["scene_name"]    = p.scene_name;
        obj["panel_addr"]    = p.panel_addr;
        obj["panel_type"]    = p.panel_type;
        obj["panel_key_num"] = p.panel_key_num;

        QJsonArray keyNames;
        for (const auto &name : p.panel_name) keyNames.append(name);
        obj["key_name"] = keyNames;

        QJsonArray keyEnable;
        for (bool b : p.key_enable) keyEnable.append(b);
        obj["key_enable"] = keyEnable;

        QJsonArray keyState;
        for (bool b : p.key_state) keyState.append(b);
        obj["key_state"] = keyState;
        panelArray.append(obj);
    }
    protocolObj["panel"] = panelArray;

    // led_ex
    QJsonArray ledArray;
    for (const auto &l :std::as_const(data.led_ex)) {
        QJsonObject obj;
        obj["scene_id"]   = l.scene_id;
        obj["scene_name"] = l.scene_name;
        obj["led_addr"]   = l.led_addr;

        QJsonArray enabled;
        for (bool b : l.led_enable) enabled.append(b);
        obj["led_enable"] = enabled;

        QJsonArray values;
        for (int v : l.led_value) values.append(v);
        obj["led_value"] = values;

        ledArray.append(obj);
    }
    protocolObj["led_ex"] = ledArray;

    // relay_ex
    QJsonArray relayArray;
    for (const auto &l : std::as_const(data.relay_ex)) {

        QJsonObject obj;
        obj["scene_id"]    = l.scene_id;
        obj["scene_name"]  = l.scene_name;
        obj["relay_addr"]  = l.relay_addr;

        QJsonArray enabled;
        for (bool b : l.relay_enable) enabled.append(b);
        obj["relay_enable"] = enabled;

        QJsonArray values;
        for (bool v : l.relay_state) values.append(v);
        obj["relay_state"] = values;

        relayArray.append(obj);
    }
    protocolObj["relay_ex"] = relayArray;


    // scene_data
    QJsonArray sceneArray;
    for (const auto &s : std::as_const(data.scene)) {
        QJsonObject obj;
        obj["scene_name"] = s.scene_name;
        obj["scene_data"] = QString(s.scene_data.toHex());
        sceneArray.append(obj);
    }
    protocolObj["scene_data"] = sceneArray;
    root["protocol"] = protocolObj; // 放到顶层 protocol 对象下

    // 写回文件
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
        file.close();
        return true;
    } else {
        return false;
    }
}


bool AppSetConfig::loadSceneDatas(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开协议配置文件进行读取：" << filePath;
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isObject()) return false;
    QJsonObject root = doc.object();

    // 检查是否存在 protocol 节点
    if (!root.contains("protocol") || !root["protocol"].isObject()) {
        qWarning() << "JSON 中未发现 protocol 场景数据";
        return false;
    }

    QJsonObject protocolObj = root["protocol"].toObject();
    config_data_t data; // 准备装载数据的结构体

    // panel
    QJsonArray panelArray = protocolObj["panel"].toArray();
    for (const auto &val : std::as_const(panelArray)) {
        QJsonObject obj = val.toObject();
        panel_save_t p;
        p.scene_id      = static_cast<uint8_t>(obj["scene_id"].toInt());
        p.scene_name    = obj["scene_name"].toString();
        p.panel_addr    = static_cast<uint8_t>(obj["panel_addr"].toInt());
        p.panel_type    = static_cast<uint8_t>(obj["panel_type"].toInt());
        p.panel_key_num = static_cast<uint8_t>(obj["panel_key_num"].toInt());

        // 还原按键别名数组 QString[6]
        QJsonArray names = obj["key_name"].toArray();
        for (int i = 0; i < names.size() && i < 6; ++i) {
            p.panel_name[i] = names[i].toString();
        }

        // 还原勾选状态 QVector<bool>
        QJsonArray keyEnable = obj["key_enable"].toArray();
        for (const auto &b : std::as_const(keyEnable)) p.key_enable.append(b.toBool());

        QJsonArray keyState = obj["key_state"].toArray();
        for (const auto &b : std::as_const(keyState)) p.key_state.append(b.toBool());

        data.panel.append(p);
    }

    // led_ex
    QJsonArray ledArray = protocolObj["led_ex"].toArray();
    for (const auto &val : std::as_const(ledArray)) {
        QJsonObject obj = val.toObject();
        led_save_t l;
        l.scene_id   = static_cast<uint8_t>(obj["scene_id"].toInt());
        l.scene_name = obj["scene_name"].toString();
        l.led_addr   = static_cast<uint8_t>(obj["led_addr"].toInt());

        QJsonArray enabled = obj["led_enable"].toArray();
        for (const auto &b : std::as_const(enabled)) l.led_enable.append(b.toBool());

        QJsonArray values = obj["led_value"].toArray();
        for (const auto &v : std::as_const(values)) l.led_value.append(v.toInt());

        data.led_ex.append(l);
    }

    // relay_ex
    QJsonArray relayArray = protocolObj["relay_ex"].toArray();
    for (const auto &val :std::as_const(relayArray)) {

        QJsonObject obj = val.toObject();
        relay_save_t r;
        r.scene_id   = static_cast<uint8_t>(obj["scene_id"].toInt());
        r.scene_name = obj["scene_name"].toString();
        r.relay_addr = static_cast<uint8_t>(obj["relay_addr"].toInt());

        QJsonArray enabled = obj["relay_enable"].toArray();
        for (const auto &b :std::as_const(enabled)) r.relay_enable.append(b.toBool());

        QJsonArray state = obj["relay_state"].toArray();
        for (const auto &v : std::as_const(state)) r.relay_state.append(v.toBool());

        data.relay_ex.append(r);
    }

    // scene_data
    QJsonArray sceneArray = protocolObj["scene_data"].toArray();
    for (const auto &val : std::as_const(sceneArray)) {
        QJsonObject obj = val.toObject();
        scene_save_t s;

        // 关键点：将 Hex 字符串还原为 QByteArray
        s.scene_data = QByteArray::fromHex(obj["scene_data"].toString().toUtf8());
        s.scene_name = obj["scene_name"].toString();
        s.scene_id = s.scene_data[0];
        data.scene.append(s);
    }

    // 将数据塞回协议管理器
    if (m_protocol_set_config) {
        m_protocol_set_config->setAllConfigData(data);
        return true;
    }

    return false;
}

// 保存绑定信息
bool AppSetConfig::saveBindDatas(const QString &filePath)
{
    QFile file(filePath);
    QJsonObject root;

    // 读取原文件内容,确保不覆盖 config 或其他 protocol 数据
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        root = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
    }

    // 获取或创建 protocol 对象
    QJsonObject protocolObj = root["protocol"].toObject();

    // 准备绑定数据映射
    bind_data_t allBindData = m_protocol_set_config->getAllBindData();
    QJsonArray bindArray;
    for (const auto &b :std::as_const(allBindData.bind_data)) {
        QJsonObject obj;
        obj["scene_name"] = b.scene_name;
        obj["bind_data"]  = QString(b.bind_data.toHex());
        bindArray.append(obj);
    }

    // 只更新 protocol 里的 scene_bind_data 字段
    protocolObj["scene_bind_data"] = bindArray;
    root["protocol"] = protocolObj;

    // 写回文件
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
        file.close();
        return true;
    } else {
        return false;
    }
}

// 加载绑定信息
bool AppSetConfig::loadBindDatas(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开配置文件进行读取：" << filePath;
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isObject()) return false;

    QJsonObject root = doc.object();

    // 先进入 protocol 层级
    if (!root.contains("protocol") || !root["protocol"].isObject()) {
        qWarning() << "JSON 中未找到 protocol 节点";
        return false;
    }
    QJsonObject protocolObj = root["protocol"].toObject();

    // 在 protocol 内部查找 scene_bind_data
    if (!protocolObj.contains("scene_bind_data") || !protocolObj["scene_bind_data"].isArray()) {
        qWarning() << "protocol 节点下未找到 scene_bind_data 数组";
        return false;
    }

    QJsonArray bindArray = protocolObj["scene_bind_data"].toArray();
    bind_data_t allBinds;

    // 解析数组内容
    for (const auto &val :std::as_const(bindArray)) {
        QJsonObject obj = val.toObject();
        bind_save_t item;
        item.scene_name = obj["scene_name"].toString();
        // 将 Hex 字符串还原为 QByteArray
        item.bind_data  = QByteArray::fromHex(obj["bind_data"].toString().toUtf8());
        allBinds.bind_data.append(item);
    }

    // 同步到协议管理器
    if (m_protocol_set_config) {
        // 传递整个结构体
        m_protocol_set_config->setAllBindData(allBinds);
        qDebug() << "成功加载绑定信息，共" << allBinds.bind_data.size() << "条";
        return true;
    }

    return false;
}


