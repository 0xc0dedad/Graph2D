#include "mainwindow.h"
#include "bfsalgorithm.h"

MainWindow::MainWindow(QWidget *parent)
    : AbstractWindow(parent),
      m_settings_bar(nullptr),
      m_view(nullptr),
      m_settings(nullptr),
      m_algorithm(nullptr)
{
    layout();
    setBackgroundColor();
}

MainWindow::~MainWindow()
{
    m_settings->deleteLater();

    if (m_algorithm)
        delete m_algorithm;
}

MainWindow &MainWindow::instance(QWidget *parent)
{
    static MainWindow instance(parent);

    return instance;
}

QToolBar *MainWindow::getSettingsBar() const
{
    return m_settings_bar;
}

GraphicsView *MainWindow::getView() const
{
    return m_view;
}

void MainWindow::layout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *center_layout = new QHBoxLayout;
    QVBoxLayout *bar_layout = new QVBoxLayout;

    layout->setContentsMargins(0, 0, 0, 0);

    if (createSettingsBar(this, &m_settings_bar))
    {
        bar_layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        bar_layout->addWidget(m_settings_bar);
        center_layout->addLayout(bar_layout);
    }

    if (createGraphicsView(this, &m_view))
        center_layout->addWidget(m_view);

    layout->addLayout(center_layout);
    this->setLayout(layout);
}

QToolBar *MainWindow::createSettingsBar(QWidget *parent, QToolBar **bar)
{
    QString path = pathToImages();
    QStringList lst;

    lst << "settings.png" << "result.png" << "play.png" << "restore.png";

    if (!createToolBar(parent, bar))
        LOG_EXIT("", nullptr);

    for(int i=0; i<lst.size(); i++)
    {
        if (!addBarAction(bar, QPixmap(path + lst[i]), lst[i].split(".")[0],
             QSize(24, 24), this, SLOT(handleControlEvent()), false))
        {
                LOG_EXIT("Can't add bar action!", nullptr);
        }
    }

    (*bar)->setFixedWidth(35);

    return *bar;
}

GraphicsView *MainWindow::createGraphicsView(QWidget *parent, GraphicsView **view)
{
    (*view) = new GraphicsView(parent);
    (*view)->setBackgroundBrush(QBrush(QColor(34, 34, 34), Qt::Dense1Pattern));

    return *view;
}

void MainWindow::setBackgroundColor()
{
    this->setStyleSheet("background: rgb(75, 75, 75);");
}

AbstractAlgorithm *MainWindow::createAlgorithm(QObject *parent)
{
    int id;

    if (m_algorithm)
    {
        delete m_algorithm;
        m_algorithm = nullptr;
    }

    switch((id = m_settings ? m_settings->selectedAlgorithm() : BFS))
    {
        case BFS:
        m_algorithm = new BFSAlgorithm(parent);
        break;

        default:
        LOG_DEBUG("Invalid algorithm:" << id);
        return nullptr;

    }

    emit execute();

    return m_algorithm;
}

void MainWindow::restoreItems()
{
    if (!m_view)
        LOG_EXIT("Invalid pointer", );

    m_view->markNode(m_view->getStartNode(), MarkAsStart);
    m_view->markNode(m_view->getFinishNode(), MarkAsFinish);
}

void MainWindow::handleControlEvent()
{
    QAction *action = qobject_cast<QAction*> (sender());

    if (!action || !m_view)
        LOG_EXIT("Invalid pointer!", );

    if (action->text() == "settings")
    {
        if (!m_settings)
            m_settings = new SettingsWindow;

        if (!m_settings->isVisible())
            m_settings->show();
    }

    if (action->text() == "play")
    {
        restoreItems();
        createAlgorithm(this);
    }

    if (action->text() == "restore")
        m_view->deleteAll();
}
