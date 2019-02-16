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
        QToolBar *createSettingsBar(QWidget *parent, QToolBar **bar);

private slots:
        void showSettings();

private:
        QToolBar *m_settings_bar;
};

#endif // MAINWINDOW_H
