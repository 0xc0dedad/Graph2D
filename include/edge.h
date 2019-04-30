#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include <QObject>

#include "node.h"
#include "abstractitem.h"

class Node;

class Edge : public AbstractItem, public QGraphicsLineItem
{
    Q_OBJECT

public:
    explicit Edge(QGraphicsLineItem *parent = Q_NULLPTR);
    explicit Edge(qreal x1, qreal y1, qreal x2, qreal y2,
      QGraphicsItem *parent = Q_NULLPTR);
    ~Edge();

    virtual int id() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
     QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    bool isEdgeSelected() const;
    void setVertices(Node *first, Node *second);
    QPair<Node*, Node*> getVertices() const;
    void setFirstVertex(Node *node);
    void setSecondVertex(Node *node);
    bool isExist(Node *node) const;
    QPointF getFirstVertexPos() const;
    QPointF getSecondVertexPos() const;
    void directable(bool able);
    bool isDirectable() const;
    bool isWeighted() const;
    void setWeight(size_t weight);
    size_t getWeight() const;
    QRectF getArrow() const;

private slots:
    void setSelection(bool);
    void signalSender();

private:
    bool m_is_selected;
    QPair<Node*, Node*> m_vertices;
    bool m_directable;
    bool m_is_weighted;
    size_t m_weight;
};

#endif // EDGE_H
