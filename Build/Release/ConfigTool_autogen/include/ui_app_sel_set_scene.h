/********************************************************************************
** Form generated from reading UI file 'app_sel_set_scene.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP_SEL_SET_SCENE_H
#define UI_APP_SEL_SET_SCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogSetScene
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_5;
    QLineEdit *scene_name;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QScrollArea *scrollArea;
    QWidget *sel_panel;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QScrollArea *scrollArea_led;
    QWidget *sel_led;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QScrollArea *scrollArea_relay;
    QWidget *sel_relay;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *DialogSetScene)
    {
        if (DialogSetScene->objectName().isEmpty())
            DialogSetScene->setObjectName("DialogSetScene");
        DialogSetScene->resize(700, 800);
        DialogSetScene->setMinimumSize(QSize(700, 800));
        DialogSetScene->setMaximumSize(QSize(700, 800));
        gridLayout = new QGridLayout(DialogSetScene);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(DialogSetScene);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        spinBox = new QSpinBox(DialogSetScene);
        spinBox->setObjectName("spinBox");
        spinBox->setMaximum(127);

        horizontalLayout->addWidget(spinBox);

        label_5 = new QLabel(DialogSetScene);
        label_5->setObjectName("label_5");

        horizontalLayout->addWidget(label_5);

        scene_name = new QLineEdit(DialogSetScene);
        scene_name->setObjectName("scene_name");

        horizontalLayout->addWidget(scene_name);

        horizontalSpacer_2 = new QSpacerItem(465, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(DialogSetScene);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        scrollArea = new QScrollArea(DialogSetScene);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setMinimumSize(QSize(680, 300));
        scrollArea->setMaximumSize(QSize(680, 300));
        scrollArea->setStyleSheet(QString::fromUtf8("QScrollArea {\n"
"    border: 1px solid #bdbdbd;\n"
"    border-radius: 4px;\n"
"    padding: 1px;\n"
"}"));
        scrollArea->setWidgetResizable(true);
        sel_panel = new QWidget();
        sel_panel->setObjectName("sel_panel");
        sel_panel->setGeometry(QRect(0, 0, 676, 296));
        scrollArea->setWidget(sel_panel);

        verticalLayout_3->addWidget(scrollArea);


        gridLayout->addLayout(verticalLayout_3, 1, 0, 1, 3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_3 = new QLabel(DialogSetScene);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        scrollArea_led = new QScrollArea(DialogSetScene);
        scrollArea_led->setObjectName("scrollArea_led");
        scrollArea_led->setMinimumSize(QSize(680, 200));
        scrollArea_led->setMaximumSize(QSize(680, 200));
        scrollArea_led->setStyleSheet(QString::fromUtf8("QScrollArea {\n"
"    border: 1px solid #bdbdbd;\n"
"    border-radius: 4px;\n"
"    padding: 1px;\n"
"}"));
        scrollArea_led->setWidgetResizable(true);
        sel_led = new QWidget();
        sel_led->setObjectName("sel_led");
        sel_led->setGeometry(QRect(0, 0, 676, 196));
        scrollArea_led->setWidget(sel_led);

        verticalLayout_2->addWidget(scrollArea_led);


        gridLayout->addLayout(verticalLayout_2, 2, 0, 1, 3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_4 = new QLabel(DialogSetScene);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        scrollArea_relay = new QScrollArea(DialogSetScene);
        scrollArea_relay->setObjectName("scrollArea_relay");
        scrollArea_relay->setMinimumSize(QSize(680, 200));
        scrollArea_relay->setMaximumSize(QSize(680, 200));
        scrollArea_relay->setStyleSheet(QString::fromUtf8("QScrollArea {\n"
"    border: 1px solid #bdbdbd;\n"
"    border-radius: 4px;\n"
"    padding: 1px;\n"
"}"));
        scrollArea_relay->setWidgetResizable(true);
        sel_relay = new QWidget();
        sel_relay->setObjectName("sel_relay");
        sel_relay->setGeometry(QRect(0, 0, 676, 196));
        scrollArea_relay->setWidget(sel_relay);

        verticalLayout->addWidget(scrollArea_relay);


        gridLayout->addLayout(verticalLayout, 3, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(282, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 0, 1, 1);

        pushButton = new QPushButton(DialogSetScene);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(100, 25));
        pushButton->setMaximumSize(QSize(100, 25));
        pushButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        pushButton->setIconSize(QSize(16, 16));

        gridLayout->addWidget(pushButton, 4, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(282, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 2, 1, 1);


        retranslateUi(DialogSetScene);

        QMetaObject::connectSlotsByName(DialogSetScene);
    } // setupUi

    void retranslateUi(QDialog *DialogSetScene)
    {
        DialogSetScene->setWindowTitle(QCoreApplication::translate("DialogSetScene", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DialogSetScene", "\345\234\272\346\231\257\347\274\226\345\217\267", nullptr));
        label_5->setText(QCoreApplication::translate("DialogSetScene", "\345\234\272\346\231\257\345\220\215\347\247\260", nullptr));
        label_2->setText(QCoreApplication::translate("DialogSetScene", "\350\256\276\347\275\256\351\235\242\347\212\266\346\200\201", nullptr));
        label_3->setText(QCoreApplication::translate("DialogSetScene", "\350\256\276\347\275\256LED\346\211\251\345\261\225\347\212\266\346\200\201", nullptr));
        label_4->setText(QCoreApplication::translate("DialogSetScene", "\350\256\276\347\275\256\347\273\247\347\224\265\345\231\250\346\211\251\345\261\225\347\212\266\346\200\201", nullptr));
        pushButton->setText(QCoreApplication::translate("DialogSetScene", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogSetScene: public Ui_DialogSetScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_SEL_SET_SCENE_H
