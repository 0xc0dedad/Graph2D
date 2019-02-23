#ifndef NODE_H
#define NODE_H

#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#include "log.h"
#include "mainwindow.h"
#include "edge.h"

/* XXX:
 * EdgeMode - the same as connection mode for grphicsview */

class Edge;

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
    bool isConnectionMode() const;
    void addEdge(Edge **edge);
    Edge *getSelectedEdge() const;
    QString text() const;
    QVector<Edge*> *getEdges();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    void init();

public slots:
    void setConnectionMode(bool);

private slots:
    void signalSender(); /* XXX: Wrapper for adding additional info */

signals:
    void menuItemSelected(QAction*, Node*);
    void setMode(int);
    void setEdgeSelection(bool);

private:
    QString m_text;
    static unsigned m_counter;
    bool m_edge_mode;
    QVector<Edge*> m_edges;
};

#endif // NODE_H
