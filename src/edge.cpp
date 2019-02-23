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

void Edge::setSelection(bool value)
{
    m_is_selected = value;
}
