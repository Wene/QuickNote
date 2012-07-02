#include "snippet.h"

snippet::snippet(QWidget *parent) :
    QWidget(parent)
{
    LayMain = new QHBoxLayout(this);
    BtnCopy = new QPushButton(tr("Kopieren"));
    BtnEdit = new QPushButton(tr("Bearbeiten"));
    BtnDelete = new QPushButton(tr("Löschen"));
    LayMain->addWidget(BtnCopy);
    LayMain->addWidget(BtnEdit);
    LayMain->addWidget(BtnDelete);

    connect(BtnDelete, SIGNAL(clicked()), this, SLOT(deleteLater()));
}
