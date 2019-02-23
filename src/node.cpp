#include "node.h"

unsigned Node::m_counter = 0;

Node::Node(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsEllipseItem(rect, parent),
      m_text(QString::number(++m_counter)),
      m_edge_mode(false),
      m_edges(0)
{
    init();
}

Node::Node(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
    : QGraphicsEllipseItem(x, y, w, h, parent),
      m_text(QString::number(++m_counter)),
      m_edge_mode(false),
      m_edges(0)
{
    init();
}

Node::Node(QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent),
      m_text(QString::number(++m_counter)),
      m_edge_mode(false),
      m_edges(0)
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
    connect(handler, SIGNAL(setConnectionMode(bool)), this,
     SLOT(setConnectionMode(bool)));
    connect(this, SIGNAL(setMode(int)), handler, SLOT(setMode(int)));
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

bool Node::isConnectionMode() const
{
    return m_edge_mode;
}

void Node::addEdge(Edge **edge)
{
    if (!edge || !*edge)
        LOG_EXIT("Invalid parameter", );

    connect(this, SIGNAL(setEdgeSelection(bool)), *edge, SLOT(setSelection(bool)));

    m_edges.push_back(*edge);
}

Edge *Node::getSelectedEdge() const
{
    return m_edges.isEmpty() ? nullptr : m_edges.back();
}

QString Node::text() const
{
    return m_text;
}

QVector<Edge *> *Node::getEdges()
{
    return &m_edges;
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    GraphicsView *view = MainWindow::instance().getView();

    if (!view)
        LOG_EXIT("Invalid pointer", );

    if (view->getMode() == Mode::Connecting)
    {
        Edge *edge;
        QPointF n1, n2;
        Node *node = view->getSelectedNode();

        if (!node)
            LOG_EXIT("Invalid pointer", );

        n1 = node->rect().center();
        n2 = this->rect().center();
        edge = node->getSelectedEdge();

        if (!edge)
            LOG_EXIT("Invalid pointer", );

        edge->setLine(n1.x(), n1.y(), n2.x(), n2.y());

        addEdge(&edge);
        emit setMode(Mode::Default);
        node->setEdgeSelection(false);
        node->setConnectionMode(false);

        /* XXX: warkround. Fix Edge disappearing */
        setConnectionMode(false);
    }
}

void Node::signalSender()
{
    QAction *action = qobject_cast<QAction*> (sender());

    if (!action)
        LOG_EXIT("Invalid action", );

    emit menuItemSelected(action, this);
}

void Node::setConnectionMode(bool value)
{
    m_edge_mode = value;
}
