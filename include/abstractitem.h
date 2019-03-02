#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QObject>
#include <QAction>

class AbstractItem : public QObject
{
    Q_OBJECT

public:
    enum ItemID
    {
        NodeID,
        EdgeID,
        UnknownID = -1
    };

public:
    explicit AbstractItem(QObject *parent = Q_NULLPTR);
    virtual ~AbstractItem();
    virtual int id() const = 0;
    void init();

signals:
    void menuItemSelected(QAction*, AbstractItem*);
};

#endif // ABSTRACTITEM_H
