#include "mainwindow.h"
#include <QSurfaceFormat>
#include <QApplication>

int main(int argc, char *argv[])
{
    QSurfaceFormat fmt;
    fmt.setSamples(8);
    QSurfaceFormat::setDefaultFormat(fmt);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
