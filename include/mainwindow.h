#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "abstractwindow.h"

class MainWindow : public AbstractWindow
{
    Q_OBJECT

    MainWindow(QWidget *parent = 0);
    MainWindow(const MainWindow &);
    MainWindow &operator =(MainWindow &);

public:
    static MainWindow &instance(QWidget *parent = 0);
    ~MainWindow();

private:
        virtual void layout();
};

#endif // MAINWINDOW_H
