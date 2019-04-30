#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include <QObject>
#include <QVector>
#include <QList>

#include <climits>
#include "mainwindow.h"

#define INF INT32_MAX

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
    QVector<int> visited_from;

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

protected:
    virtual void algorithm(Node *start, Node *finish, GraphicsView *view,
        bool order) = 0;
    void checkBranch(QVector<int> &marked, Node *finish, GraphicsView *view);
    QVector<int> markWay(GraphicsView *view, Node *finish, bool reset);
    void markEdge(QVector<int> marked, Node *finish, GraphicsView *view, bool reset);
    int getIndex(int val) const;
    void clearWay();

private slots:
    void run();

protected:
    QVector<QVector<int> > m_graph;
    QList<int> m_list;
    QVector<int> m_debug;
    QVector<Vertex*> m_way;
    QVector<int> m_raport;
    int *m_shortest;
};

extern code2color_t code2color_arr[];
Qt::GlobalColor code2color(const int code);

#endif // ABSTRACTALGORITHM_H
