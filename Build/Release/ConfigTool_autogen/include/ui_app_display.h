/********************************************************************************
** Form generated from reading UI file 'app_display.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP_DISPLAY_H
#define UI_APP_DISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppDisplay
{
public:
    QGridLayout *gridLayout;
    QTextEdit *send_input;
    QPushButton *send;
    QPushButton *clear;
    QTextEdit *display;

    void setupUi(QWidget *AppDisplay)
    {
        if (AppDisplay->objectName().isEmpty())
            AppDisplay->setObjectName("AppDisplay");
        AppDisplay->resize(600, 600);
        AppDisplay->setMinimumSize(QSize(600, 600));
        gridLayout = new QGridLayout(AppDisplay);
        gridLayout->setObjectName("gridLayout");
        send_input = new QTextEdit(AppDisplay);
        send_input->setObjectName("send_input");
        send_input->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    border: 1px solid #bdbdbd;\n"
"    border-radius: 4px;\n"
"    padding: 3px;\n"
"    background-color: white;\n"
"}"));

        gridLayout->addWidget(send_input, 1, 0, 2, 1);

        send = new QPushButton(AppDisplay);
        send->setObjectName("send");
        send->setMinimumSize(QSize(72, 36));
        send->setMaximumSize(QSize(72, 36));

        gridLayout->addWidget(send, 1, 1, 1, 1);

        clear = new QPushButton(AppDisplay);
        clear->setObjectName("clear");
        clear->setMinimumSize(QSize(72, 36));
        clear->setMaximumSize(QSize(72, 36));

        gridLayout->addWidget(clear, 2, 1, 1, 1);

        display = new QTextEdit(AppDisplay);
        display->setObjectName("display");
        display->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    border: 1px solid #bdbdbd;\n"
"    border-radius: 4px;\n"
"    padding: 3px;\n"
"    background-color: white;\n"
"}"));

        gridLayout->addWidget(display, 0, 0, 1, 2);


        retranslateUi(AppDisplay);

        QMetaObject::connectSlotsByName(AppDisplay);
    } // setupUi

    void retranslateUi(QWidget *AppDisplay)
    {
        AppDisplay->setWindowTitle(QCoreApplication::translate("AppDisplay", "\350\260\203\350\257\225\347\252\227\345\217\243", nullptr));
        send->setText(QCoreApplication::translate("AppDisplay", "\345\217\221\351\200\201", nullptr));
        clear->setText(QCoreApplication::translate("AppDisplay", "\346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AppDisplay: public Ui_AppDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_DISPLAY_H
