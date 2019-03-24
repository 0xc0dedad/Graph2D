#include "tab.h"
#include "bfsalgorithm.h"

Tab::Tab(int type, QWidget *parent)
    : QWidget(parent),
      m_list(nullptr),
      m_storage(nullptr)
{
    switch(type)
    {
        case TabType::AlgorithmsTab:
        createAlgorithmsTab(this, &m_list);
        break;

        case TabType::SettingsTab:
        break;

        case TabType::StorageTab:
        createStorageTab(this, &m_storage);
        break;

        default:
        LOG_DEBUG("Invalid tab type!");
        break;
    }

    layout();
}

Tab::~Tab()
{

}

void Tab::layout()
{
    QVBoxLayout *layout = new QVBoxLayout;

    if (m_list)
        layout->addWidget(m_list);

    if (m_storage)
        layout->addWidget(m_storage);

    this->setLayout(layout);
}

QListWidget *Tab::createAlgorithmsTab(QWidget *parent, QListWidget **list)
{
    QStringList lst;
    QListWidgetItem *item;
    QString path = SettingsWindow::pathToImages();
    SettingsWindow *sw = qobject_cast<SettingsWindow*> (this->parent());

    lst << "Algo 1" << "Algo 2" << "Algo 3";

    *list = new QListWidget(parent);
    (*list)->setIconSize(QSize(10, 10));

    if (!sw)
    {
        LOG_DEBUG("Invalid pointer");
    }
    else
    {
        connect(*list, SIGNAL(clicked(QModelIndex)), sw,
          SLOT(setSelectedAlgorithm(QModelIndex)));
    }

    for(int i=0; i<lst.size(); i++)
    {
        item = new QListWidgetItem(lst[i], *list);
        item->setIcon(QPixmap(path + "algorithm.png"));
    }

    return *list;
}

QWidget *Tab::createStorageTab(QWidget *parent, QWidget **tab)
{
    QVBoxLayout *layout = new QVBoxLayout;

    (*tab) = new QWidget(parent);
    layout->addWidget(createPushButton("Upload", SLOT(upload())));
    layout->addWidget(createPushButton("Download", SLOT(download())));
    (*tab)->setLayout(layout);

    return *tab;
}

QPushButton *Tab::createPushButton(QString title, const char *slot)
{
    QPushButton *btn = new QPushButton(title);

    btn->setCursor(Qt::PointingHandCursor);
    connect(btn, SIGNAL(clicked(bool)), this, slot);

    return btn;
}

void Tab::writeGraph(QVector<QVector<int> > graph, QTextStream &stream) const
{
    for(int i=0; i<graph.size(); i++)
    {
        for(int j=0; j<graph[i].size(); j++)
        {
            stream << graph[i][j];

            if (j < graph[i].size() - 1)
                stream << " ";
        }

        if (i < graph.size() - 1)
            stream << "\n";
    }
}

void Tab::writeUIConf(QString filename) const
{
    QFile file;
    QTextStream stream;
    QVector<Node*> nodes;
    size_t offset = 10; // Node's radius / 2
    GraphicsView *view = MainWindow::instance().getView();

    if (!view)
        LOG_EXIT("Invalid pointer", );

    file.setFileName(filename + ".conf");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        LOG_EXIT("Can't open file!", );

    stream.setDevice(&file);
    nodes = view->getNodes();

    for(int i=0; i<nodes.size(); i++)
    {
        stream << nodes[i]->rect().x() + offset << " "
          << nodes[i]->rect().y() + offset << "\n";
    }

    file.close();
}

void Tab::download()
{
    QFile file;
    QString filename;
    QTextStream stream;
    QVector<QVector<int> > graph;
    /* XXX: used only for accessing to initGraph() method. Not correct logic */
    BFSAlgorithm algorithm;

    algorithm.initGraph();
    graph = algorithm.getGraph();

    if (graph.isEmpty())
        LOG_EXIT("Canvas is empty!", );

    filename = QFileDialog::getSaveFileName(this, "Save file...", "", "*.txt");

    if (filename.isEmpty())
        LOG_EXIT("Filename is empty", );

    file.setFileName(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        LOG_EXIT("Can't open file!", );

    stream.setDevice(&file);
    writeGraph(graph, stream);
    file.close();
    writeUIConf(filename);
}

void Tab::upload()
{

}
