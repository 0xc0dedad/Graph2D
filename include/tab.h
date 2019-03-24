#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

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
    QWidget *createStorageTab(QWidget *parent, QWidget **tab);
    QPushButton *createPushButton(QString title, const char *slot);

private:
    void writeGraph(QVector<QVector<int> > graph, QTextStream &stream) const;
    void writeUIConf(QString filename) const;

private slots:
    void download();
    void upload();

private:
    QListWidget *m_list;
    QWidget *m_storage;
};

#endif // TAB_H
