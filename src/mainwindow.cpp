#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : AbstractWindow(parent),
      m_settings_bar(nullptr)
{
    layout();
}

MainWindow::~MainWindow()
{

}

MainWindow &MainWindow::instance(QWidget *parent)
{
    static MainWindow instance(parent);

    return instance;
}

void MainWindow::layout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *hl = new QHBoxLayout;

    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(0, 0, 0, 0);

    if (createSettingsBar(this, &m_settings_bar))
        hl->addWidget(m_settings_bar);

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

    return *bar;
}

void MainWindow::showSettings()
{

}
