/********************************************************************************
** Form generated from reading UI file 'model_panel_6key.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODEL_PANEL_6KEY_H
#define UI_MODEL_PANEL_6KEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModelPanel6Key
{
public:
    QGridLayout *gridLayout;
    QPushButton *key_4;
    QPushButton *key_5;
    QPushButton *key_1;
    QPushButton *key_3;
    QPushButton *key_2;
    QLabel *addr;
    QPushButton *key_6;

    void setupUi(QWidget *ModelPanel6Key)
    {
        if (ModelPanel6Key->objectName().isEmpty())
            ModelPanel6Key->setObjectName("ModelPanel6Key");
        ModelPanel6Key->resize(200, 220);
        ModelPanel6Key->setMinimumSize(QSize(200, 220));
        ModelPanel6Key->setMaximumSize(QSize(200, 220));
        ModelPanel6Key->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(ModelPanel6Key);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        key_4 = new QPushButton(ModelPanel6Key);
        key_4->setObjectName("key_4");
        key_4->setMinimumSize(QSize(66, 100));
        key_4->setMaximumSize(QSize(66, 100));

        gridLayout->addWidget(key_4, 0, 0, 1, 1);

        key_5 = new QPushButton(ModelPanel6Key);
        key_5->setObjectName("key_5");
        key_5->setMinimumSize(QSize(66, 100));
        key_5->setMaximumSize(QSize(66, 100));

        gridLayout->addWidget(key_5, 0, 1, 1, 1);

        key_1 = new QPushButton(ModelPanel6Key);
        key_1->setObjectName("key_1");
        key_1->setEnabled(true);
        key_1->setMinimumSize(QSize(66, 100));
        key_1->setMaximumSize(QSize(66, 100));
        key_1->setCheckable(false);

        gridLayout->addWidget(key_1, 0, 2, 1, 1);

        key_3 = new QPushButton(ModelPanel6Key);
        key_3->setObjectName("key_3");
        key_3->setMinimumSize(QSize(66, 100));
        key_3->setMaximumSize(QSize(66, 100));

        gridLayout->addWidget(key_3, 1, 0, 1, 1);

        key_2 = new QPushButton(ModelPanel6Key);
        key_2->setObjectName("key_2");
        key_2->setMinimumSize(QSize(66, 100));
        key_2->setMaximumSize(QSize(66, 100));
        key_2->setAutoFillBackground(false);
        key_2->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(key_2, 1, 2, 1, 1);

        addr = new QLabel(ModelPanel6Key);
        addr->setObjectName("addr");
        addr->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(addr, 2, 1, 1, 1);

        key_6 = new QPushButton(ModelPanel6Key);
        key_6->setObjectName("key_6");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(key_6->sizePolicy().hasHeightForWidth());
        key_6->setSizePolicy(sizePolicy);
        key_6->setMinimumSize(QSize(66, 100));
        key_6->setMaximumSize(QSize(66, 100));
        key_6->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(key_6, 1, 1, 1, 1);


        retranslateUi(ModelPanel6Key);

        QMetaObject::connectSlotsByName(ModelPanel6Key);
    } // setupUi

    void retranslateUi(QWidget *ModelPanel6Key)
    {
        ModelPanel6Key->setWindowTitle(QCoreApplication::translate("ModelPanel6Key", "Form", nullptr));
        key_4->setText(QString());
        key_5->setText(QString());
        key_1->setText(QString());
        key_3->setText(QString());
        key_2->setText(QString());
        addr->setText(QCoreApplication::translate("ModelPanel6Key", "TextLabel", nullptr));
        key_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ModelPanel6Key: public Ui_ModelPanel6Key {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODEL_PANEL_6KEY_H
