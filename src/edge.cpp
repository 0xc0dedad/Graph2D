#include "edge.h"

Edge::Edge(QGraphicsLineItem *parent)
    : AbstractItem(nullptr),
      QGraphicsLineItem(parent),
      m_is_selected(true),
      m_directable(false),
      m_is_weighted(false),
      m_weight(1)
{

}

Edge::Edge(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent)
    : AbstractItem(nullptr),
      QGraphicsLineItem(x1, y1, x2, y2, parent),
      m_is_selected(true),
      m_directable(false),
      m_is_weighted(false),
      m_weight(1)
{

}

Edge::~Edge()
{

}

int Edge::id() const
{
    return ItemID::EdgeID;
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
 QWidget *widget)
{
    GraphicsView *view = MainWindow::instance().getView();

    if (!view)
        LOG_EXIT("Invalid pointer", );

    QGraphicsLineItem::paint(painter, option, widget);

    if (m_directable)
    {
        int radius = 10;

        painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
        painter->drawEllipse(line().x2() - radius / 2,
         line().y2() - radius / 2, radius, radius);
    }

    if (m_is_weighted)
    {
        QFont font("Ubuntu", 12, QFont::Bold);
        QString weight = QString::number(m_weight);
        QSize metrix = view->getFontMetrix(font, weight);
        double x = (line().x1() + line().x2()) / 2;
        double y = (line().y1() + line().y2()) / 2;

        painter->setFont(font);
        painter->setPen(QPen(Qt::cyan, 1, Qt::SolidLine));
        painter->drawText(QRectF(x - metrix.width() / 2,
                  y - metrix.height() / 2, metrix.width(), metrix.height()),
                  weight);
    }
}

void Edge::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;

    menu.addAction("Directable", this, SLOT(signalSender()));
    menu.addAction("Delete edge", this, SLOT(signalSender()));
    menu.addAction("Weight...", this, SLOT(signalSender()));
    menu.exec(event->screenPos());
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

void Edge::directable(bool able)
{
    m_directable = able;
    this->update();
}

bool Edge::isDirectable() const
{
    return m_directable;
}

bool Edge::isWeighted() const
{
    return m_is_weighted;
}

void Edge::setWeight(size_t weight)
{
    m_weight = weight;
    m_is_weighted = (bool) weight;
}

size_t Edge::getWeight() const
{
    return m_weight;
}

QRectF Edge::getArrow() const
{
    int radius = 10;

    return QRectF(line().x2() - radius / 2,
            line().y2() - radius / 2, radius, radius);
}

void Edge::setSelection(bool value)
{
    m_is_selected = value;
}

void Edge::signalSender()
{
    QAction *action = qobject_cast<QAction*> (sender());

    if (!action)
        LOG_EXIT("Invalid action", );

    emit menuItemSelected(action, this);
}
