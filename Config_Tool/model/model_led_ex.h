#ifndef MODEL_LED_H
#define MODEL_LED_H

#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QMouseEvent>
#include <QAction>
#include "app/app_sel_extend.h"

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
private slots:

signals:
    void requestDelete(uint8_t id, ExtendType type);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::ModelLedEx *ui;

    uint8_t m_addr = 0;
    uint8_t m_led_status[8] = {};
    ExtendType m_type = LED_EX;

};

#endif // MODEL_LED_H
