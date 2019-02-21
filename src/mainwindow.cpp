#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : AbstractWindow(parent),
      m_settings_bar(nullptr),
      m_view(nullptr)
{
    layout();
    setBackgroundColor();
}

MainWindow::~MainWindow()
{

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

    if (!createToolBar(parent, bar))
        LOG_EXIT("", nullptr);

    if (!addBarAction(bar, QPixmap(path + "settings.png"), "",
         QSize(24, 24), this, SLOT(showSettings()), false))
    {
            LOG_EXIT("Can't add bar action!", nullptr);
    }

    (*bar)->setFixedSize(35, 35);

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

void MainWindow::showSettings()
{

}
