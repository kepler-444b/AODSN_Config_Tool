/********************************************************************************
** Form generated from reading UI file 'model_led_ex.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODEL_LED_EX_H
#define UI_MODEL_LED_EX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModelLedEx
{
public:
    QWidget *led_1;
    QGridLayout *gridLayout_2;
    QLabel *led_1_lum;
    QLabel *label;
    QWidget *led_8;
    QGridLayout *gridLayout;
    QLabel *led_8_lum;
    QLabel *label_8;
    QWidget *led_7;
    QGridLayout *gridLayout_5;
    QLabel *led_7_lum;
    QLabel *label_7;
    QWidget *led_6;
    QGridLayout *gridLayout_4;
    QLabel *led_6_lum;
    QLabel *label_6;
    QWidget *led_5;
    QGridLayout *gridLayout_3;
    QLabel *led_5_lum;
    QLabel *label_5;
    QWidget *led_4;
    QGridLayout *gridLayout_6;
    QLabel *led_4_lum;
    QLabel *label_4;
    QWidget *led_3;
    QGridLayout *gridLayout_7;
    QLabel *led_3_lum;
    QLabel *label_3;
    QWidget *led_2;
    QGridLayout *gridLayout_8;
    QLabel *led_2_lum;
    QLabel *label_2;
    QGridLayout *gridLayout_9;
    QFrame *frame;
    QLabel *addr;

    void setupUi(QWidget *ModelLedEx)
    {
        if (ModelLedEx->objectName().isEmpty())
            ModelLedEx->setObjectName("ModelLedEx");
        ModelLedEx->resize(200, 220);
        ModelLedEx->setMinimumSize(QSize(200, 220));
        ModelLedEx->setMaximumSize(QSize(200, 220));
        ModelLedEx->setLayoutDirection(Qt::LeftToRight);
        ModelLedEx->setStyleSheet(QString::fromUtf8(""));
        led_1 = new QWidget(ModelLedEx);
        led_1->setObjectName("led_1");
        led_1->setGeometry(QRect(10, 10, 40, 80));
        led_1->setMinimumSize(QSize(40, 80));
        led_1->setMaximumSize(QSize(40, 80));
        led_1->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    \n"
"    border-radius: 4px;\n"
"	background-color: white;\n"
"}"));
        gridLayout_2 = new QGridLayout(led_1);
        gridLayout_2->setObjectName("gridLayout_2");
        led_1_lum = new QLabel(led_1);
        led_1_lum->setObjectName("led_1_lum");
        led_1_lum->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(led_1_lum, 0, 0, 1, 1);

        label = new QLabel(led_1);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        led_8 = new QWidget(ModelLedEx);
        led_8->setObjectName("led_8");
        led_8->setGeometry(QRect(148, 96, 40, 80));
        led_8->setMinimumSize(QSize(40, 80));
        led_8->setMaximumSize(QSize(40, 80));
        led_8->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    \n"
"    border-radius: 4px;\n"
"	background-color: white;\n"
"}"));
        gridLayout = new QGridLayout(led_8);
        gridLayout->setObjectName("gridLayout");
        led_8_lum = new QLabel(led_8);
        led_8_lum->setObjectName("led_8_lum");
        led_8_lum->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(led_8_lum, 0, 0, 1, 1);

        label_8 = new QLabel(led_8);
        label_8->setObjectName("label_8");
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_8, 1, 0, 1, 1);

        led_7 = new QWidget(ModelLedEx);
        led_7->setObjectName("led_7");
        led_7->setGeometry(QRect(102, 96, 40, 80));
        led_7->setMinimumSize(QSize(40, 80));
        led_7->setMaximumSize(QSize(40, 80));
        led_7->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    \n"
"    border-radius: 4px;\n"
"	background-color: white;\n"
"}"));
        gridLayout_5 = new QGridLayout(led_7);
        gridLayout_5->setObjectName("gridLayout_5");
        led_7_lum = new QLabel(led_7);
        led_7_lum->setObjectName("led_7_lum");
        led_7_lum->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(led_7_lum, 0, 0, 1, 1);

        label_7 = new QLabel(led_7);
        label_7->setObjectName("label_7");
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_7, 1, 0, 1, 1);

        led_6 = new QWidget(ModelLedEx);
        led_6->setObjectName("led_6");
        led_6->setGeometry(QRect(56, 96, 40, 80));
        led_6->setMinimumSize(QSize(40, 80));
        led_6->setMaximumSize(QSize(40, 80));
        led_6->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    \n"
"    border-radius: 4px;\n"
"	background-color: white;\n"
"}"));
        gridLayout_4 = new QGridLayout(led_6);
        gridLayout_4->setObjectName("gridLayout_4");
        led_6_lum = new QLabel(led_6);
        led_6_lum->setObjectName("led_6_lum");
        led_6_lum->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(led_6_lum, 0, 0, 1, 1);

        label_6 = new QLabel(led_6);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_6, 1, 0, 1, 1);

        led_5 = new QWidget(ModelLedEx);
        led_5->setObjectName("led_5");
        led_5->setGeometry(QRect(10, 96, 40, 80));
        led_5->setMinimumSize(QSize(40, 80));
        led_5->setMaximumSize(QSize(40, 80));
        led_5->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    \n"
"    border-radius: 4px;\n"
"	background-color: white;\n"
"}"));
        gridLayout_3 = new QGridLayout(led_5);
        gridLayout_3->setObjectName("gridLayout_3");
        led_5_lum = new QLabel(led_5);
        led_5_lum->setObjectName("led_5_lum");
        led_5_lum->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(led_5_lum, 0, 0, 1, 1);

        label_5 = new QLabel(led_5);
        label_5->setObjectName("label_5");
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_5, 1, 0, 1, 1);

        led_4 = new QWidget(ModelLedEx);
        led_4->setObjectName("led_4");
        led_4->setGeometry(QRect(148, 10, 40, 80));
        led_4->setMinimumSize(QSize(40, 80));
        led_4->setMaximumSize(QSize(40, 80));
        led_4->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    \n"
"    border-radius: 4px;\n"
"	background-color: white;\n"
"}"));
        gridLayout_6 = new QGridLayout(led_4);
        gridLayout_6->setObjectName("gridLayout_6");
        led_4_lum = new QLabel(led_4);
        led_4_lum->setObjectName("led_4_lum");
        led_4_lum->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(led_4_lum, 0, 0, 1, 1);

        label_4 = new QLabel(led_4);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_4, 1, 0, 1, 1);

        led_3 = new QWidget(ModelLedEx);
        led_3->setObjectName("led_3");
        led_3->setGeometry(QRect(102, 10, 40, 80));
        led_3->setMinimumSize(QSize(40, 80));
        led_3->setMaximumSize(QSize(40, 80));
        led_3->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    \n"
"    border-radius: 4px;\n"
"	background-color: white;\n"
"}"));
        gridLayout_7 = new QGridLayout(led_3);
        gridLayout_7->setObjectName("gridLayout_7");
        led_3_lum = new QLabel(led_3);
        led_3_lum->setObjectName("led_3_lum");
        led_3_lum->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(led_3_lum, 0, 0, 1, 1);

        label_3 = new QLabel(led_3);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_3, 1, 0, 1, 1);

        led_2 = new QWidget(ModelLedEx);
        led_2->setObjectName("led_2");
        led_2->setGeometry(QRect(56, 10, 40, 80));
        led_2->setMinimumSize(QSize(40, 80));
        led_2->setMaximumSize(QSize(40, 80));
        led_2->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    \n"
"    border-radius: 4px;\n"
"	background-color: white;\n"
"}"));
        gridLayout_8 = new QGridLayout(led_2);
        gridLayout_8->setObjectName("gridLayout_8");
        led_2_lum = new QLabel(led_2);
        led_2_lum->setObjectName("led_2_lum");
        led_2_lum->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(led_2_lum, 0, 0, 1, 1);

        label_2 = new QLabel(led_2);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_2, 1, 0, 1, 1);

        gridLayout_9 = new QGridLayout(ModelLedEx);
        gridLayout_9->setObjectName("gridLayout_9");
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(ModelLedEx);
        frame->setObjectName("frame");
        frame->setMinimumSize(QSize(200, 200));
        frame->setMaximumSize(QSize(200, 200));
        frame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: 1px solid #C0C0C0;\n"
"    border-radius: 4px;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout_9->addWidget(frame, 0, 0, 1, 1);

        addr = new QLabel(ModelLedEx);
        addr->setObjectName("addr");
        addr->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(addr, 1, 0, 1, 1);

        frame->raise();
        led_7->raise();
        led_6->raise();
        led_5->raise();
        led_4->raise();
        addr->raise();
        led_8->raise();
        led_1->raise();
        led_2->raise();
        led_3->raise();

        retranslateUi(ModelLedEx);

        QMetaObject::connectSlotsByName(ModelLedEx);
    } // setupUi

    void retranslateUi(QWidget *ModelLedEx)
    {
        ModelLedEx->setWindowTitle(QCoreApplication::translate("ModelLedEx", "Form", nullptr));
        led_1_lum->setText(QCoreApplication::translate("ModelLedEx", "0", nullptr));
        label->setText(QCoreApplication::translate("ModelLedEx", "1\350\267\257", nullptr));
        led_8_lum->setText(QCoreApplication::translate("ModelLedEx", "0", nullptr));
        label_8->setText(QCoreApplication::translate("ModelLedEx", "8\350\267\257", nullptr));
        led_7_lum->setText(QCoreApplication::translate("ModelLedEx", "0", nullptr));
        label_7->setText(QCoreApplication::translate("ModelLedEx", "7\350\267\257", nullptr));
        led_6_lum->setText(QCoreApplication::translate("ModelLedEx", "0", nullptr));
        label_6->setText(QCoreApplication::translate("ModelLedEx", "6\350\267\257", nullptr));
        led_5_lum->setText(QCoreApplication::translate("ModelLedEx", "0", nullptr));
        label_5->setText(QCoreApplication::translate("ModelLedEx", "5\350\267\257", nullptr));
        led_4_lum->setText(QCoreApplication::translate("ModelLedEx", "0", nullptr));
        label_4->setText(QCoreApplication::translate("ModelLedEx", "4\350\267\257", nullptr));
        led_3_lum->setText(QCoreApplication::translate("ModelLedEx", "0", nullptr));
        label_3->setText(QCoreApplication::translate("ModelLedEx", "3\350\267\257", nullptr));
        led_2_lum->setText(QCoreApplication::translate("ModelLedEx", "0", nullptr));
        label_2->setText(QCoreApplication::translate("ModelLedEx", "2\350\267\257", nullptr));
        addr->setText(QCoreApplication::translate("ModelLedEx", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModelLedEx: public Ui_ModelLedEx {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODEL_LED_EX_H
