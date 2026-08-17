#ifndef APP_SET_CONFIG_H
#define APP_SET_CONFIG_H

#include <QWidget>
#include <QtDebug>
#include <QMessageBox>
#include <QGridLayout>
#include <QSettings>
#include <QHash>
#include <QTimer>
#include <QShortcut>
#include <QKeySequence>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>

#include "app/app_serial.h"
#include "app_sel_panel.h"
#include "app_sel_extend.h"
#include "app_sel_timer.h"
#include "app_sel_set_scene.h"
#include "app_all_list.h"
#include "app_protocol_set_config.h"
#include "app_protocol_sim_state.h"

#include "flow/flowlayout.h"

#define MAX_PANEL  32
#define MAX_LED     4
#define MAX_RELAY   4

namespace Ui {
class AppSetConfig;
}

class AppSetConfig : public QWidget
{
    Q_OBJECT

public:
    explicit AppSetConfig(QWidget *parent, AppSerial* serialWidget);
    ~AppSetConfig();

    bool ConfigIsChanged();             // 检查 UI 及配置是否发生变化
    void CloseListWidget();             // 关闭场景全局列表窗口
    void CloseSceneDialog();            // 关闭设置/编辑场景弹窗

    void RemovePanel(uint8_t id);
    void UpdatePanelKeyName(uint8_t panelId, int keyIndex, const QString& newAlias);
    void RemoveExtend(uint8_t id, ExtendType type);


private slots:

    void on_add_panel_clicked();        // 点击添加面板
    void on_add_extend_clicked();       // 点击添加扩展
    void on_set_scene_clicked();        // 点击快捷创建场景
    void on_scene_list_clicked();       // 点击查看/打开全局场景列表
    void on_timer_task_clicked();       // 点击打开定时任务
    void create_scene(int id);          // 创建/编辑指定 ID 的场景页面

    void on_new_data_clicked();         // 槽:新建工程/配置
    void on_load_data_clicked();        // 槽:导入配置
    void on_save_data_clicked();        // 槽:保存配置
    void autoLoadAllData();             // 定时器触发：自动加载上次保存的配置

    void on_time_cal_clicked();

private:
    // 硬件网格布局与组件生成 (Hardware UI Generator)
    template<typename PanelType>
    QWidget* CreateSetupPanel(const PanelInfo_t& info);    // 模板函数:实例化具体的面板对象
    QWidget* CreatePanelWidget(const PanelInfo_t& info);   // 动态创建面板包装
    QWidget* CreateExtendWidget(const ExtendInfo_t& info); // 动态创建扩展包装
    void AddToLayout(QWidget* Widget);                     // 将生成的 Widget 塞入流式布局

    bool IsPanelIdExist(uint8_t id) const;             // 校验面板通信地址是否冲突
    bool IsExtendLedExist(ExtendInfo_t *info) const;   // 校验扩展模块通信地址是否冲突

    bool saveWidgets(const QString& filePath = "data.json");     // 读写本地:UI 树形结构
    bool loadWidgets(const QString& filePath = "data.json");     // 还原本地:UI 树形结构

    bool saveSceneDatas(const QString &filePath);                // 读写本地:场景指令状态
    bool loadSceneDatas(const QString &filePath);                // 还原本地:场景指令状态

    bool saveBindDatas(const QString &filePath);                 // 读写本地:按键/场景绑定映射
    bool loadBindDatas(const QString &filePath);                 // 还原本地:按键/场景绑定映射

    void CreateListWindow();  // 初始化场景列表全局窗口

    DialogTimer* m_timerSelDialog      = nullptr;
    DialogPanel* m_panelSelDialog      = nullptr;          // 弹窗:选择面板属性
    DialogExtend* m_extendSelDialog    = nullptr;          // 弹窗:选择扩展属性
    DialogSetScene* m_set_sceneDialog  = nullptr;          // 弹窗:单条场景细则配置界面
    AppAllList* m_sceneListWidget      = nullptr;          // 独立窗口:展示所有已建场景/绑定的主列表
    AppProtocolSetConfig* m_protocol_set_config = nullptr; // 数据帧打包/解析协议层控制器
    AppProtocolSimState* m_protocol_sim_state   = nullptr; // 设备模拟状态

    // 面板数据层
    PanelInfo_t m_panelArray[MAX_PANEL];
    PanelInfo_t m_lastPanelInfo = {0, PANEL, 1, {}, {}, {}};
    int         m_panelCount = 0;

    // 扩展模块数据层
    ExtendInfo_t m_ledArray[MAX_LED];
    ExtendInfo_t m_relayArray[MAX_RELAY];
    int m_ledCount   = 0;
    int m_relayCount = 0;
    ExtendInfo_t m_lastExtendInfo = {0, LED_EX, {}, {}, {}, {}};


    Ui::AppSetConfig* ui;
    AppSerial* m_serialWidget  = nullptr; // 外部注入的公共串口实例
    FlowLayout* m_flowLayout   = nullptr; // 动态流式布局管理器指针
    bool m_ui_Changed          = false;   // 界面改变标记位
};

#endif // APP_SET_CONFIG_H
