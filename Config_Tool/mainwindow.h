#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtDebug>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QDialogButtonBox>
#include "app/app_serial.h"
#include "app/app_display.h"
#include "app/app_set_addr.h"
#include "app/app_set_config.h"
#include "app/app_set_net.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:
    void closeEvent(QCloseEvent *event) override; // 重写关闭事件

private slots:
    void on_debug_triggered();
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_ver_triggered();

    void on_readme_triggered();

private:
    Ui::MainWindow *ui             = nullptr;
    AppSerial *SerialWidget        = nullptr;
    AppDisplay *DisplayWidget      = nullptr;

    AppSetAddr *SetAddrWidget      = nullptr;
    AppSetConfig *SetConfigWidget  = nullptr;
    AppSetNet* SetNetWidget        = nullptr;


};
#endif // MAINWINDOW_H
