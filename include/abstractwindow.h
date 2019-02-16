#ifndef ABSTRACTWINDOW_H
#define ABSTRACTWINDOW_H

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QApplication>

#include "log.h"

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
            QGroupBox *createGroupBox(QWidget *parent, QGroupBox **group);
            QLabel *createLabel(QString title, QFont font, QLabel **lbl);
    public:
            ~AbstractWindow();
            QString pathToImages() const;
};

#endif // ABSTRACTWINDOW_H
