#ifndef MODEL_RELAY_EX_H
#define MODEL_RELAY_EX_H


#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QMouseEvent>
#include <QAction>
#include "app/app_sel_extend.h"

namespace Ui {
class ModelRelayEx;
}

class ModelRelayEx : public QWidget
{
    Q_OBJECT

public:
    explicit ModelRelayEx(QWidget *parent = nullptr);
    ~ModelRelayEx();
    void SetExtendAddr(const uint8_t addr, const ExtendType type);
    void SetExtendSatae(const QByteArray &data);

signals:
    void requestDelete(uint8_t id, ExtendType type);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:

private:
    Ui::ModelRelayEx *ui;

    uint8_t m_addr = 0;
    uint8_t m_relay_status_h = 0;  // 继电器回路状态(高)
    uint8_t m_relay_status_l = 0;  // 继电器回路状态(低)
    ExtendType m_type = RELAY_EX;
};

#endif // MODEL_RELAY_EX_H
