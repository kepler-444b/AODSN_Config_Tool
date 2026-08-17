/********************************************************************************
** Form generated from reading UI file 'app_set_config.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP_SET_CONFIG_H
#define UI_APP_SET_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppSetConfig
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *new_data;
    QPushButton *load_data;
    QPushButton *save_data;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QPushButton *timer_task;
    QPushButton *set_scene;
    QPushButton *time_cal;
    QPushButton *scene_list;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *add_panel;
    QPushButton *add_extend;
    QSpacerItem *horizontalSpacer_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QWidget *AppSetConfig)
    {
        if (AppSetConfig->objectName().isEmpty())
            AppSetConfig->setObjectName("AppSetConfig");
        AppSetConfig->resize(860, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AppSetConfig->sizePolicy().hasHeightForWidth());
        AppSetConfig->setSizePolicy(sizePolicy);
        AppSetConfig->setMinimumSize(QSize(860, 600));
        AppSetConfig->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_2 = new QGridLayout(AppSetConfig);
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        new_data = new QPushButton(AppSetConfig);
        new_data->setObjectName("new_data");
        new_data->setMaximumSize(QSize(40, 23));

        horizontalLayout->addWidget(new_data);

        load_data = new QPushButton(AppSetConfig);
        load_data->setObjectName("load_data");
        load_data->setMaximumSize(QSize(40, 23));

        horizontalLayout->addWidget(load_data);

        save_data = new QPushButton(AppSetConfig);
        save_data->setObjectName("save_data");
        save_data->setMaximumSize(QSize(40, 23));

        horizontalLayout->addWidget(save_data);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(535, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        timer_task = new QPushButton(AppSetConfig);
        timer_task->setObjectName("timer_task");
        timer_task->setMinimumSize(QSize(0, 23));
        timer_task->setMaximumSize(QSize(16777215, 23));

        gridLayout->addWidget(timer_task, 0, 0, 1, 1);

        set_scene = new QPushButton(AppSetConfig);
        set_scene->setObjectName("set_scene");

        gridLayout->addWidget(set_scene, 0, 1, 1, 1);

        time_cal = new QPushButton(AppSetConfig);
        time_cal->setObjectName("time_cal");

        gridLayout->addWidget(time_cal, 1, 0, 1, 1);

        scene_list = new QPushButton(AppSetConfig);
        scene_list->setObjectName("scene_list");

        gridLayout->addWidget(scene_list, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 3, 2, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        add_panel = new QPushButton(AppSetConfig);
        add_panel->setObjectName("add_panel");

        horizontalLayout_2->addWidget(add_panel);

        add_extend = new QPushButton(AppSetConfig);
        add_extend->setObjectName("add_extend");

        horizontalLayout_2->addWidget(add_extend);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(511, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        scrollArea = new QScrollArea(AppSetConfig);
        scrollArea->setObjectName("scrollArea");
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setMinimumSize(QSize(840, 524));
        scrollArea->setStyleSheet(QString::fromUtf8("QScrollArea {\n"
"    border: 1px solid #bdbdbd;\n"
"    border-radius: 4px;\n"
"    padding: 1px;\n"
"} "));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 838, 520));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy1);
        scrollAreaWidgetContents->setLayoutDirection(Qt::LeftToRight);
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 2, 0, 1, 4);


        retranslateUi(AppSetConfig);

        QMetaObject::connectSlotsByName(AppSetConfig);
    } // setupUi

    void retranslateUi(QWidget *AppSetConfig)
    {
        AppSetConfig->setWindowTitle(QCoreApplication::translate("AppSetConfig", "Form", nullptr));
        new_data->setText(QCoreApplication::translate("AppSetConfig", "\346\226\260\345\273\272", nullptr));
        load_data->setText(QCoreApplication::translate("AppSetConfig", "\345\257\274\345\205\245", nullptr));
        save_data->setText(QCoreApplication::translate("AppSetConfig", "\344\277\235\345\255\230", nullptr));
        timer_task->setText(QCoreApplication::translate("AppSetConfig", "\345\256\232\346\227\266\344\273\273\345\212\241", nullptr));
        set_scene->setText(QCoreApplication::translate("AppSetConfig", "\345\210\233\345\273\272\345\234\272\346\231\257", nullptr));
        time_cal->setText(QCoreApplication::translate("AppSetConfig", "\346\240\241\345\207\206\346\227\266\351\227\264", nullptr));
        scene_list->setText(QCoreApplication::translate("AppSetConfig", "\345\234\272\346\231\257\345\210\227\350\241\250", nullptr));
        add_panel->setText(QCoreApplication::translate("AppSetConfig", "\346\267\273\345\212\240\351\235\242\346\235\277", nullptr));
        add_extend->setText(QCoreApplication::translate("AppSetConfig", "\346\267\273\345\212\240\346\211\251\345\261\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AppSetConfig: public Ui_AppSetConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_SET_CONFIG_H
