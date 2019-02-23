#ifndef NODE_H
#define NODE_H

#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#include "log.h"
#include "mainwindow.h"

class Node : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

public:
    explicit Node(const QRectF &rect, QGraphicsItem *parent = Q_NULLPTR);
    explicit Node(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = Q_NULLPTR);
    explicit Node(QGraphicsItem *parent = Q_NULLPTR);
    ~Node();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void setText(const QString string);

private:
    void init();

private slots:
    void signalSender(); /* XXX: Wrapper for adding additional info */

signals:
    void menuItemSelected(QAction*, Node*);

private:
    QString m_text;
    static unsigned m_counter;

};

#endif // NODE_H
