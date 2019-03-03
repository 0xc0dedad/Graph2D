#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>

#include "settingswindow.h"

class Tab : public QWidget
{
    Q_OBJECT

public:
     explicit Tab(int type, QWidget *parent = Q_NULLPTR);
     ~Tab();

private:
    void layout();
    QListWidget *createAlgorithmsTab(QWidget *parent, QListWidget **list);

private:
    QListWidget *m_list;
};

#endif // TAB_H
