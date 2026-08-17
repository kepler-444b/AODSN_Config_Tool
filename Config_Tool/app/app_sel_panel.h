#ifndef APP_SEL_PANEL_H
#define APP_SEL_PANEL_H

#include <QDialog>
#include <QtDebug>
#include <QButtonGroup>
#include <QMessageBox>

typedef enum
{
    KNOB = 0,
    PANEL = 1
} PanelType;

typedef struct
{
    uint8_t addr;
    uint8_t type;
    uint8_t key_num;
    QString key_name[6];        // 按键别名
    QVector<bool> key_enable;   // 按键勾选状态
    QVector<bool> key_state;    // 对应状态勾选状态

} PanelInfo_t;



namespace Ui {
class DialogPanel;
}

class DialogPanel : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPanel(QWidget *parent = nullptr);
    ~DialogPanel();

    PanelInfo_t GetPanelInfo() const;
    void SetPanelInfo(const PanelInfo_t &info);

private slots:
    void on_knob_clicked();
    void on_panel_clicked();
    void on_key_1_clicked();
    void on_key_2_clicked();
    void on_key_3_clicked();
    void on_key_4_clicked();
    void on_key_6_clicked();

    void on_set_addr_valueChanged(int arg1);
    void on_pushButton_clicked();

private:
    Ui::DialogPanel *ui;
    PanelInfo_t m_PanelInfo;
};

#endif // APP_SEL_PANEL_H
