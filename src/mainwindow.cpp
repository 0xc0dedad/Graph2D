#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : AbstractWindow(parent)
{

}

MainWindow::~MainWindow()
{

}

MainWindow &MainWindow::instance(QWidget *parent)
{
    static MainWindow instance(parent);

    return instance;
}

void MainWindow::layout()
{

}
