/********************************************************************************
** Form generated from reading UI file 'app_serial.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP_SERIAL_H
#define UI_APP_SERIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppSerial
{
public:
    QGridLayout *gridLayout;
    QLabel *label_serial;
    QComboBox *com;
    QPushButton *switch_com;
    QLabel *label_baudrate;
    QComboBox *baudrate;
    QPushButton *refresh_com;

    void setupUi(QWidget *AppSerial)
    {
        if (AppSerial->objectName().isEmpty())
            AppSerial->setObjectName("AppSerial");
        AppSerial->resize(200, 80);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AppSerial->sizePolicy().hasHeightForWidth());
        AppSerial->setSizePolicy(sizePolicy);
        AppSerial->setMinimumSize(QSize(200, 80));
        AppSerial->setMaximumSize(QSize(200, 80));
        AppSerial->setLayoutDirection(Qt::LeftToRight);
        gridLayout = new QGridLayout(AppSerial);
        gridLayout->setObjectName("gridLayout");
        label_serial = new QLabel(AppSerial);
        label_serial->setObjectName("label_serial");
        label_serial->setMinimumSize(QSize(36, 0));
        label_serial->setMaximumSize(QSize(36, 16777215));

        gridLayout->addWidget(label_serial, 0, 0, 1, 1);

        com = new QComboBox(AppSerial);
        com->setObjectName("com");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(com->sizePolicy().hasHeightForWidth());
        com->setSizePolicy(sizePolicy1);
        com->setMinimumSize(QSize(70, 0));
        com->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(com, 0, 1, 1, 1);

        switch_com = new QPushButton(AppSerial);
        switch_com->setObjectName("switch_com");
        switch_com->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(switch_com, 0, 2, 1, 1);

        label_baudrate = new QLabel(AppSerial);
        label_baudrate->setObjectName("label_baudrate");
        label_baudrate->setMaximumSize(QSize(36, 16777215));

        gridLayout->addWidget(label_baudrate, 1, 0, 1, 1);

        baudrate = new QComboBox(AppSerial);
        baudrate->setObjectName("baudrate");
        baudrate->setMinimumSize(QSize(70, 0));
        baudrate->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(baudrate, 1, 1, 1, 1);

        refresh_com = new QPushButton(AppSerial);
        refresh_com->setObjectName("refresh_com");
        refresh_com->setMinimumSize(QSize(60, 0));
        refresh_com->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(refresh_com, 1, 2, 1, 1);


        retranslateUi(AppSerial);

        QMetaObject::connectSlotsByName(AppSerial);
    } // setupUi

    void retranslateUi(QWidget *AppSerial)
    {
        AppSerial->setWindowTitle(QCoreApplication::translate("AppSerial", "Form", nullptr));
        label_serial->setText(QCoreApplication::translate("AppSerial", "\347\253\257\345\217\243", nullptr));
        switch_com->setText(QCoreApplication::translate("AppSerial", "\346\211\223\345\274\200", nullptr));
        label_baudrate->setText(QCoreApplication::translate("AppSerial", "\346\263\242\347\211\271\347\216\207", nullptr));
        refresh_com->setText(QCoreApplication::translate("AppSerial", "\345\210\267\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AppSerial: public Ui_AppSerial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_SERIAL_H
