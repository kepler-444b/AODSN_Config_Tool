/********************************************************************************
** Form generated from reading UI file 'app_set_net.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP_SET_NET_H
#define UI_APP_SET_NET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppSetNet
{
public:
    QPushButton *get_info;
    QPushButton *set_info;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QComboBox *ip_type;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QLineEdit *dev_name;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QLineEdit *dev_key;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *ip;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QLineEdit *gw;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *mac;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *sn;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QLineEdit *dns;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QLineEdit *ver;

    void setupUi(QWidget *AppSetNet)
    {
        if (AppSetNet->objectName().isEmpty())
            AppSetNet->setObjectName("AppSetNet");
        AppSetNet->resize(860, 600);
        AppSetNet->setMinimumSize(QSize(860, 600));
        get_info = new QPushButton(AppSetNet);
        get_info->setObjectName("get_info");
        get_info->setGeometry(QRect(10, 300, 101, 23));
        set_info = new QPushButton(AppSetNet);
        set_info->setObjectName("set_info");
        set_info->setGeometry(QRect(110, 300, 101, 23));
        layoutWidget = new QWidget(AppSetNet);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 260, 119, 24));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");
        label_6->setMinimumSize(QSize(45, 0));

        horizontalLayout_8->addWidget(label_6);

        ip_type = new QComboBox(layoutWidget);
        ip_type->addItem(QString());
        ip_type->addItem(QString());
        ip_type->setObjectName("ip_type");

        horizontalLayout_8->addWidget(ip_type);

        layoutWidget1 = new QWidget(AppSetNet);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(20, 12, 163, 236));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName("label_7");
        label_7->setMinimumSize(QSize(45, 0));

        horizontalLayout->addWidget(label_7);

        dev_name = new QLineEdit(layoutWidget1);
        dev_name->setObjectName("dev_name");
        dev_name->setMinimumSize(QSize(45, 0));

        horizontalLayout->addWidget(dev_name);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName("label_8");
        label_8->setMinimumSize(QSize(45, 0));

        horizontalLayout_2->addWidget(label_8);

        dev_key = new QLineEdit(layoutWidget1);
        dev_key->setObjectName("dev_key");

        horizontalLayout_2->addWidget(dev_key);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(45, 0));

        horizontalLayout_4->addWidget(label_2);

        ip = new QLineEdit(layoutWidget1);
        ip->setObjectName("ip");

        horizontalLayout_4->addWidget(ip);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(45, 0));

        horizontalLayout_6->addWidget(label_4);

        gw = new QLineEdit(layoutWidget1);
        gw->setObjectName("gw");

        horizontalLayout_6->addWidget(gw);


        gridLayout->addLayout(horizontalLayout_6, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(layoutWidget1);
        label->setObjectName("label");
        label->setMinimumSize(QSize(45, 0));

        horizontalLayout_3->addWidget(label);

        mac = new QLineEdit(layoutWidget1);
        mac->setObjectName("mac");

        horizontalLayout_3->addWidget(mac);


        gridLayout->addLayout(horizontalLayout_3, 4, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(45, 0));

        horizontalLayout_5->addWidget(label_3);

        sn = new QLineEdit(layoutWidget1);
        sn->setObjectName("sn");

        horizontalLayout_5->addWidget(sn);


        gridLayout->addLayout(horizontalLayout_5, 5, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(45, 0));

        horizontalLayout_7->addWidget(label_5);

        dns = new QLineEdit(layoutWidget1);
        dns->setObjectName("dns");

        horizontalLayout_7->addWidget(dns);


        gridLayout->addLayout(horizontalLayout_7, 6, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_9 = new QLabel(layoutWidget1);
        label_9->setObjectName("label_9");
        label_9->setMinimumSize(QSize(45, 0));

        horizontalLayout_9->addWidget(label_9);

        ver = new QLineEdit(layoutWidget1);
        ver->setObjectName("ver");

        horizontalLayout_9->addWidget(ver);


        gridLayout->addLayout(horizontalLayout_9, 7, 0, 1, 1);


        retranslateUi(AppSetNet);

        QMetaObject::connectSlotsByName(AppSetNet);
    } // setupUi

    void retranslateUi(QWidget *AppSetNet)
    {
        AppSetNet->setWindowTitle(QCoreApplication::translate("AppSetNet", "Form", nullptr));
        get_info->setText(QCoreApplication::translate("AppSetNet", "\350\216\267\345\217\226\344\277\241\346\201\257", nullptr));
        set_info->setText(QCoreApplication::translate("AppSetNet", "\344\270\213\345\217\221\344\277\241\346\201\257", nullptr));
        label_6->setText(QCoreApplication::translate("AppSetNet", "IP\346\226\271\345\274\217", nullptr));
        ip_type->setItemText(0, QCoreApplication::translate("AppSetNet", "\351\235\231\346\200\201IP", nullptr));
        ip_type->setItemText(1, QCoreApplication::translate("AppSetNet", "\345\212\250\346\200\201IP", nullptr));

        label_7->setText(QCoreApplication::translate("AppSetNet", "\350\256\276\345\244\207ID", nullptr));
        label_8->setText(QCoreApplication::translate("AppSetNet", "\350\256\276\345\244\207KEY", nullptr));
        label_2->setText(QCoreApplication::translate("AppSetNet", "IP", nullptr));
        label_4->setText(QCoreApplication::translate("AppSetNet", "\347\275\221\345\205\263", nullptr));
        label->setText(QCoreApplication::translate("AppSetNet", "MAC", nullptr));
        label_3->setText(QCoreApplication::translate("AppSetNet", "SN", nullptr));
        label_5->setText(QCoreApplication::translate("AppSetNet", "DNS", nullptr));
        label_9->setText(QCoreApplication::translate("AppSetNet", "Ver", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AppSetNet: public Ui_AppSetNet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_SET_NET_H
