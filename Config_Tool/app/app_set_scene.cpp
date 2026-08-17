#include "app_set_scene.h"
#include "ui_app_set_scene.h"

AppSetScene::AppSetScene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppSetScene)
{
    ui->setupUi(this);
}

AppSetScene::~AppSetScene()
{
    delete ui;
}
