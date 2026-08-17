#ifndef APP_SET_SCENE_H
#define APP_SET_SCENE_H

#include <QDialog>

namespace Ui {
class AppSetScene;
}

class AppSetScene : public QDialog
{
    Q_OBJECT

public:
    explicit AppSetScene(QWidget *parent = nullptr);
    ~AppSetScene();

private:
    Ui::AppSetScene *ui;
};

#endif // APP_SET_SCENE_H
