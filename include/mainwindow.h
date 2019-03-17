#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStringList>

#include "abstractwindow.h"
#include "graphicsview.h"
#include "settingswindow.h"
#include "abstractalgorithm.h"

class GraphicsView;
class AbstractAlgorithm;

class MainWindow : public AbstractWindow
{
    Q_OBJECT

    MainWindow(QWidget *parent = 0);
    MainWindow(const MainWindow &);
    MainWindow &operator =(MainWindow &);

public:
    static MainWindow &instance(QWidget *parent = 0);
    QToolBar *getSettingsBar() const;
    GraphicsView *getView() const;
    ~MainWindow();

private:
        virtual void layout();
        QToolBar *createSettingsBar(QWidget *parent, QToolBar **bar);
        GraphicsView *createGraphicsView(QWidget *parent, GraphicsView **view);
        void setBackgroundColor();
        AbstractAlgorithm *createAlgorithm(QObject *parent);
        void restoreItems();

private slots:
        void handleControlEvent();
signals:
        void execute();

private:
        QToolBar *m_settings_bar;
        GraphicsView *m_view;
        SettingsWindow *m_settings;
        AbstractAlgorithm *m_algorithm;
};

#endif // MAINWINDOW_H
