#ifndef NODE_H
#define NODE_H

#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#include "log.h"

class Node : public QGraphicsEllipseItem
{
public:
    explicit Node(const QRectF &rect, QGraphicsItem *parent = Q_NULLPTR);
    explicit Node(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = Q_NULLPTR);
    explicit Node(QGraphicsItem *parent = Q_NULLPTR);
    ~Node();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void setText(const QString string);

private:
    QString m_text;
    static unsigned m_counter;

};

#endif // NODE_H
