#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QKeyEvent>

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include "log.h"
#include "mainwindow.h"
#include "node.h"
#include "edge.h"
#include "abstractitem.h"

class MainWindow;
class Node;
class Edge;

enum Mode
{
    Default,
    Renaming,
    Connecting,
    Moving,
    DeletingNode,
    DeletingEdge,
    None = -1
};

typedef struct
{
    QString str;
    Mode mode;
} str2mode_t;


/* XXX: Item will be called as selected node or edge, when
 * Node - when changed mode via popup menu
 * Edge - in connection mode */

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

    GraphicsView(const QWidget&);
    GraphicsView &operator=(GraphicsView &);

public:
    GraphicsView(QWidget *parent = 0);
    ~GraphicsView();

    QSize sizeHint() const;
    void addItem(QGraphicsItem *item);
    void setBrush(QBrush brush);
    QGraphicsScene *getScene() const;
    void addNode(const size_t radius, const QBrush brush, const QPointF pos);
    void addEdge(qreal x1, qreal y1, qreal x2, qreal y2);
    Mode getMode() const;
    Node *getSelectedNode() const;
    void disableNodesConnectionModes();
    void deleteNode(Node *node);
    /* XXX: Remove from m_nodes vector */
    void removeNode(Node *node);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QGraphicsScene *createScene(QWidget *parent, QGraphicsScene **scene);
    size_t horizontalOffset() const;
    bool isNodeIntersected(QRectF rect) const;

public slots:
    void modeHandler(QAction*, AbstractItem*);
    void setMode(int);

signals:
    void setConnectionMode(bool);

private:
        QGraphicsScene *m_scene;
        Mode m_mode;
        Node *m_selected_node;
        Edge *m_selected_edge;
        QVector<Node*> m_nodes;
        bool m_moving_captured;
};

extern str2mode_t str2mode_arr[];
Mode str2mode(const QString str);

#endif // GRAPHICSVIEW_H
