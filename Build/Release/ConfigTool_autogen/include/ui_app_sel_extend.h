/********************************************************************************
** Form generated from reading UI file 'app_sel_extend.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP_SEL_EXTEND_H
#define UI_APP_SEL_EXTEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_DialogExtend
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QGroupBox *sel_dev;
    QRadioButton *led_ex;
    QRadioButton *relay_ex;
    QLabel *label;
    QSpinBox *set_addr;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *DialogExtend)
    {
        if (DialogExtend->objectName().isEmpty())
            DialogExtend->setObjectName("DialogExtend");
        DialogExtend->resize(200, 150);
        DialogExtend->setMinimumSize(QSize(200, 150));
        DialogExtend->setMaximumSize(QSize(200, 150));
        gridLayout_2 = new QGridLayout(DialogExtend);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        sel_dev = new QGroupBox(DialogExtend);
        sel_dev->setObjectName("sel_dev");
        sel_dev->setMinimumSize(QSize(180, 50));
        sel_dev->setMaximumSize(QSize(180, 50));
        sel_dev->setStyleSheet(QString::fromUtf8(""));
        led_ex = new QRadioButton(sel_dev);
        led_ex->setObjectName("led_ex");
        led_ex->setGeometry(QRect(12, 29, 67, 16));
        relay_ex = new QRadioButton(sel_dev);
        relay_ex->setObjectName("relay_ex");
        relay_ex->setGeometry(QRect(85, 29, 83, 16));

        gridLayout->addWidget(sel_dev, 0, 0, 1, 2);

        label = new QLabel(DialogExtend);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        set_addr = new QSpinBox(DialogExtend);
        set_addr->setObjectName("set_addr");
        set_addr->setMaximum(99);

        gridLayout->addWidget(set_addr, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(45, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);

        pushButton = new QPushButton(DialogExtend);
        pushButton->setObjectName("pushButton");

        gridLayout_2->addWidget(pushButton, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(44, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 2, 1, 1);


        retranslateUi(DialogExtend);

        QMetaObject::connectSlotsByName(DialogExtend);
    } // setupUi

    void retranslateUi(QDialog *DialogExtend)
    {
        DialogExtend->setWindowTitle(QCoreApplication::translate("DialogExtend", "Dialog", nullptr));
        sel_dev->setTitle(QCoreApplication::translate("DialogExtend", "\351\200\211\346\213\251\346\211\251\345\261\225\347\261\273\345\236\213", nullptr));
        led_ex->setText(QCoreApplication::translate("DialogExtend", "8\350\267\257\350\260\203\345\205\211", nullptr));
        relay_ex->setText(QCoreApplication::translate("DialogExtend", "\347\273\247\347\224\265\345\231\250\346\211\251\345\261\225", nullptr));
        label->setText(QCoreApplication::translate("DialogExtend", "\350\256\276\345\244\207\345\234\260\345\235\200", nullptr));
        pushButton->setText(QCoreApplication::translate("DialogExtend", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogExtend: public Ui_DialogExtend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_SEL_EXTEND_H
