#include "snippet.h"

snippet::snippet(int index, QWidget *parent) :
    QWidget(parent)
{
    iListIndex = index;
    sContent = tr("<leer>");
    initialize();
}

snippet::snippet(int index, QString content, QWidget *parent) :
    QWidget(parent)
{
    iListIndex = index;
    sContent = content;
    initialize();
}

void snippet::initialize()
{
    this->setContentsMargins(-1,-1,-1,-1);
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
        setContent(edit->text());
        edit->hide();
        BtnCopy->show();
    }
}

void snippet::setContent(QString content)
{
    sContent = content;
    BtnCopy->setText(sContent);
    emit contentChanged(iListIndex, sContent);
}

QString snippet::getContent()
{
    return sContent;
}
