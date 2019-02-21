#include "node.h"

unsigned Node::m_counter = 0;

Node::Node(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsEllipseItem(rect, parent),
      m_text(QString::number(++m_counter))
{

}

Node::Node(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
    : QGraphicsEllipseItem(x, y, w, h, parent),
      m_text(QString::number(++m_counter))
{

}

Node::Node(QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent),
      m_text(QString::number(++m_counter))
{

}

Node::~Node()
{

}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
  QWidget *widget)
{
    size_t x_offset = 5; // XXX: Should be added smart calculation (fontMetric)

    QGraphicsEllipseItem::paint(painter, option, widget);
    painter->drawText(QRectF(rect().x() + x_offset, rect().y(), rect().width(),
      rect().height()), m_text);
}

void Node::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QStringList lst;

    lst << "Rename" << "Connect..." << "Move..." << "Delete";

    for(int i=0; i<lst.size(); i++)
        menu.addAction(lst[i]);

    menu.exec(event->screenPos());
}

void Node::setText(const QString string)
{
   int len = 1;

   if (string.length() > len)
        LOG_EXIT("Invalid title", );

   m_text = string;
}
