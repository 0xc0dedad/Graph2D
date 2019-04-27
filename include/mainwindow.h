#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStringList>
#include <QMessageBox>
#include <QInputDialog>

#include "abstractwindow.h"
#include "graphicsview.h"
#include "settingswindow.h"
#include "abstractalgorithm.h"
#include "raport.h"

class GraphicsView;
class AbstractAlgorithm;
class Raport;

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
    Raport *getRaport() const;
    SettingsWindow *getSettingsWindow() const;
    void createRaport();
    void showRaport();
    void showMessage(QString msg);
    QString openInputDialog(QString title, QString msg, bool *ok);
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
        Raport *m_raport;
};

#endif // MAINWINDOW_H
