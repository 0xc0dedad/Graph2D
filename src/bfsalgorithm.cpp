#include "bfsalgorithm.h"

BFSAlgorithm::BFSAlgorithm(QObject *parent)
    : AbstractAlgorithm(parent)
{

}

BFSAlgorithm::~BFSAlgorithm()
{

}

void BFSAlgorithm::algorithm(Node *start, Node *finish, GraphicsView *view)
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
    m_list.push_back(id);

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

        for(int i=0; i<m_graph[current].size(); i++)
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
                    markWay(view, finish, reset);
                    found = true;
                    reset = false;

                    MainWindow::instance().createRaport();
                    MainWindow::instance().getRaport()->setRaport(m_raport);
                }

                if (!visited[i]) /* if not visited yet */
                {
                    visited[i] = true;
                    m_list.push_back(i);
                }
            }
        }
    }

    if (debug)
        qDebug() << m_debug;

  Exit:
    delete[] visited;
}
