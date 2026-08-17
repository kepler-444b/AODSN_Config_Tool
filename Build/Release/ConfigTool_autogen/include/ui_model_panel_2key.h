/********************************************************************************
** Form generated from reading UI file 'model_panel_2key.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODEL_PANEL_2KEY_H
#define UI_MODEL_PANEL_2KEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModelPanel2Key
{
public:
    QGridLayout *gridLayout;
    QPushButton *key_2;
    QPushButton *key_1;
    QLabel *addr;

    void setupUi(QWidget *ModelPanel2Key)
    {
        if (ModelPanel2Key->objectName().isEmpty())
            ModelPanel2Key->setObjectName("ModelPanel2Key");
        ModelPanel2Key->resize(200, 220);
        ModelPanel2Key->setMinimumSize(QSize(200, 220));
        ModelPanel2Key->setMaximumSize(QSize(200, 220));
        gridLayout = new QGridLayout(ModelPanel2Key);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        key_2 = new QPushButton(ModelPanel2Key);
        key_2->setObjectName("key_2");
        key_2->setMinimumSize(QSize(100, 200));
        key_2->setMaximumSize(QSize(100, 220));

        gridLayout->addWidget(key_2, 0, 0, 1, 1);

        key_1 = new QPushButton(ModelPanel2Key);
        key_1->setObjectName("key_1");
        key_1->setMinimumSize(QSize(100, 200));
        key_1->setMaximumSize(QSize(100, 220));

        gridLayout->addWidget(key_1, 0, 1, 1, 1);

        addr = new QLabel(ModelPanel2Key);
        addr->setObjectName("addr");
        addr->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(addr, 1, 0, 1, 2);


        retranslateUi(ModelPanel2Key);

        QMetaObject::connectSlotsByName(ModelPanel2Key);
    } // setupUi

    void retranslateUi(QWidget *ModelPanel2Key)
    {
        ModelPanel2Key->setWindowTitle(QCoreApplication::translate("ModelPanel2Key", "Form", nullptr));
        key_2->setText(QString());
        key_1->setText(QString());
        addr->setText(QCoreApplication::translate("ModelPanel2Key", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModelPanel2Key: public Ui_ModelPanel2Key {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODEL_PANEL_2KEY_H
