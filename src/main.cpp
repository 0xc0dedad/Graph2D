#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow::instance();
    MainWindow::instance().showFullScreen();

    return a.exec();
}
