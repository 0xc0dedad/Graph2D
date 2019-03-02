#include "abstractitem.h"
#include "mainwindow.h"

AbstractItem::AbstractItem(QObject *parent)
    : QObject(parent)
{
    init();
}

AbstractItem::~AbstractItem()
{

}

void AbstractItem::init()
{
    GraphicsView *handler = MainWindow::instance().getView();

    if (!handler)
        LOG_EXIT("Invalid handler", );

    connect(this, SIGNAL(menuItemSelected(QAction*, AbstractItem*)), handler,
     SLOT(modeHandler(QAction*, AbstractItem*)));
}
