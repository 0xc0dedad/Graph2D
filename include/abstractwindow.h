#ifndef ABSTRACTWINDOW_H
#define ABSTRACTWINDOW_H

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>

class AbstractWindow : public QWidget
{
    Q_OBJECT

    protected:
            AbstractWindow(QWidget *parent = 0);
            virtual void layout() = 0;
            QToolBar *createToolBar(QWidget *parent, QToolBar **bar);
            QAction *addBarAction(QToolBar **bar, QIcon icon, QString tooltip,
                              QSize size, QWidget *handler, const char *slot,
                              bool is_checkable);
    public:
            ~AbstractWindow();
};

#endif // ABSTRACTWINDOW_H
