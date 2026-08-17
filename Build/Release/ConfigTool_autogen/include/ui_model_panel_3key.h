/********************************************************************************
** Form generated from reading UI file 'model_panel_3key.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODEL_PANEL_3KEY_H
#define UI_MODEL_PANEL_3KEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModelPanel3Key
{
public:
    QGridLayout *gridLayout;
    QPushButton *key_3;
    QLabel *addr;
    QPushButton *key_2;
    QPushButton *key_1;

    void setupUi(QWidget *ModelPanel3Key)
    {
        if (ModelPanel3Key->objectName().isEmpty())
            ModelPanel3Key->setObjectName("ModelPanel3Key");
        ModelPanel3Key->resize(200, 220);
        ModelPanel3Key->setMinimumSize(QSize(200, 220));
        ModelPanel3Key->setMaximumSize(QSize(200, 220));
        gridLayout = new QGridLayout(ModelPanel3Key);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        key_3 = new QPushButton(ModelPanel3Key);
        key_3->setObjectName("key_3");
        key_3->setMinimumSize(QSize(66, 200));
        key_3->setMaximumSize(QSize(66, 200));

        gridLayout->addWidget(key_3, 0, 0, 1, 1);

        addr = new QLabel(ModelPanel3Key);
        addr->setObjectName("addr");
        addr->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(addr, 1, 1, 1, 1);

        key_2 = new QPushButton(ModelPanel3Key);
        key_2->setObjectName("key_2");
        key_2->setMinimumSize(QSize(66, 200));
        key_2->setMaximumSize(QSize(66, 200));

        gridLayout->addWidget(key_2, 0, 1, 1, 1);

        key_1 = new QPushButton(ModelPanel3Key);
        key_1->setObjectName("key_1");
        key_1->setMinimumSize(QSize(66, 200));
        key_1->setMaximumSize(QSize(66, 200));

        gridLayout->addWidget(key_1, 0, 2, 1, 1);


        retranslateUi(ModelPanel3Key);

        QMetaObject::connectSlotsByName(ModelPanel3Key);
    } // setupUi

    void retranslateUi(QWidget *ModelPanel3Key)
    {
        ModelPanel3Key->setWindowTitle(QCoreApplication::translate("ModelPanel3Key", "Form", nullptr));
        key_3->setText(QString());
        addr->setText(QCoreApplication::translate("ModelPanel3Key", "TextLabel", nullptr));
        key_2->setText(QString());
        key_1->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ModelPanel3Key: public Ui_ModelPanel3Key {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODEL_PANEL_3KEY_H
