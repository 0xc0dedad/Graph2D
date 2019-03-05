#include "abstractalgorithm.h"

AbstractAlgorithm::AbstractAlgorithm(QObject *parent)
    : QObject(parent),
      m_graph(0)
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
            m_graph[name][connected] = 1;
        }
    }

    if (debug)
        debugGraph();
}

void AbstractAlgorithm::debugGraph()
{
    for(int i=0; i<m_graph.size(); i++)
    {
        for(int j=0; j<m_graph[i].size(); j++)
            qDebug() << m_graph[i][j];
        qDebug() << "\n";
    }
}

void AbstractAlgorithm::run()
{
    m_graph.clear();
    initGraph();
}
