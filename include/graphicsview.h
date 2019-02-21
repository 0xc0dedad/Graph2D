#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include "log.h"
#include "mainwindow.h"
#include "node.h"

class MainWindow;

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

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QGraphicsScene *createScene(QWidget *parent, QGraphicsScene **scene);
    size_t horizontalOffset() const;

private:
        QGraphicsScene *m_scene;
};

#endif // GRAPHICSVIEW_H
