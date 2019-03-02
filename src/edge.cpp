#include "edge.h"

Edge::Edge(QGraphicsLineItem *parent)
    : QGraphicsLineItem(parent),
      m_is_selected(true)
{

}

Edge::Edge(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent)
    : QGraphicsLineItem(x1, y1, x2, y2, parent),
      m_is_selected(true)
{

}

Edge::~Edge()
{

}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
 QWidget *widget)
{
    QGraphicsLineItem::paint(painter, option, widget);
}

bool Edge::isEdgeSelected() const
{
    return m_is_selected;
}

void Edge::setVertices(Node *first, Node *second)
{
    m_vertices.first = first;
    m_vertices.second = second;
}

QPair<Node *, Node *> Edge::getVertices() const
{
    return m_vertices;
}

void Edge::setFirstVertex(Node *node)
{
    m_vertices.first = node;
}

void Edge::setSecondVertex(Node *node)
{
    m_vertices.second = node;
}

bool Edge::isExist(Node *node) const
{
    if (!node)
        LOG_EXIT("Invalid pointer", false);

    if (m_vertices.first == node || m_vertices.second == node)
        return true;

    return false;
}

QPointF Edge::getFirstVertexPos() const
{
    return m_vertices.first->rect().center();
}

QPointF Edge::getSecondVertexPos() const
{
    return m_vertices.second->rect().center();
}

void Edge::setSelection(bool value)
{
    m_is_selected = value;
}
