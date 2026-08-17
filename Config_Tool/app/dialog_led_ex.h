#ifndef DIALOG_LED_EX_H
#define DIALOG_LED_EX_H

#include <QDialog>

namespace Ui {
class DialogLedEx;
}

class DialogLedEx : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLedEx(QWidget *parent = nullptr);
    ~DialogLedEx();

private:
    Ui::DialogLedEx *ui;
};

#endif // DIALOG_LED_EX_H
