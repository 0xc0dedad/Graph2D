#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include <QObject>

class Edge : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

public:
    explicit Edge(QGraphicsLineItem *parent = Q_NULLPTR);
    explicit Edge(qreal x1, qreal y1, qreal x2, qreal y2,
      QGraphicsItem *parent = Q_NULLPTR);
    ~Edge();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
     QWidget *widget);
    bool isEdgeSelected() const;

private slots:
    void setSelection(bool);

private:
    bool m_is_selected;

};

#endif // EDGE_H
