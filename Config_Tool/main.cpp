#include "mainwindow.h"
#include <QApplication>
#include <QSharedMemory>
#include <QLockFile>
#include <QIcon>
#include <QStyleFactory>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/app/app.ico"));
    a.setStyle(QStyleFactory::create("windowsvista"));

    QLockFile lockFile(QDir::temp().absoluteFilePath("ConfigTool.lock"));

    if (!lockFile.tryLock())
    {
        QMessageBox::information(nullptr, "提示", "程序已经在运行!");
        return 0;
    }
    MainWindow w;
    w.show();

    return a.exec();
}
