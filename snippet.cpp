#include "snippet.h"

snippet::snippet(QWidget *parent) :
    QWidget(parent)
{
    sContent = tr("<leer>");

    LayMain = new QHBoxLayout(this);
    BtnCopy = new QPushButton(sContent);
    BtnEdit = new QPushButton(tr("E"));
    BtnEdit->setToolTip(tr("Bearbeiten"));
    BtnEdit->setCheckable(true);
    BtnEdit->setChecked(false);
    BtnDelete = new QPushButton(tr("X"));
    BtnDelete->setToolTip(tr("Löschen"));
    edit = new QLineEdit();
    LayMain->addWidget(BtnCopy);
    LayMain->addWidget(edit);
    edit->hide();
    LayMain->addWidget(BtnEdit);
    LayMain->addWidget(BtnDelete);

    connect(BtnDelete, SIGNAL(clicked()), this, SLOT(deleteLater()));
    connect(BtnEdit, SIGNAL(toggled(bool)), this, SLOT(toggleEdit(bool)));
    connect(BtnCopy, SIGNAL(clicked()), this, SLOT(copyContent()));
}


void snippet::copyContent()
{
    QClipboard *Clip = QApplication::clipboard();
    Clip->setText(sContent);
}

void snippet::toggleEdit(bool editMode)
{
    if(editMode)
    {
        edit->setText(sContent);
        BtnCopy->hide();
        edit->show();
    }
    else
    {
        sContent = edit->text();
        BtnCopy->setText(sContent);
        edit->hide();
        BtnCopy->show();
    }
}
