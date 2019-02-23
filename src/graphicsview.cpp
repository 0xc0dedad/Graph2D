#include "graphicsview.h"

str2mode_t str2mode_arr[] = {
  { .str = "Rename", .mode = Renaming },
  { .str = "Connect...", .mode = Connecting },
  { .str = "Move...", .mode = Moving },
  { .str = "Delete", .mode = Deleting },
  { NULL, None }
};

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent),
      m_scene(nullptr),
      m_mode(Default)
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

void GraphicsView::modeHandler(QAction *action, Node *sndr)
{
    if (!action || !sndr)
        LOG_EXIT("Invalid parameter", );

    m_mode = str2mode(action->text());
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
    Node *item = new Node;

    item->setRect(pos.x() - radius / 2, pos.y() - radius / 2, radius, radius);
    item->setBrush(brush);
    m_scene->addItem(item);
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

            default:
            LOG_DEBUG("Invalid mode!");
            break;
        }
    }
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
