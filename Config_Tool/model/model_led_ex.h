#ifndef MODEL_LED_H
#define MODEL_LED_H

#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QMouseEvent>
#include <QAction>
#include "app/app_sel_extend.h"

typedef struct
{
    uint8_t lum;
    uint8_t cct;
    bool led;
} led_status;

namespace Ui {
class ModelLedEx;
}

class ModelLedEx : public QWidget
{
    Q_OBJECT

public:
    explicit ModelLedEx(QWidget *parent = nullptr);
    ~ModelLedEx();

    void SetExtendAddr(const uint8_t addr, const ExtendType type);
    void SetExtendSatae(const QByteArray &data);

private:
    void setLedState(QPushButton *button, uint8_t cct, uint8_t lum, int state = -1);
private slots:

    void on_led_1_clicked();
    void on_led_2_clicked();
    void on_led_3_clicked();
    void on_led_4_clicked();
    void on_led_5_clicked();
    void on_led_6_clicked();
    void on_led_7_clicked();
    void on_led_8_clicked();

    void on_lum_1_editingFinished();
    void on_lum_2_editingFinished();
    void on_lum_3_editingFinished();
    void on_lum_4_editingFinished();
    void on_lum_5_editingFinished();
    void on_lum_6_editingFinished();
    void on_lum_7_editingFinished();
    void on_lum_8_editingFinished();

    void on_cct_1_editingFinished();
    void on_cct_2_editingFinished();
    void on_cct_3_editingFinished();
    void on_cct_4_editingFinished();
    void on_cct_5_editingFinished();
    void on_cct_6_editingFinished();
    void on_cct_7_editingFinished();
    void on_cct_8_editingFinished();

signals:
    void requestDelete(uint8_t id, ExtendType type);
    void sendSimLedState(const uint8_t led_num, const uint8_t lum, const uint8_t cct);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::ModelLedEx *ui;

    uint8_t m_addr = 0;
    led_status m_led_status[8] = {
        {0, 50, false},
        {0, 50, false},
        {0, 50, false},
        {0, 50, false},
        {0, 50, false},
        {0, 50, false},
        {0, 50, false},
        {0, 50, false}
    };

    ExtendType m_type = LED_EX;

};

#endif // MODEL_LED_H
