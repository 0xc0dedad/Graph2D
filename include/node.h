#ifndef NODE_H
#define NODE_H

#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#include "log.h"
#include "mainwindow.h"
#include "edge.h"
#include "abstractitem.h"

/* XXX:
 * EdgeMode - the same as connection mode for grphicsview */

class Edge;

class Node : public AbstractItem, public QGraphicsEllipseItem
{
    Q_OBJECT

public:
    explicit Node(const QRectF &rect, QGraphicsItem *parent = Q_NULLPTR);
    explicit Node(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = Q_NULLPTR);
    explicit Node(QGraphicsItem *parent = Q_NULLPTR);
    ~Node();

    virtual int id() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void setText(const QString string);
    bool isConnectionMode() const;
    void addNeighbor(Node *node);
    void delNeighbor(Node *node);
    bool isAmongNeighbors(Node *node) const;
    Edge *getSelectedEdge() const;
    QString text() const;

    void addEdge(Node *first, Node *second, Edge **edge);
    bool delEdge(Edge *edge);
    void modifyEdgeVertices(Edge *edge, Node *first, Node *second);
    Edge *findConnectedEdge(Node *node) const;

    /*XXX: find edge/neighbor in corresponded vector */
    int findEdge(Edge *edge) const;
    int findNeighbor(Node *node) const;

    /* Can modify data. Not trivial logic */
    QVector<Edge*> *getEdges();
    QVector<Node*> *getNeighbors();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    void init();
    int findValidName() const;

public slots:
    void setConnectionMode(bool);

private slots:
    void signalSender(); /* XXX: Wrapper for adding additional info */

signals:
    void setMode(int);
    void setEdgeSelection(bool);

private:
    QString m_text;
    bool m_edge_mode;
    QVector<Edge*> m_edges;
    QVector<Node*> m_neighbors;
};

#endif // NODE_H
