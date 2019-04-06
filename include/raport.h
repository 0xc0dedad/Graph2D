#ifndef RAPORT_H
#define RAPORT_H

#include "abstractwindow.h"

class Raport : public AbstractWindow
{
    Q_OBJECT

    enum
    {
      Width = 450,
      Height = 150
    };

public:
    explicit Raport(QWidget *parent = Q_NULLPTR);
    ~Raport();
    void setRaport(QVector<int>);
    void appendRaport(QVector<int>, QString msg);

private:
    void layout();

private:
    QLabel *m_lbl;
    QWidget *m_parent;
};

#endif // RAPORT_H
