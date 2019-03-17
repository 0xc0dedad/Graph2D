#ifndef BFSALGORITHM_H
#define BFSALGORITHM_H

#include "abstractalgorithm.h"

class BFSAlgorithm : public AbstractAlgorithm
{
    Q_OBJECT

public:
     explicit BFSAlgorithm(QObject *parent = Q_NULLPTR);
     ~BFSAlgorithm();

protected:
    virtual void algorithm(Node *start, Node *finish, GraphicsView *view);
};

#endif // BFSALGORITHM_H
