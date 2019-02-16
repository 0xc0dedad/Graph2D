#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "abstractwindow.h"
#include "graphicsview.h"

class GraphicsView;

class MainWindow : public AbstractWindow
{
    Q_OBJECT

    MainWindow(QWidget *parent = 0);
    MainWindow(const MainWindow &);
    MainWindow &operator =(MainWindow &);

public:
    static MainWindow &instance(QWidget *parent = 0);
    QToolBar *getSettingsBar() const;
    ~MainWindow();

private:
        virtual void layout();
        QToolBar *createSettingsBar(QWidget *parent, QToolBar **bar);
        GraphicsView *createGraphicsView(QWidget *parent, GraphicsView **view);
        void setBackgroundColor();

private slots:
        void showSettings();

private:
        QToolBar *m_settings_bar;
        GraphicsView *m_view;
};

#endif // MAINWINDOW_H
