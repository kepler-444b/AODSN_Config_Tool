/********************************************************************************
** Form generated from reading UI file 'model_panel_1key.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODEL_PANEL_1KEY_H
#define UI_MODEL_PANEL_1KEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModelPanel1Key
{
public:
    QGridLayout *gridLayout;
    QPushButton *key_1;
    QLabel *addr;

    void setupUi(QWidget *ModelPanel1Key)
    {
        if (ModelPanel1Key->objectName().isEmpty())
            ModelPanel1Key->setObjectName("ModelPanel1Key");
        ModelPanel1Key->resize(200, 220);
        ModelPanel1Key->setMinimumSize(QSize(200, 220));
        ModelPanel1Key->setMaximumSize(QSize(200, 220));
        gridLayout = new QGridLayout(ModelPanel1Key);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        key_1 = new QPushButton(ModelPanel1Key);
        key_1->setObjectName("key_1");
        key_1->setMinimumSize(QSize(200, 200));
        key_1->setMaximumSize(QSize(200, 200));

        gridLayout->addWidget(key_1, 0, 0, 1, 1);

        addr = new QLabel(ModelPanel1Key);
        addr->setObjectName("addr");
        addr->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(addr, 1, 0, 1, 1);


        retranslateUi(ModelPanel1Key);

        QMetaObject::connectSlotsByName(ModelPanel1Key);
    } // setupUi

    void retranslateUi(QWidget *ModelPanel1Key)
    {
        ModelPanel1Key->setWindowTitle(QCoreApplication::translate("ModelPanel1Key", "Form", nullptr));
        key_1->setText(QString());
        addr->setText(QCoreApplication::translate("ModelPanel1Key", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModelPanel1Key: public Ui_ModelPanel1Key {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODEL_PANEL_1KEY_H
