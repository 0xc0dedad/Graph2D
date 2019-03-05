#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include <QObject>
#include <QVector>

#include "mainwindow.h"

class GraphicsView;

class AbstractAlgorithm : public QObject
{
    Q_OBJECT

public:
     explicit AbstractAlgorithm(QObject *parent = Q_NULLPTR);
     ~AbstractAlgorithm();

private:
    bool resizeGraph(GraphicsView *view);
    void initGraph();
    void debugGraph();

private slots:
    void run();

private:
    QVector<QVector<int> > m_graph;
};

#endif // ABSTRACTALGORITHM_H
