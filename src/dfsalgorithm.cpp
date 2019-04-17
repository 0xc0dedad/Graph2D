#include "dfsalgorithm.h"

DFSAlgorithm::DFSAlgorithm(QObject *parent)
    : AbstractAlgorithm(parent)
{

}

DFSAlgorithm::~DFSAlgorithm()
{

}

void DFSAlgorithm::algorithm(Node *start, Node *finish, GraphicsView *view,
  bool order)
{
    int id;
    bool debug, reset, found = false;
    bool *visited = new bool[m_graph.size()]();

    if (!visited)
    {
        LOG_DEBUG("Invalid pointer");
    }

    id = start->text().toInt() - 1;
    visited[id] = reset = true;
    m_list.push_front(id);

    /* XXX: For graph debugging */
    debug = true;

    while(!m_list.isEmpty())
    {
        Node *node;
        int current = m_list.front();

        m_list.pop_front();
        m_way.push_back(new Vertex(current, false));

        if (!(node = view->findNodeByIndex(current)))
        {
            LOG_DEBUG("Node doesn't exist");
            goto Exit;
        }

        if (debug)
            m_debug.push_back(current + 1);

        /* Mark opened nodes until not found connected one */
        if (!found)
        {
            if (node != start)
                node->setBrush(QBrush(Qt::yellow, Qt::SolidPattern));

            m_raport.push_back(current + 1);
        }

        for(int i = order ? 0 : m_graph[current].size() - 1;
            order ? (i<m_graph[current].size()) : (i>=0) ; order ? i++ : i--)
        {
            if (m_graph[current][i]) /* if connectced with i-node */
            {
                if (!(node = view->findNodeByIndex(i)))
                {
                    LOG_DEBUG("Node doesn't exist");
                    goto Exit;
                }

            /* XXX: Workaround: Found only one way
             * After found way, algorithm not stoping.
             * We continue opening all nodes. This is important in case
             * if want mark more than one way from start to finish point later. */
                if ((node == finish) && !found)
                {
                    QVector<int> marked = markWay(view, finish, reset);

                    if (marked.isEmpty())
                        LOG_EXIT("Vector is empty", );

                    /* XXX: Workaround */
                    for(int i=0; i<marked.size(); i++)
                        marked[i]++;

                    found = true;
                    reset = false;

                    MainWindow::instance().createRaport();
                    MainWindow::instance().getRaport()->setRaport(m_raport);
                    MainWindow::instance().getRaport()->appendRaport(marked,
               "Way: ");
                }

                if (!visited[i]) /* if not visited yet */
                {
                    visited[i] = true;
                    m_list.push_front(i);
                }
            }
        }
    }

    if (!found)
        MainWindow::instance().showMessage("Solution not found!");

    if (debug)
        qDebug() << m_debug;

  Exit:
    delete[] visited;
}
