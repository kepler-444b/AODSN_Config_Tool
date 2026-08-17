#ifndef APP_SEL_EXTEND_H
#define APP_SEL_EXTEND_H

#include <QDialog>
#include <QtDebug>
#include <QMessageBox>

typedef enum
{
    RELAY_EX = 0,
    LED_EX   = 1
} ExtendType;

typedef struct
{
    uint8_t id;
    ExtendType type;
    QVector<bool> led_enable;
    QVector<int>  led_value;

    QVector<bool> relay_enable;
    QVector<bool> relay_state;
} ExtendInfo_t;

typedef struct
{
    uint8_t addr;
    uint8_t led_lum[8];

} ExtendLedInfo_t;

typedef struct
{
    uint8_t addr;
    uint8_t relay_state;
} ExtendRelayInfo_t;

namespace Ui {
class DialogExtend;
}

class DialogExtend : public QDialog
{
    Q_OBJECT

public:
    explicit DialogExtend(QWidget *parent = nullptr);
    ~DialogExtend();
    ExtendInfo_t GetExtendInfo() const;

    void SetExtendInfo(const ExtendInfo_t &info);

private slots:
    void on_led_ex_clicked();
    void on_relay_ex_clicked();
    void on_pushButton_clicked();

    void on_set_addr_valueChanged(int arg1);

private:
    Ui::DialogExtend *ui;
    ExtendInfo_t m_ExtendInfo;
};

#endif // APP_SEL_EXTEND_H
