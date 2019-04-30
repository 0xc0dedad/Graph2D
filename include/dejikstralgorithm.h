#ifndef DEJIKSTRALGORITHM_H
#define DEJIKSTRALGORITHM_H

#include "abstractalgorithm.h"

class DejikstraAlgorithm : public AbstractAlgorithm
{
    Q_OBJECT

public:
     explicit DejikstraAlgorithm(QObject *parent = Q_NULLPTR);
     ~DejikstraAlgorithm();

protected:
    virtual void algorithm(Node *start, Node *finish, GraphicsView *view,
    bool order);
    bool checkBranch(QVector<int> &marked, Node *finish, GraphicsView *view,
	bool reset);

private:
        bool wasVisitedFromNode(int from, Vertex *node) const;
        QVector<int> markWay(GraphicsView *view, Node *finish, bool reset);
        void updateToolTips(GraphicsView *view) const;
        void createRaport(Node *first, GraphicsView *view) const;
};

#endif // DEJIKSTRALGORITHM_H
