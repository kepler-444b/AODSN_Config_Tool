#include "dialog_led_ex.h"
#include "ui_dialog_led_ex.h"

DialogLedEx::DialogLedEx(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLedEx)
{
    ui->setupUi(this);
}

DialogLedEx::~DialogLedEx()
{
    delete ui;
}
