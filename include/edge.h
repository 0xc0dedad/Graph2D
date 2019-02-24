#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include <QObject>

#include "node.h"

class Node;

class Edge : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

public:
    explicit Edge(QGraphicsLineItem *parent = Q_NULLPTR);
    explicit Edge(qreal x1, qreal y1, qreal x2, qreal y2,
      QGraphicsItem *parent = Q_NULLPTR);
    ~Edge();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
     QWidget *widget);
    bool isEdgeSelected() const;
    void setVertices(Node *first, Node *second);
    QPair<Node*, Node*> getVertices() const;
    void setFirstVertex(Node *node);
    void setSecondVertex(Node *node);
    bool isExist(Node *node) const;

private slots:
    void setSelection(bool);

private:
    bool m_is_selected;
    QPair<Node*, Node*> m_vertices;

};

#endif // EDGE_H
