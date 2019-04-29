#include "node.h"

Node::Node(const QRectF &rect, QGraphicsItem *parent)
    : AbstractItem(nullptr),
      QGraphicsEllipseItem(rect, parent),
      m_edge_mode(false),
      m_edges(0),
      m_neighbors(0)
{
    init();
}

Node::Node(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
    : AbstractItem(nullptr),
      QGraphicsEllipseItem(x, y, w, h, parent),
      m_edge_mode(false),
      m_edges(0),
      m_neighbors(0)
{
    init();
}

Node::Node(QGraphicsItem *parent)
    : AbstractItem(nullptr),
      QGraphicsEllipseItem(parent),
      m_edge_mode(false),
      m_edges(0),
      m_neighbors(0)
{
    init();
}

Node::~Node()
{

}

int Node::id() const
{
    return ItemID::NodeID;
}

void Node::init()
{
    int name;
    GraphicsView *handler = MainWindow::instance().getView();

    setCursor(Qt::PointingHandCursor);

    if (!handler)
        LOG_EXIT("Invalid handler", );

    if ((name = findValidName()) != -1)
        m_text = QString::number(name);
    else
        LOG_EXIT("Invalid name!", );

    connect(handler, SIGNAL(setConnectionMode(bool)), this,
     SLOT(setConnectionMode(bool)));
    connect(this, SIGNAL(setMode(int)), handler, SLOT(setMode(int)));
}

int Node::findValidName() const
{
    int name;
    Node *first;
    GraphicsView *view = MainWindow::instance().getView();
    QVector<Node*> nodes;

    if (!view)
        LOG_EXIT("Invalid pointer", -1);

    nodes = view->getNodes();

    if (!(first = view->findNodeByName(1)))
        return 1;

    name = first->text().toInt();

    while (true)
    {
        if (!view->findNodeByName(++name))
            return name;
    }

    return -1;
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

    lst << "Connect..." << "Move..." << "Delete node" <<
        "Mark as start" << "Mark as finish" << "ToolTip...";

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

void Node::addEdge(Node *first, Node *second, Edge **edge)
{
    if (!edge || !*edge)
        LOG_EXIT("Invalid parameter", );

    connect(this, SIGNAL(setEdgeSelection(bool)), *edge,
     SLOT(setSelection(bool)));

    (*edge)->setVertices(first, second);
    m_edges.push_back(*edge);
}

bool Node::delEdge(Edge *edge)
{
    int index;

    if (!edge)
        LOG_EXIT("Invalid pointer", false);

    if ((index = findEdge(edge)) != -1)
    {
        getEdges()->remove(index);
        return true;
    }

    return false;
}

void Node::modifyEdgeVertices(Edge *edge, Node *first, Node *second)
{
    if (!edge)
        LOG_EXIT("Invalid pointer", );

    if (!first)
        edge->setSecondVertex(second);

    if (!second)
        edge->setFirstVertex(first);
}

Edge *Node::findConnectedEdge(Node *node) const
{
    if (!node)
        LOG_EXIT("Invalid pointer", nullptr);

    for(int i=0; i<m_edges.size(); i++)
    {
        if (m_edges[i]->isExist(node))
            return m_edges[i];
    }

    return nullptr;
}

int Node::findEdge(Edge *edge) const
{
    for(int i=0; i<m_edges.size(); i++)
    {
        if (m_edges[i] == edge)
            return i;
    }

    return -1;
}

int Node::findNeighbor(Node *node) const
{
    for(int i=0; i<m_neighbors.size(); i++)
    {
        if (m_neighbors[i] == node)
            return i;
    }

    return -1;
}

void Node::addNeighbor(Node *node)
{
    if (!node)
        LOG_EXIT("Invalid parameter", );

    m_neighbors.push_back(node);
}

void Node::delNeighbor(Node *node)
{
    int index;

    if (!node)
        LOG_EXIT("Invalid pointer", );

    index = findNeighbor(node);

    if (index != -1)
        m_neighbors.remove(index);
    else
        LOG_DEBUG("Can't find neighbor!");
}

bool Node::isAmongNeighbors(Node *node) const
{
    for(int i=0; i<m_neighbors.size(); i++)
    {
        if (node == m_neighbors[i])
            return true;
    }

    return false;
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

QVector<Node *> *Node::getNeighbors()
{
    return &m_neighbors;
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Node *node;
    GraphicsView *view = MainWindow::instance().getView();

    if (!view)
        LOG_EXIT("Invalid pointer", );

    node = view->getSelectedNode();

    /* XXX: Handler for non selected node */
    if ((view->getMode() == Mode::Connecting) && (this != node))
    {
        Edge *edge;
        QPointF n1, n2;

        if (!node)
            LOG_EXIT("Invalid pointer", );

        if (isAmongNeighbors(node))
            LOG_EXIT("Is a neighbor!", );

        n1 = node->rect().center();
        n2 = this->rect().center();
        edge = node->getSelectedEdge();

        if (!edge)
            LOG_EXIT("Invalid pointer", );

        edge->setLine(n1.x(), n1.y(), n2.x(), n2.y());

        /* Add edges and vertices to it */
        this->addEdge(node, this,  &edge);
        node->modifyEdgeVertices(edge, nullptr, this);

        emit setMode(Mode::Default);
        node->setEdgeSelection(false);

        /* Add neighbors */
        this->addNeighbor(node);
        node->addNeighbor(this);

        /* XXX: warkround. Fix Edge disappearing */
        view->disableNodesConnectionModes();
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
