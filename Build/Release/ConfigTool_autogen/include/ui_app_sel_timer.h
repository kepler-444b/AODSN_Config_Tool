/********************************************************************************
** Form generated from reading UI file 'app_sel_timer.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP_SEL_TIMER_H
#define UI_APP_SEL_TIMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogTimer
{
public:
    QGridLayout *DialogTimer_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *name_id_1;
    QLineEdit *scene_id_1;
    QLabel *name_hour_1;
    QLineEdit *hour_1;
    QLabel *name_min_1;
    QLineEdit *min_1;
    QCheckBox *checkBox_1;
    QFrame *line_10;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *name_id_2;
    QLineEdit *scene_id_2;
    QLabel *name_hour_2;
    QLineEdit *hour_2;
    QLabel *name_min_2;
    QLineEdit *min_2;
    QCheckBox *checkBox_2;
    QFrame *line_9;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *name_id_3;
    QLineEdit *scene_id_3;
    QLabel *name_hour_3;
    QLineEdit *hour_3;
    QLabel *name_min_3;
    QLineEdit *min_3;
    QCheckBox *checkBox_3;
    QFrame *line_8;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *name_id_4;
    QLineEdit *scene_id_4;
    QLabel *name_hour_4;
    QLineEdit *hour_4;
    QLabel *name_min_4;
    QLineEdit *min_4;
    QCheckBox *checkBox_4;
    QFrame *line_7;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *name_id_5;
    QLineEdit *scene_id_5;
    QLabel *name_hour_5;
    QLineEdit *hour_5;
    QLabel *name_min_5;
    QLineEdit *min_5;
    QCheckBox *checkBox_5;
    QFrame *line_6;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *name_id_6;
    QLineEdit *scene_id_6;
    QLabel *name_hour_6;
    QLineEdit *hour_6;
    QLabel *name_min_6;
    QLineEdit *min_6;
    QCheckBox *checkBox_6;
    QFrame *line_5;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_4;
    QLabel *name_id_7;
    QLineEdit *scene_id_7;
    QLabel *name_hour_7;
    QLineEdit *hour_7;
    QLabel *name_min_7;
    QLineEdit *min_7;
    QCheckBox *checkBox_7;
    QFrame *line_4;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_3;
    QLabel *name_id_8;
    QLineEdit *scene_id_8;
    QLabel *name_hour_8;
    QLineEdit *hour_8;
    QLabel *name_min_8;
    QLineEdit *min_8;
    QCheckBox *checkBox_8;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_2;
    QLabel *name_id_9;
    QLineEdit *scene_id_9;
    QLabel *name_hour_9;
    QLineEdit *hour_9;
    QLabel *name_min_9;
    QLineEdit *min_9;
    QCheckBox *checkBox_9;
    QFrame *line_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *name_id_10;
    QLineEdit *scene_id_10;
    QLabel *name_hour_10;
    QLineEdit *hour_10;
    QLabel *name_min_10;
    QLineEdit *min_10;
    QCheckBox *checkBox_10;
    QFrame *line;
    QPushButton *get_timer_task;
    QPushButton *set_timer_task;

    void setupUi(QDialog *DialogTimer)
    {
        if (DialogTimer->objectName().isEmpty())
            DialogTimer->setObjectName("DialogTimer");
        DialogTimer->resize(270, 450);
        DialogTimer->setMinimumSize(QSize(270, 330));
        DialogTimer->setMaximumSize(QSize(270, 450));
        DialogTimer_2 = new QGridLayout(DialogTimer);
        DialogTimer_2->setObjectName("DialogTimer_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        name_id_1 = new QLabel(DialogTimer);
        name_id_1->setObjectName("name_id_1");

        horizontalLayout_10->addWidget(name_id_1);

        scene_id_1 = new QLineEdit(DialogTimer);
        scene_id_1->setObjectName("scene_id_1");
        scene_id_1->setMinimumSize(QSize(25, 0));
        scene_id_1->setMaximumSize(QSize(25, 16777215));
        scene_id_1->setMaxLength(3);

        horizontalLayout_10->addWidget(scene_id_1);

        name_hour_1 = new QLabel(DialogTimer);
        name_hour_1->setObjectName("name_hour_1");

        horizontalLayout_10->addWidget(name_hour_1);

        hour_1 = new QLineEdit(DialogTimer);
        hour_1->setObjectName("hour_1");
        hour_1->setMinimumSize(QSize(20, 0));
        hour_1->setMaximumSize(QSize(20, 16777215));
        hour_1->setMaxLength(2);

        horizontalLayout_10->addWidget(hour_1);

        name_min_1 = new QLabel(DialogTimer);
        name_min_1->setObjectName("name_min_1");

        horizontalLayout_10->addWidget(name_min_1);

        min_1 = new QLineEdit(DialogTimer);
        min_1->setObjectName("min_1");
        min_1->setMinimumSize(QSize(20, 0));
        min_1->setMaximumSize(QSize(20, 16777215));
        min_1->setMaxLength(2);

        horizontalLayout_10->addWidget(min_1);

        checkBox_1 = new QCheckBox(DialogTimer);
        checkBox_1->setObjectName("checkBox_1");
        checkBox_1->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_10->addWidget(checkBox_1);


        verticalLayout_2->addLayout(horizontalLayout_10);

        line_10 = new QFrame(DialogTimer);
        line_10->setObjectName("line_10");
        line_10->setFrameShape(QFrame::Shape::HLine);
        line_10->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line_10);


        DialogTimer_2->addLayout(verticalLayout_2, 0, 0, 1, 2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        name_id_2 = new QLabel(DialogTimer);
        name_id_2->setObjectName("name_id_2");

        horizontalLayout_9->addWidget(name_id_2);

        scene_id_2 = new QLineEdit(DialogTimer);
        scene_id_2->setObjectName("scene_id_2");
        scene_id_2->setMinimumSize(QSize(25, 0));
        scene_id_2->setMaximumSize(QSize(25, 16777215));
        scene_id_2->setMaxLength(3);

        horizontalLayout_9->addWidget(scene_id_2);

        name_hour_2 = new QLabel(DialogTimer);
        name_hour_2->setObjectName("name_hour_2");

        horizontalLayout_9->addWidget(name_hour_2);

        hour_2 = new QLineEdit(DialogTimer);
        hour_2->setObjectName("hour_2");
        hour_2->setMinimumSize(QSize(20, 0));
        hour_2->setMaximumSize(QSize(20, 16777215));
        hour_2->setMaxLength(2);

        horizontalLayout_9->addWidget(hour_2);

        name_min_2 = new QLabel(DialogTimer);
        name_min_2->setObjectName("name_min_2");

        horizontalLayout_9->addWidget(name_min_2);

        min_2 = new QLineEdit(DialogTimer);
        min_2->setObjectName("min_2");
        min_2->setMinimumSize(QSize(20, 0));
        min_2->setMaximumSize(QSize(20, 16777215));
        min_2->setMaxLength(2);

        horizontalLayout_9->addWidget(min_2);

        checkBox_2 = new QCheckBox(DialogTimer);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_9->addWidget(checkBox_2);


        verticalLayout_3->addLayout(horizontalLayout_9);

        line_9 = new QFrame(DialogTimer);
        line_9->setObjectName("line_9");
        line_9->setFrameShape(QFrame::Shape::HLine);
        line_9->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line_9);


        DialogTimer_2->addLayout(verticalLayout_3, 1, 0, 1, 2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        name_id_3 = new QLabel(DialogTimer);
        name_id_3->setObjectName("name_id_3");

        horizontalLayout_8->addWidget(name_id_3);

        scene_id_3 = new QLineEdit(DialogTimer);
        scene_id_3->setObjectName("scene_id_3");
        scene_id_3->setMinimumSize(QSize(25, 0));
        scene_id_3->setMaximumSize(QSize(25, 16777215));
        scene_id_3->setMaxLength(3);

        horizontalLayout_8->addWidget(scene_id_3);

        name_hour_3 = new QLabel(DialogTimer);
        name_hour_3->setObjectName("name_hour_3");

        horizontalLayout_8->addWidget(name_hour_3);

        hour_3 = new QLineEdit(DialogTimer);
        hour_3->setObjectName("hour_3");
        hour_3->setMinimumSize(QSize(20, 0));
        hour_3->setMaximumSize(QSize(20, 16777215));
        hour_3->setMaxLength(2);

        horizontalLayout_8->addWidget(hour_3);

        name_min_3 = new QLabel(DialogTimer);
        name_min_3->setObjectName("name_min_3");

        horizontalLayout_8->addWidget(name_min_3);

        min_3 = new QLineEdit(DialogTimer);
        min_3->setObjectName("min_3");
        min_3->setMinimumSize(QSize(20, 0));
        min_3->setMaximumSize(QSize(20, 16777215));
        min_3->setMaxLength(2);

        horizontalLayout_8->addWidget(min_3);

        checkBox_3 = new QCheckBox(DialogTimer);
        checkBox_3->setObjectName("checkBox_3");
        checkBox_3->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_8->addWidget(checkBox_3);


        verticalLayout_4->addLayout(horizontalLayout_8);

        line_8 = new QFrame(DialogTimer);
        line_8->setObjectName("line_8");
        line_8->setFrameShape(QFrame::Shape::HLine);
        line_8->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_4->addWidget(line_8);


        DialogTimer_2->addLayout(verticalLayout_4, 2, 0, 1, 2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        name_id_4 = new QLabel(DialogTimer);
        name_id_4->setObjectName("name_id_4");

        horizontalLayout_7->addWidget(name_id_4);

        scene_id_4 = new QLineEdit(DialogTimer);
        scene_id_4->setObjectName("scene_id_4");
        scene_id_4->setMinimumSize(QSize(25, 0));
        scene_id_4->setMaximumSize(QSize(25, 16777215));
        scene_id_4->setMaxLength(3);

        horizontalLayout_7->addWidget(scene_id_4);

        name_hour_4 = new QLabel(DialogTimer);
        name_hour_4->setObjectName("name_hour_4");

        horizontalLayout_7->addWidget(name_hour_4);

        hour_4 = new QLineEdit(DialogTimer);
        hour_4->setObjectName("hour_4");
        hour_4->setMinimumSize(QSize(20, 0));
        hour_4->setMaximumSize(QSize(20, 16777215));
        hour_4->setMaxLength(2);

        horizontalLayout_7->addWidget(hour_4);

        name_min_4 = new QLabel(DialogTimer);
        name_min_4->setObjectName("name_min_4");

        horizontalLayout_7->addWidget(name_min_4);

        min_4 = new QLineEdit(DialogTimer);
        min_4->setObjectName("min_4");
        min_4->setMinimumSize(QSize(20, 0));
        min_4->setMaximumSize(QSize(20, 16777215));
        min_4->setMaxLength(2);

        horizontalLayout_7->addWidget(min_4);

        checkBox_4 = new QCheckBox(DialogTimer);
        checkBox_4->setObjectName("checkBox_4");
        checkBox_4->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_7->addWidget(checkBox_4);


        verticalLayout_5->addLayout(horizontalLayout_7);

        line_7 = new QFrame(DialogTimer);
        line_7->setObjectName("line_7");
        line_7->setFrameShape(QFrame::Shape::HLine);
        line_7->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_5->addWidget(line_7);


        DialogTimer_2->addLayout(verticalLayout_5, 3, 0, 1, 2);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        name_id_5 = new QLabel(DialogTimer);
        name_id_5->setObjectName("name_id_5");

        horizontalLayout_6->addWidget(name_id_5);

        scene_id_5 = new QLineEdit(DialogTimer);
        scene_id_5->setObjectName("scene_id_5");
        scene_id_5->setMinimumSize(QSize(25, 0));
        scene_id_5->setMaximumSize(QSize(25, 16777215));
        scene_id_5->setMaxLength(3);

        horizontalLayout_6->addWidget(scene_id_5);

        name_hour_5 = new QLabel(DialogTimer);
        name_hour_5->setObjectName("name_hour_5");

        horizontalLayout_6->addWidget(name_hour_5);

        hour_5 = new QLineEdit(DialogTimer);
        hour_5->setObjectName("hour_5");
        hour_5->setMinimumSize(QSize(20, 0));
        hour_5->setMaximumSize(QSize(20, 16777215));
        hour_5->setMaxLength(2);

        horizontalLayout_6->addWidget(hour_5);

        name_min_5 = new QLabel(DialogTimer);
        name_min_5->setObjectName("name_min_5");

        horizontalLayout_6->addWidget(name_min_5);

        min_5 = new QLineEdit(DialogTimer);
        min_5->setObjectName("min_5");
        min_5->setMinimumSize(QSize(20, 0));
        min_5->setMaximumSize(QSize(20, 16777215));
        min_5->setMaxLength(2);

        horizontalLayout_6->addWidget(min_5);

        checkBox_5 = new QCheckBox(DialogTimer);
        checkBox_5->setObjectName("checkBox_5");
        checkBox_5->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_6->addWidget(checkBox_5);


        verticalLayout_6->addLayout(horizontalLayout_6);

        line_6 = new QFrame(DialogTimer);
        line_6->setObjectName("line_6");
        line_6->setFrameShape(QFrame::Shape::HLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_6->addWidget(line_6);


        DialogTimer_2->addLayout(verticalLayout_6, 4, 0, 1, 2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        name_id_6 = new QLabel(DialogTimer);
        name_id_6->setObjectName("name_id_6");

        horizontalLayout_5->addWidget(name_id_6);

        scene_id_6 = new QLineEdit(DialogTimer);
        scene_id_6->setObjectName("scene_id_6");
        scene_id_6->setMinimumSize(QSize(25, 0));
        scene_id_6->setMaximumSize(QSize(25, 16777215));
        scene_id_6->setMaxLength(3);

        horizontalLayout_5->addWidget(scene_id_6);

        name_hour_6 = new QLabel(DialogTimer);
        name_hour_6->setObjectName("name_hour_6");

        horizontalLayout_5->addWidget(name_hour_6);

        hour_6 = new QLineEdit(DialogTimer);
        hour_6->setObjectName("hour_6");
        hour_6->setMinimumSize(QSize(20, 0));
        hour_6->setMaximumSize(QSize(20, 16777215));
        hour_6->setMaxLength(2);

        horizontalLayout_5->addWidget(hour_6);

        name_min_6 = new QLabel(DialogTimer);
        name_min_6->setObjectName("name_min_6");

        horizontalLayout_5->addWidget(name_min_6);

        min_6 = new QLineEdit(DialogTimer);
        min_6->setObjectName("min_6");
        min_6->setMinimumSize(QSize(20, 0));
        min_6->setMaximumSize(QSize(20, 16777215));
        min_6->setMaxLength(2);

        horizontalLayout_5->addWidget(min_6);

        checkBox_6 = new QCheckBox(DialogTimer);
        checkBox_6->setObjectName("checkBox_6");
        checkBox_6->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_5->addWidget(checkBox_6);


        verticalLayout_7->addLayout(horizontalLayout_5);

        line_5 = new QFrame(DialogTimer);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_7->addWidget(line_5);


        DialogTimer_2->addLayout(verticalLayout_7, 5, 0, 1, 2);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        name_id_7 = new QLabel(DialogTimer);
        name_id_7->setObjectName("name_id_7");

        horizontalLayout_4->addWidget(name_id_7);

        scene_id_7 = new QLineEdit(DialogTimer);
        scene_id_7->setObjectName("scene_id_7");
        scene_id_7->setMinimumSize(QSize(25, 0));
        scene_id_7->setMaximumSize(QSize(25, 16777215));
        scene_id_7->setMaxLength(3);

        horizontalLayout_4->addWidget(scene_id_7);

        name_hour_7 = new QLabel(DialogTimer);
        name_hour_7->setObjectName("name_hour_7");

        horizontalLayout_4->addWidget(name_hour_7);

        hour_7 = new QLineEdit(DialogTimer);
        hour_7->setObjectName("hour_7");
        hour_7->setMinimumSize(QSize(20, 0));
        hour_7->setMaximumSize(QSize(20, 16777215));
        hour_7->setMaxLength(2);

        horizontalLayout_4->addWidget(hour_7);

        name_min_7 = new QLabel(DialogTimer);
        name_min_7->setObjectName("name_min_7");

        horizontalLayout_4->addWidget(name_min_7);

        min_7 = new QLineEdit(DialogTimer);
        min_7->setObjectName("min_7");
        min_7->setMinimumSize(QSize(20, 0));
        min_7->setMaximumSize(QSize(20, 16777215));
        min_7->setMaxLength(2);

        horizontalLayout_4->addWidget(min_7);

        checkBox_7 = new QCheckBox(DialogTimer);
        checkBox_7->setObjectName("checkBox_7");
        checkBox_7->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_4->addWidget(checkBox_7);


        verticalLayout_8->addLayout(horizontalLayout_4);

        line_4 = new QFrame(DialogTimer);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_8->addWidget(line_4);


        DialogTimer_2->addLayout(verticalLayout_8, 6, 0, 1, 2);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        name_id_8 = new QLabel(DialogTimer);
        name_id_8->setObjectName("name_id_8");

        horizontalLayout_3->addWidget(name_id_8);

        scene_id_8 = new QLineEdit(DialogTimer);
        scene_id_8->setObjectName("scene_id_8");
        scene_id_8->setMinimumSize(QSize(25, 0));
        scene_id_8->setMaximumSize(QSize(25, 16777215));
        scene_id_8->setMaxLength(3);

        horizontalLayout_3->addWidget(scene_id_8);

        name_hour_8 = new QLabel(DialogTimer);
        name_hour_8->setObjectName("name_hour_8");

        horizontalLayout_3->addWidget(name_hour_8);

        hour_8 = new QLineEdit(DialogTimer);
        hour_8->setObjectName("hour_8");
        hour_8->setMinimumSize(QSize(20, 0));
        hour_8->setMaximumSize(QSize(20, 16777215));
        hour_8->setMaxLength(2);

        horizontalLayout_3->addWidget(hour_8);

        name_min_8 = new QLabel(DialogTimer);
        name_min_8->setObjectName("name_min_8");

        horizontalLayout_3->addWidget(name_min_8);

        min_8 = new QLineEdit(DialogTimer);
        min_8->setObjectName("min_8");
        min_8->setMinimumSize(QSize(20, 0));
        min_8->setMaximumSize(QSize(20, 16777215));
        min_8->setMaxLength(2);

        horizontalLayout_3->addWidget(min_8);

        checkBox_8 = new QCheckBox(DialogTimer);
        checkBox_8->setObjectName("checkBox_8");
        checkBox_8->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_3->addWidget(checkBox_8);


        verticalLayout_9->addLayout(horizontalLayout_3);

        line_3 = new QFrame(DialogTimer);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_9->addWidget(line_3);


        DialogTimer_2->addLayout(verticalLayout_9, 7, 0, 1, 2);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        name_id_9 = new QLabel(DialogTimer);
        name_id_9->setObjectName("name_id_9");

        horizontalLayout_2->addWidget(name_id_9);

        scene_id_9 = new QLineEdit(DialogTimer);
        scene_id_9->setObjectName("scene_id_9");
        scene_id_9->setMinimumSize(QSize(25, 0));
        scene_id_9->setMaximumSize(QSize(25, 16777215));
        scene_id_9->setMaxLength(3);

        horizontalLayout_2->addWidget(scene_id_9);

        name_hour_9 = new QLabel(DialogTimer);
        name_hour_9->setObjectName("name_hour_9");

        horizontalLayout_2->addWidget(name_hour_9);

        hour_9 = new QLineEdit(DialogTimer);
        hour_9->setObjectName("hour_9");
        hour_9->setMinimumSize(QSize(20, 0));
        hour_9->setMaximumSize(QSize(20, 16777215));
        hour_9->setMaxLength(2);

        horizontalLayout_2->addWidget(hour_9);

        name_min_9 = new QLabel(DialogTimer);
        name_min_9->setObjectName("name_min_9");

        horizontalLayout_2->addWidget(name_min_9);

        min_9 = new QLineEdit(DialogTimer);
        min_9->setObjectName("min_9");
        min_9->setMinimumSize(QSize(20, 0));
        min_9->setMaximumSize(QSize(20, 16777215));
        min_9->setMaxLength(2);

        horizontalLayout_2->addWidget(min_9);

        checkBox_9 = new QCheckBox(DialogTimer);
        checkBox_9->setObjectName("checkBox_9");
        checkBox_9->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_2->addWidget(checkBox_9);


        verticalLayout_10->addLayout(horizontalLayout_2);

        line_2 = new QFrame(DialogTimer);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_10->addWidget(line_2);


        DialogTimer_2->addLayout(verticalLayout_10, 8, 0, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        name_id_10 = new QLabel(DialogTimer);
        name_id_10->setObjectName("name_id_10");

        horizontalLayout->addWidget(name_id_10);

        scene_id_10 = new QLineEdit(DialogTimer);
        scene_id_10->setObjectName("scene_id_10");
        scene_id_10->setMinimumSize(QSize(25, 0));
        scene_id_10->setMaximumSize(QSize(25, 16777215));
        scene_id_10->setMaxLength(3);

        horizontalLayout->addWidget(scene_id_10);

        name_hour_10 = new QLabel(DialogTimer);
        name_hour_10->setObjectName("name_hour_10");

        horizontalLayout->addWidget(name_hour_10);

        hour_10 = new QLineEdit(DialogTimer);
        hour_10->setObjectName("hour_10");
        hour_10->setMinimumSize(QSize(20, 0));
        hour_10->setMaximumSize(QSize(20, 16777215));
        hour_10->setMaxLength(2);

        horizontalLayout->addWidget(hour_10);

        name_min_10 = new QLabel(DialogTimer);
        name_min_10->setObjectName("name_min_10");

        horizontalLayout->addWidget(name_min_10);

        min_10 = new QLineEdit(DialogTimer);
        min_10->setObjectName("min_10");
        min_10->setMinimumSize(QSize(20, 0));
        min_10->setMaximumSize(QSize(20, 16777215));
        min_10->setMaxLength(2);

        horizontalLayout->addWidget(min_10);

        checkBox_10 = new QCheckBox(DialogTimer);
        checkBox_10->setObjectName("checkBox_10");
        checkBox_10->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout->addWidget(checkBox_10);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(DialogTimer);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);


        DialogTimer_2->addLayout(verticalLayout, 9, 0, 1, 2);

        get_timer_task = new QPushButton(DialogTimer);
        get_timer_task->setObjectName("get_timer_task");

        DialogTimer_2->addWidget(get_timer_task, 10, 0, 1, 1);

        set_timer_task = new QPushButton(DialogTimer);
        set_timer_task->setObjectName("set_timer_task");

        DialogTimer_2->addWidget(set_timer_task, 10, 1, 1, 1);


        retranslateUi(DialogTimer);

        QMetaObject::connectSlotsByName(DialogTimer);
    } // setupUi

    void retranslateUi(QDialog *DialogTimer)
    {
        DialogTimer->setWindowTitle(QCoreApplication::translate("DialogTimer", "\345\256\232\346\227\266\344\273\273\345\212\241", nullptr));
        name_id_1->setText(QCoreApplication::translate("DialogTimer", "0 \345\234\272\346\231\257ID", nullptr));
        scene_id_1->setText(QString());
        name_hour_1->setText(QCoreApplication::translate("DialogTimer", "\345\260\217\346\227\266", nullptr));
        hour_1->setText(QString());
        name_min_1->setText(QCoreApplication::translate("DialogTimer", "\345\210\206\351\222\237", nullptr));
        min_1->setText(QString());
        checkBox_1->setText(QCoreApplication::translate("DialogTimer", "\345\220\257\347\224\250", nullptr));
        name_id_2->setText(QCoreApplication::translate("DialogTimer", "1 \345\234\272\346\231\257ID", nullptr));
        scene_id_2->setText(QString());
        name_hour_2->setText(QCoreApplication::translate("DialogTimer", "\345\260\217\346\227\266", nullptr));
        hour_2->setText(QString());
        name_min_2->setText(QCoreApplication::translate("DialogTimer", "\345\210\206\351\222\237", nullptr));
        min_2->setText(QString());
        checkBox_2->setText(QCoreApplication::translate("DialogTimer", "\345\220\257\347\224\250", nullptr));
        name_id_3->setText(QCoreApplication::translate("DialogTimer", "2 \345\234\272\346\231\257ID", nullptr));
        scene_id_3->setText(QString());
        name_hour_3->setText(QCoreApplication::translate("DialogTimer", "\345\260\217\346\227\266", nullptr));
        hour_3->setText(QString());
        name_min_3->setText(QCoreApplication::translate("DialogTimer", "\345\210\206\351\222\237", nullptr));
        min_3->setText(QString());
        checkBox_3->setText(QCoreApplication::translate("DialogTimer", "\345\220\257\347\224\250", nullptr));
        name_id_4->setText(QCoreApplication::translate("DialogTimer", "3 \345\234\272\346\231\257ID", nullptr));
        scene_id_4->setText(QString());
        name_hour_4->setText(QCoreApplication::translate("DialogTimer", "\345\260\217\346\227\266", nullptr));
        hour_4->setText(QString());
        name_min_4->setText(QCoreApplication::translate("DialogTimer", "\345\210\206\351\222\237", nullptr));
        min_4->setText(QString());
        checkBox_4->setText(QCoreApplication::translate("DialogTimer", "\345\220\257\347\224\250", nullptr));
        name_id_5->setText(QCoreApplication::translate("DialogTimer", "4 \345\234\272\346\231\257ID", nullptr));
        scene_id_5->setText(QString());
        name_hour_5->setText(QCoreApplication::translate("DialogTimer", "\345\260\217\346\227\266", nullptr));
        hour_5->setText(QString());
        name_min_5->setText(QCoreApplication::translate("DialogTimer", "\345\210\206\351\222\237", nullptr));
        min_5->setText(QString());
        checkBox_5->setText(QCoreApplication::translate("DialogTimer", "\345\220\257\347\224\250", nullptr));
        name_id_6->setText(QCoreApplication::translate("DialogTimer", "5 \345\234\272\346\231\257ID", nullptr));
        scene_id_6->setText(QString());
        name_hour_6->setText(QCoreApplication::translate("DialogTimer", "\345\260\217\346\227\266", nullptr));
        hour_6->setText(QString());
        name_min_6->setText(QCoreApplication::translate("DialogTimer", "\345\210\206\351\222\237", nullptr));
        min_6->setText(QString());
        checkBox_6->setText(QCoreApplication::translate("DialogTimer", "\345\220\257\347\224\250", nullptr));
        name_id_7->setText(QCoreApplication::translate("DialogTimer", "6 \345\234\272\346\231\257ID", nullptr));
        scene_id_7->setText(QString());
        name_hour_7->setText(QCoreApplication::translate("DialogTimer", "\345\260\217\346\227\266", nullptr));
        hour_7->setText(QString());
        name_min_7->setText(QCoreApplication::translate("DialogTimer", "\345\210\206\351\222\237", nullptr));
        min_7->setText(QString());
        checkBox_7->setText(QCoreApplication::translate("DialogTimer", "\345\220\257\347\224\250", nullptr));
        name_id_8->setText(QCoreApplication::translate("DialogTimer", "7 \345\234\272\346\231\257ID", nullptr));
        scene_id_8->setText(QString());
        name_hour_8->setText(QCoreApplication::translate("DialogTimer", "\345\260\217\346\227\266", nullptr));
        hour_8->setText(QString());
        name_min_8->setText(QCoreApplication::translate("DialogTimer", "\345\210\206\351\222\237", nullptr));
        min_8->setText(QString());
        checkBox_8->setText(QCoreApplication::translate("DialogTimer", "\345\220\257\347\224\250", nullptr));
        name_id_9->setText(QCoreApplication::translate("DialogTimer", "8 \345\234\272\346\231\257ID", nullptr));
        scene_id_9->setText(QString());
        name_hour_9->setText(QCoreApplication::translate("DialogTimer", "\345\260\217\346\227\266", nullptr));
        hour_9->setText(QString());
        name_min_9->setText(QCoreApplication::translate("DialogTimer", "\345\210\206\351\222\237", nullptr));
        min_9->setText(QString());
        checkBox_9->setText(QCoreApplication::translate("DialogTimer", "\345\220\257\347\224\250", nullptr));
        name_id_10->setText(QCoreApplication::translate("DialogTimer", "9 \345\234\272\346\231\257ID", nullptr));
        scene_id_10->setText(QString());
        name_hour_10->setText(QCoreApplication::translate("DialogTimer", "\345\260\217\346\227\266", nullptr));
        hour_10->setText(QString());
        name_min_10->setText(QCoreApplication::translate("DialogTimer", "\345\210\206\351\222\237", nullptr));
        min_10->setText(QString());
        checkBox_10->setText(QCoreApplication::translate("DialogTimer", "\345\220\257\347\224\250", nullptr));
        get_timer_task->setText(QCoreApplication::translate("DialogTimer", "\350\216\267\345\217\226\344\273\273\345\212\241", nullptr));
        set_timer_task->setText(QCoreApplication::translate("DialogTimer", "\344\270\213\345\217\221\344\273\273\345\212\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogTimer: public Ui_DialogTimer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_SEL_TIMER_H
