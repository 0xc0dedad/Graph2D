#include "dejikstralgorithm.h"

DejikstraAlgorithm::DejikstraAlgorithm(QObject *parent)
    : AbstractAlgorithm(parent)
{

}

DejikstraAlgorithm::~DejikstraAlgorithm()
{

}

void DejikstraAlgorithm::algorithm(Node *start, Node *finish, GraphicsView *view,
  bool order)
{
    int id;
    bool debug, found = false;
    bool *visited = new bool[m_graph.size()]();

    m_shortest = new int[m_graph.size()];

    if (!visited || !m_shortest)
    {
        LOG_DEBUG("Invalid pointer");
    }

    /* XXX: Init array of ways with INf value */
    for(int i=0; i<m_graph.size(); i++)
        m_shortest[i] = INF;

    id = start->text().toInt() - 1;
    visited[id] = true;
    m_list.push_back(id);

    /* XXX: Shortest way to start node is 0. */
    m_shortest[id] = 0;
    /* XXX: For graph debugging */
    debug = true;

    while(!m_list.isEmpty())
    {
        Node *node;
        int current = m_list.front();

        m_list.pop_front();

        /* Don't add finish node to m_way array! */
        if (current != (finish->text().toInt() - 1))
            m_way.push_back(new Vertex(current, false));

        if (!(node = view->findNodeByIndex(current)))
        {
            LOG_DEBUG("Node doesn't exist");
            goto Exit;
        }

        for(int i = 0; i<m_graph[current].size(); i++)
        {
            int weight, sum = 0;

            if ((weight = m_graph[current][i])) /* if connectced with i-node */
            {
                if (!(node = view->findNodeByIndex(i)))
                {
                    LOG_DEBUG("Node doesn't exist");
                    goto Exit;
                }

                sum = weight + m_shortest[current];

                if (sum < m_shortest[i])
                    m_shortest[i] = sum;

                if ((node == finish) && !found)
                    found = true;

                if (!visited[i]) /* if not visited yet */
                {
                    visited[i] = true;
                    m_list.push_back(i);
                }
            }
        }
    }

    if (found)
    {
        QVector<int> marked = markWay(view, finish, true);

        if (marked.isEmpty())
            LOG_EXIT("Vector is empty", );

        /* XXX: Create raport here! */
        updateToolTips(view);
        createRaport(start, view);
    }
    else
        MainWindow::instance().showMessage("Solution not found!");

    if (debug)
    {
        for(int i=0; i<m_graph.size(); i++)
            qDebug() << m_shortest[i];
    }

  Exit:
    delete[] visited;
    delete[] m_shortest;
}

bool DejikstraAlgorithm::checkBranch(QVector<int> &marked, Node *finish,
 GraphicsView *view, bool reset)
{
    int index;
    Node *n1, *n2;
    Edge *edge;
    static int checksum = m_shortest[finish->text().toInt() - 1];
    static QVector<size_t> weights;

    if (reset)
    {
        checksum = m_shortest[finish->text().toInt() - 1];
        weights.clear();
    }

    if (marked.isEmpty())
        LOG_EXIT("Empty array", false);

    /* get index of value for m_way array */
    if ((index = getIndex(marked.back())) == -1)
        LOG_EXIT("Invalid index", false);

    if(!(n1 = view->findNodeByIndex(marked.back())))
        LOG_EXIT("Invalid pointer", false);

    if ((edge = n1->findConnectedEdge(finish)))
    {
        if (!(checksum - edge->getWeight()))
            return true;
    }
    else
    {
        for(int i=index + 1; i<m_way.size(); i++)
        {
            if (!(n2 = view->findNodeByIndex(m_way[i]->id)))
                LOG_EXIT("Invalid pointer", false);

            if ((edge = n1->findConnectedEdge(n2)) && !wasVisitedFromNode(index,
		  m_way[i]))
            {
                marked.push_back(m_way[i]->id);
                m_way[i]->visited_from.push_back(index);
                weights.push_back(edge->getWeight());
                checksum -= weights.at(weights.size() - 1);
                checkBranch(marked, finish, view, false);
                return true;
            }
        }
    }

    if (weights.isEmpty())
        LOG_EXIT("Vector is empty", false);

    checksum += weights.at(weights.size() - 1);
    weights.pop_back();
    marked.pop_back();
    checkBranch(marked, finish, view, false);

    return true;
}

bool DejikstraAlgorithm::wasVisitedFromNode(int from, Vertex *node) const
{
    for(int i=0; i<node->visited_from.size(); i++)
    {
        if (node->visited_from[i] == from)
            return true;
    }

    return false;
}

QVector<int> DejikstraAlgorithm::markWay(GraphicsView *view, Node *finish,
  bool reset)
{
    bool reset_color = true;
    QVector<int> marked;

    if (m_way.isEmpty())
        LOG_EXIT("Array is empty", QVector<int>());

    marked.push_back(m_way[0]->id);

    while(checkBranch(marked, finish, view, reset))
    {
        markEdge(marked, finish, view, reset_color);
        marked.clear();
        marked.push_back(m_way[0]->id);
        reset_color = false;
    }

    clearWay();

    return marked;
}

void DejikstraAlgorithm::updateToolTips(GraphicsView *view) const
{
    QVector<Node*> nodes;

    if (!view)
        LOG_EXIT("Invalid pointer!", );

    nodes = view->getNodes();

    for(int i=0; i<nodes.size(); i++)
    {
        int path = m_shortest[nodes[i]->text().toInt() - 1];

        if (nodes[i]->toolTip().isEmpty())
            nodes[i]->setToolTip(QString::number(path));
        else
        {
            nodes[i]->setToolTip(nodes[i]->toolTip().split(",")[0] + ", " +
             QString::number(path));
        }
    }
}

void DejikstraAlgorithm::createRaport(Node *first, GraphicsView *view) const
{
    QString result, source, destination;
    QVector<Node*> nodes;

    if (!view || !first)
        LOG_EXIT("Invalid pointer!", );

    nodes = view->getNodes();
    source = first->toolTip().isEmpty() ? first->text() :
       first->toolTip().split(",")[0];

    for(int i=0; i<nodes.size(); i++)
    {
        if (nodes[i] == first)
            continue;

        destination = nodes[i]->toolTip().isEmpty() ? nodes[i]->text() :
           nodes[i]->toolTip().split(",")[0];

        result += source + " - " + destination + " : " +
         QString::number(m_shortest[nodes[i]->text().toInt() - 1]) + "<br/>";
    }

    MainWindow::instance().createRaport();
    MainWindow::instance().getRaport()->setRaport(result);
}
