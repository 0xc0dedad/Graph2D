#include "graphicsview.h"

str2mode_t str2mode_arr[] = {
  { .str = "Rename", .mode = Renaming },
  { .str = "Connect...", .mode = Connecting },
  { .str = "Move...", .mode = Moving },
  { .str = "Delete node", .mode = DeletingNode },
  { .str = "Delete edge", .mode = DeletingEdge },
  { NULL, None }
};

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent),
      m_scene(nullptr),
      m_mode(Default),
      m_selected_node(nullptr),
      m_selected_edge(nullptr),
      m_moving_captured(false)
{
    QSize size = sizeHint();

    this->setWindowState(Qt::WindowFullScreen);
    this->resize(size);
    this->setGeometry(horizontalOffset(), 0, size.width(), size.height());
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setBackgroundBrush(Qt::white);

    createScene(this, &m_scene);
}

GraphicsView::~GraphicsView()
{

}

QSize GraphicsView::sizeHint() const
{
    size_t hoffset = horizontalOffset();
    QSize size = QApplication::desktop()->size();

    return QSize(size.width() - hoffset, size.height());
}

QGraphicsScene *GraphicsView::createScene(QWidget *parent, QGraphicsScene **scene)
{
    (*scene) = new QGraphicsScene(this->rect(), parent);

    if (scene)
        this->setScene(*scene);

    qDebug() << "View size: " << this->size();
    qDebug() << "Scene rect: " << this->rect();

    return *scene;
}

size_t GraphicsView::horizontalOffset() const
{
    size_t offset = 0;
    size_t additional = 10; // offset between items

    if (MainWindow *parent = qobject_cast<MainWindow*> (this->parent()))
        offset = parent->getSettingsBar()->width();

    return offset + additional;
}

bool GraphicsView::isNodeIntersected(QRectF rect) const
{
    for(int i=0; i<m_nodes.size(); i++)
    {
        if (rect.intersects(m_nodes[i]->rect()))
            return true;
    }

    return false;
}

void GraphicsView::modeHandler(QAction *action, AbstractItem *sndr)
{
    if (!action || !sndr)
        LOG_EXIT("Invalid parameter", );

    switch (sndr->id())
    {
        case AbstractItem::NodeID:
        if (!(m_selected_node = dynamic_cast<Node*> (sndr)))
            LOG_DEBUG("Invalid casting to Node class");
        break;

        case AbstractItem::EdgeID:
        if (!(m_selected_edge = dynamic_cast<Edge*> (sndr)))
            LOG_DEBUG("Invalid casting to Edge class");
        break;

        default:
        LOG_DEBUG("Invalid sender!");
        return;
    }

    switch ((m_mode = str2mode(action->text())))
    {
        case DeletingNode:
        deleteNode(m_selected_node);
        break;

        case DeletingEdge:
        deleteEdge(m_selected_edge);
        break;

        case Default:
        case Renaming:
        case Connecting:
        case Moving:
        break;

        case None:
        default:
        LOG_DEBUG("Invalid mode!");
        return;
    }

    if (m_mode != Connecting)
        emit setConnectionMode(false);
}

void GraphicsView::setMode(int mode)
{
    m_mode = (Mode) mode;
    m_selected_node = nullptr;
    m_selected_edge = nullptr;
}

void GraphicsView::addItem(QGraphicsItem *item)
{
    m_scene->addItem(item);
}

void GraphicsView::setBrush(QBrush brush)
{
    this->setBackgroundBrush(brush);
}

QGraphicsScene *GraphicsView::getScene() const
{
    return m_scene;
}

void GraphicsView::addNode(const size_t radius, const QBrush brush,
  const QPointF pos)
{
    QRectF rect;
    Node *item;

    rect.setRect(pos.x() - radius / 2, pos.y() - radius / 2, radius, radius);

    if (isNodeIntersected(rect))
        LOG_EXIT("Node intersected!", );

    item = new Node;
    item->setRect(rect);
    item->setBrush(brush);

    m_scene->addItem(item);
    m_nodes.push_back(item);
}

void GraphicsView::addEdge(qreal x1, qreal y1, qreal x2, qreal y2)
{
    Edge *item = new Edge;

    item->setLine(x1, y1, x2, y2);
    item->setPen(QPen(Qt::white, 1.5, Qt::SolidLine));

    if (!m_selected_node)
    {
        delete item;
        LOG_EXIT("Can't add edge!", );
    }

    m_scene->addItem(item);
    m_selected_node->addEdge(m_selected_node, nullptr, &item);
}

Mode GraphicsView::getMode() const
{
    return m_mode;
}

Node *GraphicsView::getSelectedNode() const
{
    return m_selected_node;
}

void GraphicsView::disableNodesConnectionModes()
{
    for(int i=0; i<m_nodes.size(); i++)
        m_nodes[i]->setConnectionMode(false);
}

