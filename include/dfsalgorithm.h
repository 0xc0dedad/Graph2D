#ifndef DFSALGORITHM_H
#define DFSALGORITHM_H

#include "abstractalgorithm.h"

class DFSAlgorithm : public AbstractAlgorithm
{
    Q_OBJECT

public:
     explicit DFSAlgorithm(QObject *parent = Q_NULLPTR);
     ~DFSAlgorithm();

protected:
    virtual void algorithm(Node *start, Node *finish, GraphicsView *view,
    bool order);
};

#endif // DFSALGORITHM_H
