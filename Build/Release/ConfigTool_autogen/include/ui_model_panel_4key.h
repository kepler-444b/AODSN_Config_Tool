/********************************************************************************
** Form generated from reading UI file 'model_panel_4key.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODEL_PANEL_4KEY_H
#define UI_MODEL_PANEL_4KEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModelPanel4Key
{
public:
    QGridLayout *gridLayout;
    QPushButton *key_4;
    QPushButton *key_1;
    QPushButton *key_3;
    QPushButton *key_2;
    QLabel *addr;

    void setupUi(QWidget *ModelPanel4Key)
    {
        if (ModelPanel4Key->objectName().isEmpty())
            ModelPanel4Key->setObjectName("ModelPanel4Key");
        ModelPanel4Key->resize(200, 220);
        ModelPanel4Key->setMinimumSize(QSize(200, 220));
        ModelPanel4Key->setMaximumSize(QSize(200, 222));
        ModelPanel4Key->setLayoutDirection(Qt::LeftToRight);
        gridLayout = new QGridLayout(ModelPanel4Key);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        key_4 = new QPushButton(ModelPanel4Key);
        key_4->setObjectName("key_4");
        key_4->setMinimumSize(QSize(100, 100));
        key_4->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(key_4, 0, 0, 1, 1);

        key_1 = new QPushButton(ModelPanel4Key);
        key_1->setObjectName("key_1");
        key_1->setMinimumSize(QSize(100, 100));
        key_1->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(key_1, 0, 1, 1, 1);

        key_3 = new QPushButton(ModelPanel4Key);
        key_3->setObjectName("key_3");
        key_3->setMinimumSize(QSize(100, 100));
        key_3->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(key_3, 1, 0, 1, 1);

        key_2 = new QPushButton(ModelPanel4Key);
        key_2->setObjectName("key_2");
        key_2->setMinimumSize(QSize(100, 100));
        key_2->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(key_2, 1, 1, 1, 1);

        addr = new QLabel(ModelPanel4Key);
        addr->setObjectName("addr");
        addr->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(addr, 2, 0, 1, 2);


        retranslateUi(ModelPanel4Key);

        QMetaObject::connectSlotsByName(ModelPanel4Key);
    } // setupUi

    void retranslateUi(QWidget *ModelPanel4Key)
    {
        ModelPanel4Key->setWindowTitle(QCoreApplication::translate("ModelPanel4Key", "Form", nullptr));
        key_4->setText(QString());
        key_1->setText(QString());
        key_3->setText(QString());
        key_2->setText(QString());
        addr->setText(QCoreApplication::translate("ModelPanel4Key", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModelPanel4Key: public Ui_ModelPanel4Key {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODEL_PANEL_4KEY_H