void GraphicsView::deleteNode(Node *node)
{
    Edge *edge;
    QVector<Node*> *neighbors;

    if (!node)
        LOG_EXIT("Invalid pointer", );

    neighbors = node->getNeighbors();

    for(int i=0; i<neighbors->size(); i++)
    {
        if ((edge = (*neighbors)[i]->findConnectedEdge(node)))
        {
            int index;

            index = (*neighbors)[i]->findEdge(edge);

            if (index != -1)
                (*neighbors)[i]->getEdges()->remove(index);
            else
                LOG_DEBUG("Can't find edge!");

            index = (*neighbors)[i]->findNeighbor(node);

            if (index != -1)
                (*neighbors)[i]->getNeighbors()->remove(index);
            else
                LOG_DEBUG("Can't find neighbor!");

            m_scene->removeItem(edge);
            delete edge;
        }
    }

    m_scene->removeItem(node);
    removeNode(node);
    delete node;

    setMode(Default);
}

void GraphicsView::deleteEdge(Edge *edge)
{
    int index;
    QPair<Node*, Node*> vertices;

    if (!edge)
        LOG_EXIT("Invalid pointer", );

    vertices = edge->getVertices();

    index = vertices.first->findEdge(edge);
    vertices.first->delNeighbor(vertices.second);

    if (index != -1)
        vertices.first->getEdges()->remove(index);
    else
        LOG_DEBUG("Can't find edge!");

    index = vertices.second->findEdge(edge);
    vertices.second->delNeighbor(vertices.first);

    if (index != -1)
        vertices.second->getEdges()->remove(index);
    else
        LOG_DEBUG("Can't find edge!");

    m_scene->removeItem(edge);
    delete edge;

    setMode(Default);
}

void GraphicsView::removeNode(Node *node)
{
    if (!node)
        LOG_EXIT("Invalid pointer", );

    for(int i=0; i<m_nodes.size(); i++)
        if (m_nodes[i] == node)
            m_nodes.remove(i);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    size_t radius = 20;

    if (event->button() == Qt::LeftButton)
    {
        switch (m_mode)
        {
            case Default:
            addNode(radius, QBrush(Qt::white, Qt::SolidPattern), event->pos());
            break;

            case Moving:
            m_moving_captured = true;
            break;

            default:
            LOG_DEBUG("Invalid mode!" << m_mode);
            break;
        }

        QGraphicsView::mousePressEvent(event);
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = event->pos();

    if (m_mode == Connecting)
    {
        QPointF center;

        if (!m_selected_node)
            LOG_EXIT("Invalid parameter", );

        center = m_selected_node->rect().center();

        if (m_selected_node->isConnectionMode())
        {
            Edge *selected = m_selected_node->getSelectedEdge();

            if (!selected)
                LOG_EXIT("Invalid pointer",  );

            selected->setLine(center.x(), center.y(), pos.x(), pos.y());
        }
        else
        {
            addEdge(center.x(), center.y(), pos.x(), pos.y());
            emit setConnectionMode(true);
        }
    }

    if ((m_mode == Moving) && m_moving_captured)
    {
        QVector<Edge*> *edges;
        const size_t radius = 20;

        if (!m_selected_node)
            LOG_EXIT("Invalid parameter", );

        edges = m_selected_node->getEdges();
        m_selected_node->setRect(pos.x() - radius / 2,
          pos.y() - radius / 2, radius, radius);

        for(int i=0; i<(*edges).size(); i++)
        {
            QPointF vpos;
            QPair<Node*, Node*> vertices = (*edges)[i]->getVertices();

            if (vertices.first == m_selected_node)
            {
                vpos = (*edges)[i]->getSecondVertexPos();
                (*edges)[i]->setLine(pos.x(), pos.y(), vpos.x(), vpos.y());
                continue;
            }
            else
            {
                vpos = (*edges)[i]->getFirstVertexPos();
                (*edges)[i]->setLine(vpos.x(), vpos.y(), pos.x(), pos.y());
            }
        }
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && (m_mode == Moving) &&
         m_moving_captured)
    {
        m_moving_captured = false;
        setMode(Default);
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        QVector<Edge*> *edges = m_selected_node->getEdges();

        for(int j=0; j<edges->size(); j++)
        {
            if ((*edges)[j]->isEdgeSelected())
            {
                m_scene->removeItem((*edges)[j]);
                edges->remove(j);
                setMode(Mode::Default);
                disableNodesConnectionModes();

                return;
            }
        }
    }

    QGraphicsView::keyPressEvent(event);
}

Mode str2mode(const QString str)
{
    str2mode_t *current = str2mode_arr;

    if (str.isEmpty())
        return None;

    for(; current->str != NULL; current++)
    {
        if (current->str == str)
            return current->mode;
    }

    return Mode::None;
}
