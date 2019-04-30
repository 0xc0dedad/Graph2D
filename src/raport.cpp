#include "raport.h"
#include "abstractalgorithm.h"

Raport::Raport(QWidget *parent)
    : AbstractWindow(parent),
      m_lbl(nullptr)
{
    layout();
    this->setMinimumWidth(Width);
    this->setMinimumHeight(Height);
}

Raport::~Raport()
{

}


void Raport::layout()
{
    QVBoxLayout *layout = new QVBoxLayout;

    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    if (createLabel("", QFont("Ubuntu", 10), &m_lbl))
        layout->addWidget(m_lbl);

    this->setLayout(layout);
}

void Raport::setRaport(QVector<int> raport)
{
    size_t counter = 0, limit = 15;

    m_lbl->setText("Nodes: ");

    for(int i=0; i<raport.size(); i++)
    {
        if (counter == limit)
        {
            m_lbl->setText(m_lbl->text() + "<br/>");
            counter = 0;
        }

        m_lbl->setText(m_lbl->text() + QString::number(raport[i]) + " - ");
        counter++;
    }
}

void Raport::setRaport(QString msg)
{
    m_lbl->setText(msg);
}

void Raport::appendRaport(QVector<int> raport, QString msg)
{
    size_t counter = 0, limit = 15;

    m_lbl->setText(m_lbl->text() + "<br/>" + msg);

    for(int i=0; i<raport.size(); i++)
    {
        if (counter == limit)
        {
            m_lbl->setText(m_lbl->text() + "<br/>");
            counter = 0;
        }

        m_lbl->setText(m_lbl->text() + QString::number(raport[i]) + " - ");
        counter++;
    }
}
