/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *debug;
    QAction *ver;
    QAction *readme;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *serial_widget;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *set_addr;
    QWidget *set_config;
    QWidget *set_net;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *help;
    QMenu *about;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1030, 800);
        MainWindow->setMinimumSize(QSize(1030, 800));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        MainWindow->setIconSize(QSize(24, 24));
        debug = new QAction(MainWindow);
        debug->setObjectName("debug");
        ver = new QAction(MainWindow);
        ver->setObjectName("ver");
        readme = new QAction(MainWindow);
        readme->setObjectName("readme");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(800, 500));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        serial_widget = new QWidget(centralwidget);
        serial_widget->setObjectName("serial_widget");
        serial_widget->setEnabled(true);
        serial_widget->setMinimumSize(QSize(200, 80));
        serial_widget->setMaximumSize(QSize(200, 80));

        gridLayout->addWidget(serial_widget, 0, 0, 1, 2);

        listWidget = new QListWidget(centralwidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setMinimumSize(QSize(100, 300));
        listWidget->setMaximumSize(QSize(100, 300));
        listWidget->setSizeIncrement(QSize(100, 0));
        listWidget->setStyleSheet(QString::fromUtf8("QListWidget  {\n"
"    border: 1px solid #bdbdbd;\n"
"    border-radius: 4px;\n"
"    padding: 3px;\n"
"    background-color: white;\n"
"}"));

        gridLayout->addWidget(listWidget, 1, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setMinimumSize(QSize(860, 400));
        stackedWidget->setMaximumSize(QSize(16777215, 16777215));
        stackedWidget->setAutoFillBackground(false);
        stackedWidget->setStyleSheet(QString::fromUtf8("QStackedWidget {\n"
"    border: 1px solid #bdbdbd;\n"
"    border-radius: 4px;\n"
"    padding: 3px;\n"
"    background-color: white;\n"
"}"));
        set_addr = new QWidget();
        set_addr->setObjectName("set_addr");
        stackedWidget->addWidget(set_addr);
        set_config = new QWidget();
        set_config->setObjectName("set_config");
        stackedWidget->addWidget(set_config);
        set_net = new QWidget();
        set_net->setObjectName("set_net");
        stackedWidget->addWidget(set_net);

        gridLayout->addWidget(stackedWidget, 1, 1, 2, 1);

        verticalSpacer = new QSpacerItem(20, 322, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1030, 22));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        help = new QMenu(menubar);
        help->setObjectName("help");
        about = new QMenu(menubar);
        about->setObjectName("about");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(help->menuAction());
        menubar->addAction(about->menuAction());
        menu->addAction(debug);
        help->addAction(readme);
        about->addAction(ver);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\245\245\350\277\252\344\277\241\350\256\276\347\275\256\345\267\245\345\205\267", nullptr));
        debug->setText(QCoreApplication::translate("MainWindow", "\350\260\203\350\257\225\347\252\227\345\217\243", nullptr));
        ver->setText(QCoreApplication::translate("MainWindow", "\350\275\257\344\273\266\347\211\210\346\234\254", nullptr));
        readme->setText(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\350\257\264\346\230\216", nullptr));
#if QT_CONFIG(tooltip)
        readme->setToolTip(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\350\257\264\346\230\216", nullptr));
#endif // QT_CONFIG(tooltip)

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\351\205\215\347\275\256", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("MainWindow", "\344\270\273\346\234\272\351\200\273\350\276\221", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("MainWindow", "\344\270\273\346\234\272\344\277\241\346\201\257", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        menu->setTitle(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267", nullptr));
        help->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        about->setTitle(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
