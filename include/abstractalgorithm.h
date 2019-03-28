#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include <QObject>
#include <QVector>
#include <QList>

#include "mainwindow.h"

class GraphicsView;
class Node;

typedef struct
{
    int code;
    Qt::GlobalColor color;
} code2color_t;


struct Vertex
{
    int id;
    bool visited;

    Vertex(int _id, bool _visited) :
        id (_id),
        visited(_visited)
    { }
};

class AbstractAlgorithm : public QObject
{
    Q_OBJECT

public:
     explicit AbstractAlgorithm(QObject *parent = Q_NULLPTR);
     ~AbstractAlgorithm();
     void initGraph();
     QVector<QVector<int> > getGraph() const;

private:
    bool resizeGraph(GraphicsView *view);
    void debugGraph();
    int getIndex(int val) const;
    void checkBranch(QVector<int> &marked, Node *finish, GraphicsView *view);
    void markEdge(QVector<int> marked, Node *finish, GraphicsView *view, bool reset);

protected:
    virtual void algorithm(Node *start, Node *finish, GraphicsView *view,
        bool order) = 0;
    void markWay(GraphicsView *view, Node *finish, bool reset);
    void clearWay();

private slots:
    void run();

protected:
    QVector<QVector<int> > m_graph;
    QList<int> m_list;
    QVector<int> m_debug;
    QVector<Vertex*> m_way;
    QVector<int> m_raport;
};

extern code2color_t code2color_arr[];
Qt::GlobalColor code2color(const int code);

#endif // ABSTRACTALGORITHM_H
