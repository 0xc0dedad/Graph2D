#include "tab.h"

Tab::Tab(int type, QWidget *parent)
    : QWidget(parent),
      m_list(nullptr)
{
    switch(type)
    {
        case TabType::AlgorithmsTab:
        createAlgorithmsTab(this, &m_list);
        break;

        case TabType::SettingsTab:
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

    this->setLayout(layout);
}

QListWidget *Tab::createAlgorithmsTab(QWidget *parent, QListWidget **list)
{
    QStringList lst;
    QListWidgetItem *item;
    QString path = SettingsWindow::pathToImages();

    lst << "Algo 1" << "Algo 2" << "Algo 3";
    *list = new QListWidget(parent);
    (*list)->setIconSize(QSize(10, 10));

    for(int i=0; i<lst.size(); i++)
    {
        item = new QListWidgetItem(lst[i], *list);
        item->setIcon(QPixmap(path + "algorithm.png"));
    }

    return *list;
}
