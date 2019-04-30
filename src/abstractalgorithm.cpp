#include "abstractalgorithm.h"
#include "settingswindow.h"

code2color_t code2color_arr[] = {
  { .code = 0, .color = Qt::green},
  { .code = 1, .color = Qt::red},
  { .code = 2, .color = Qt::blue},
  { .code = -1, .color = Qt::black }
};

AbstractAlgorithm::AbstractAlgorithm(QObject *parent)
    : QObject(parent),
      m_graph(0),
      m_debug(0),
      m_way(0),
      m_shortest(nullptr)
{
    MainWindow *sender = qobject_cast<MainWindow*> (parent);

    if (!sender)
    {
        LOG_DEBUG("Invalid pointer");
    }
    else
        connect(sender, SIGNAL(execute()), this, SLOT(run()));
}

AbstractAlgorithm::~AbstractAlgorithm()
{
    clearWay();
}

bool AbstractAlgorithm::resizeGraph(GraphicsView *view)
{
    int size;

    if (!view)
        LOG_EXIT("Invalid pointer", false);

    if (!(size = view->getNodes().size()))
        LOG_EXIT("Invalid size", false);

    for(int i=0; i<size; i++)
        m_graph.push_back(QVector<int>(size, 0));

    return true;
}

void AbstractAlgorithm::initGraph()
{
    QVector<Node*> nodes;
    bool debug  = true;
    GraphicsView *view = MainWindow::instance().getView();

    if (!view)
        LOG_EXIT("Invalid pointer", );

    nodes = view->getNodes();
    resizeGraph(view);

    for(int i=0; i<nodes.size(); i++)
    {
        int name = nodes[i]->text().toInt() - 1;
        QVector<Edge*> *edges = nodes[i]->getEdges();

        if (name >= nodes.size() || name < 0)
            LOG_EXIT("Invalid node name:" << name, );

        for(int j=0; j<edges->size(); j++)
        {
            int connected;
            QPair<Node*, Node*> vertices = (*edges)[j]->getVertices();

            if (vertices.first == nodes[i])
                connected = vertices.second->text().toInt();
            else if (vertices.second == nodes[i])
                connected = vertices.first->text().toInt();
            else
                LOG_EXIT("Invalid node", );

            --connected;
            m_graph[name][connected] = (*edges)[j]->isWeighted() ?
               (*edges)[j]->getWeight() : 1;
        }
    }

    if (debug)
        debugGraph();
}

QVector<QVector<int> > AbstractAlgorithm::getGraph() const
{
    return m_graph;
}

void AbstractAlgorithm::debugGraph()
{
    qDebug() << m_graph;
}

int AbstractAlgorithm::getIndex(int val) const
{
    for(int i=0; i<m_way.size(); i++)
    {
        if (val == m_way[i]->id)
            return i;
    }

    return -1;
}

void AbstractAlgorithm::checkBranch(QVector<int> &marked, Node *finish,
 GraphicsView *view)
{
    int index;
    Node *n1, *n2;

    if (marked.isEmpty())
        LOG_EXIT("Empty array", );

    /* get index of value for m_way array */
    if ((index = getIndex(marked.back())) == -1)
        LOG_EXIT("Invalid index", );

    if(!(n1 = view->findNodeByIndex(marked.back())))
        LOG_EXIT("Invalid pointer", );

    if (n1->findConnectedEdge(finish))
        return;

    for(int i=index + 1; i<m_way.size(); i++)
    {
        if (!(n2 = view->findNodeByIndex(m_way[i]->id)))
            LOG_EXIT("Invalid pointer", );

        if (!m_way[i]->visited && n1->findConnectedEdge(n2))
        {
            marked.push_back(m_way[i]->id);
            m_way[i]->visited = true;
            checkBranch(marked, finish, view);
            return;
        }
    }

    marked.pop_back();
    checkBranch(marked, finish, view);
}

void AbstractAlgorithm::markEdge(QVector<int> marked, Node *finish,
 GraphicsView *view, bool reset)
{
    Edge *edge;
    Node *n1, *n2;
    static int code = 0;

    if (marked.isEmpty())
        LOG_EXIT("Array is empty", );

    if (reset)
        code = 0;

    for(int i=0; i<marked.size(); i++)
    {
        if(!(n1 = view->findNodeByIndex(marked[i])))
            LOG_EXIT("Invalid pointer", );

        if ((i + 1) == marked.size())
            n2 = finish;
        else if (!(n2 = view->findNodeByIndex(marked[i + 1])))
            LOG_EXIT("Invalid pointer", );

        if (!(edge = n1->findConnectedEdge(n2)))
            LOG_EXIT("Invalid pointer", );

        if (edge->pen().color() == Qt::white)
            edge->setPen(QPen(code2color(code), 1.5, Qt::SolidLine));
    }

    code++;
}

QVector<int> AbstractAlgorithm::markWay(GraphicsView *view,
  Node *finish, bool reset)
{
    QVector<int> marked;

    if (m_way.isEmpty())
        LOG_EXIT("Array is empty", QVector<int>());

    marked.push_back(m_way[0]->id);
    checkBranch(marked, finish, view);
    markEdge(marked, finish, view, reset);
    clearWay();

    return marked;
}

void AbstractAlgorithm::clearWay()
{
    for(int i=0; i<m_way.size(); i++)
    {
        if (m_way[i])
            delete m_way[i];
    }

    m_way.clear();
}

void AbstractAlgorithm::run()
{
    SettingsWindow *s;
    Tab *tab;
    Node *start, *finish;
    GraphicsView *view = MainWindow::instance().getView();
    bool order = true;

    if (!view)
        LOG_EXIT("Invalid pointer", );

    start = view->getStartNode();
    finish = view->getFinishNode();

    if (!(start = view->getStartNode()) ||
         !(finish = view->getFinishNode()) || (start == finish))
    {
        MainWindow::instance().showMessage("Select start and end node!");
        LOG_EXIT("Invalid pointer", );
    }

    if ((s = MainWindow::instance().getSettingsWindow()) &&
         (tab = s->getSettingsTab()))
    {
        QRadioButton *btn;

        if ((btn = tab->getLittleBitRB()) && btn->isChecked())
            order = true;

        if ((btn = tab->getBiggestBitRB()) && btn->isChecked())
            order = false;
    }

    m_graph.clear();
    m_list.clear();
    m_debug.clear();

    initGraph();
    algorithm(start, finish, view, order);
}

Qt::GlobalColor code2color(const int code)
{
    code2color_t *current = code2color_arr;

    for(; current->code != -1; current++)
    {
        if (current->code == code)
            return current->color;
    }

    return Qt::black;
}
