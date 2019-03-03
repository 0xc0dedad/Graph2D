#include <abstractwindow.h>

AbstractWindow::AbstractWindow(QWidget *parent)
    : QWidget(parent)
{

}

AbstractWindow::~AbstractWindow()
{

}

QString AbstractWindow::pathToImages() const
{
    return QApplication::applicationDirPath() + "/images/";
}

QToolBar *AbstractWindow::createToolBar(QWidget *parent, QToolBar **bar)
{
    (*bar) = new QToolBar(parent);
    (*bar)->setOrientation(Qt::Vertical);

    return *bar;
}

QAction *AbstractWindow::addBarAction(QToolBar **bar, QIcon icon,
  QString tooltip, QSize size, QWidget *handler, const char *slot,
   bool is_checkable)
{
    QAction *action = new QAction(this);

    if (!bar || !slot || !handler)
    {
        delete action;
        return nullptr;
    }

    (*bar)->setIconSize(size);

    action->setIcon(icon);
    action->setText(tooltip);
    action->setCheckable(is_checkable);

    connect(action, SIGNAL(triggered(bool)), handler, slot);
    (*bar)->addAction(action);

    return action;
}

QGroupBox *AbstractWindow::createGroupBox(QWidget *parent, QGroupBox **group)
{
    (*group) = new QGroupBox(parent);

    return *group;
}

QLabel *AbstractWindow::createLabel(QString title, QFont font, QLabel **lbl)
{
    (*lbl) = new QLabel;
    (*lbl)->setText(title);
    (*lbl)->setFont(font);

    return *lbl;
}
