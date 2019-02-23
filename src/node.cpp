#include "node.h"

unsigned Node::m_counter = 0;

Node::Node(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsEllipseItem(rect, parent),
      m_text(QString::number(++m_counter))
{
    init();
}

Node::Node(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
    : QGraphicsEllipseItem(x, y, w, h, parent),
      m_text(QString::number(++m_counter))
{
    init();
}

Node::Node(QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent),
      m_text(QString::number(++m_counter))
{
    init();
}

Node::~Node()
{

}

void Node::init()
{
    GraphicsView *handler = MainWindow::instance().getView();

    setCursor(Qt::PointingHandCursor);

    if (!handler)
        LOG_EXIT("Invalid handler", );

    connect(this, SIGNAL(menuItemSelected(QAction*, Node*)), handler,
     SLOT(modeHandler(QAction*, Node*)));
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
        menu.addAction(lst[i], this, SLOT(signalSender()));

    menu.exec(event->screenPos());
}

void Node::setText(const QString string)
{
   int len = 1;

   if (string.length() > len)
        LOG_EXIT("Invalid title", );

   m_text = string;
}

void Node::signalSender()
{
    QAction *action = qobject_cast<QAction*> (sender());

    if (!action)
        LOG_EXIT("Invalid action", );

    emit menuItemSelected(action, this);
}
