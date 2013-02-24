/*
QuickNote is a small and simple Notepad
Copyright (C) 2013  Werner Meier <wene83@gmx.ch>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    //create Widgets
    LayMain = new QVBoxLayout(this);
    TabMain = new QTabWidget();
    LaySettings = new QHBoxLayout();
    LayClipButtons = new QHBoxLayout();
    EdtMain = new QPlainTextEdit();
    BtnCopy = new QPushButton(tr("Kopieren"));
    BtnCopy->setToolTip(tr("<p>Kopiert den markierten Bereich als Plain Text in die Zwischenablage</p>"));
    BtnAppend = new QPushButton(tr("Anhängen"));
    BtnAppend->setToolTip(tr("<p>Hängt den Text aus der Zwischenablage zu unterst an</p>"));
    ChkTransparent = new QCheckBox(tr("Transparent"));
    ChkOnTop = new QCheckBox(tr("Immer im Vordergrund"));
    ScrollSnippets = new QScrollArea();
    WidSnippets = new QWidget();
    WidEdit = new QWidget();
    LaySnippets = new QVBoxLayout();
    LayEdit = new QVBoxLayout();
    BtnEditSnippets = new QPushButton(tr("Bearbeiten"));
    BtnEditSnippets->setToolTip(tr("<p>Klicken um die Snipsel zu bearbeiten, "
                                   "erneut klicken um die Bearbeitung abzuschliessen.</p>"
                                   "<p>Bei jeder Bearbeitung steht ein neues leeres Eingabefeld "
                                   "zur Verfügung um neue Inhalte hinzuzufügen.</p>"
                                   "<p>Leere Eingabefelder werden gelöscht.</p>"));
    BtnEditSnippets->setCheckable(true);

    //create Layout
    LayMain->addWidget(TabMain);
    TabMain->addTab(WidEdit, tr("Editor"));
    WidEdit->setLayout(LayEdit);
    LayEdit->addWidget(EdtMain);
    LayEdit->addLayout(LayClipButtons);
    LayClipButtons->addWidget(BtnCopy);
    LayClipButtons->addWidget(BtnAppend);
    LayMain->addLayout(LaySettings);
    LaySettings->addWidget(ChkTransparent);
    LaySettings->addWidget(ChkOnTop);
    LaySettings->addStretch();
    WidSnippets->setLayout(LaySnippets);
    TabMain->addTab(ScrollSnippets, tr("Schnipsel"));
    ScrollSnippets->setWidgetResizable(true);
    ScrollSnippets->setWidget(WidSnippets);
    LaySnippets->addWidget(BtnEditSnippets);

    QFrame *horizontalLine = new QFrame();
    horizontalLine->setFrameStyle(QFrame::HLine);
    LaySnippets->addWidget(horizontalLine);

    //Load Settings
    Settings = new QSettings("QuickNote","QuickNote", this);
    Settings->beginGroup("window");
    QPoint *defaultPos = new QPoint(10,10);
    QSize *defaultSize = new QSize(500,300);
    qreal defaultOpacity = 1.0;
    this->move(Settings->value("position",*defaultPos).toPoint());
    this->resize(Settings->value("size",*defaultSize).toSize());
    this->setWindowOpacity(Settings->value("opacity",defaultOpacity).toReal());
    if(this->windowOpacity() < 1)
    {
        ChkTransparent->setChecked(true);
    }
    if(Settings->value("onTop",false).toInt())
    {
        ChkOnTop->setChecked(true);
        Qt::WindowFlags flags = this->windowFlags();
        this->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    }
    TabMain->setCurrentIndex(Settings->value("activeTab",0).toInt());
    Settings->endGroup();

    Settings->beginGroup("content");
    EdtMain->setPlainText(Settings->value("text","").toString());
    SnippetsList.append(Settings->value("snippets").toStringList());
    createSnippetButtons();
    LaySnippets->addStretch();
    Settings->endGroup();

    //connect signals and slots
    connect(ChkTransparent, SIGNAL(stateChanged(int)), this, SLOT(setOpacity(int)));
    connect(ChkOnTop, SIGNAL(stateChanged(int)), this, SLOT(setOnTop(int)));
    connect(BtnCopy, SIGNAL(clicked()), this, SLOT(copyClip()));
    connect(BtnEditSnippets, SIGNAL(toggled(bool)), this, SLOT(editSnippets(bool)));
    connect(BtnAppend, SIGNAL(clicked()), this, SLOT(appendClip()));
}

//Destructor - save all settings
MainWidget::~MainWidget()
{
    Settings->beginGroup("window");
    Settings->setValue("position",this->pos());
    Settings->setValue("size",this->size());
    Settings->setValue("opacity", this->windowOpacity());
    if(ChkOnTop->isChecked())
    {
        Settings->setValue("onTop",1);
    }
    else
    {
        Settings->setValue("onTop",0);
    }
    Settings->setValue("activeTab", TabMain->currentIndex());
    Settings->endGroup();

    Settings->beginGroup("content");
    Settings->setValue("text",EdtMain->toPlainText());
    Settings->setValue("snippets", SnippetsList);
    Settings->endGroup();
    
}

//private slots
void MainWidget::setOpacity(int checked)
{
    if(checked)
    {
        this->setWindowOpacity(0.60);
    }
    else
    {
        this->setWindowOpacity(1.0);
    }

}

void MainWidget::setOnTop(int checked)
{
    if(checked)
    {
        Qt::WindowFlags flags = this->windowFlags();
        this->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
        this->show();
    }
    else
    {
        Qt::WindowFlags flags = this->windowFlags();
        this->setWindowFlags(flags ^ (Qt::WindowStaysOnTopHint));
        this->show();
    }

}

void MainWidget::copyClip()
{
    QClipboard *Clip = QApplication::clipboard();
    Clip->setText(EdtMain->textCursor().selectedText());
}

void MainWidget::editSnippets(bool bEdit)
{
    if(bEdit)
    {
        int count = LaySnippets->count();

        //Clean up UI and eventhandler
        for(int i = count-1; i > 1; i--) //Continue while more than EditButton and Line are in the Layout
        {
            QLayoutItem *Item = LaySnippets->itemAt(i);
            if(!Item->isEmpty())
            {
                Item->widget()->deleteLater();
            }
            LaySnippets->removeItem(Item);
        }
        for(int i = 0; i < HandlerList.count(); i++)
        {
            SnippetHandler *Handler = HandlerList.at(i);
            delete Handler;
        }
        HandlerList.clear();

        //Create the editor interface
        for(int i = 0; i < SnippetsList.count(); i++)
        {
            EdtSnippet = new QLineEdit(SnippetsList.at(i));
            LaySnippets->addWidget(EdtSnippet);
        }
        EdtSnippet = new QLineEdit();
        LaySnippets->addWidget(EdtSnippet);
        connect(EdtSnippet, SIGNAL(textEdited(QString)), this, SLOT(createNewEdit(QString)));
        LaySnippets->addStretch();
    }
    else
    {
        SnippetsList.clear();
        int count = LaySnippets->count();
        for(int i = 2; i < count-1; i++)
        {
            QLayoutItem *Item = LaySnippets->itemAt(2);
            EdtSnippet = (QLineEdit*)Item->widget();
            if(!EdtSnippet->text().isEmpty())
            {
                SnippetsList.append(EdtSnippet->text());
            }
            EdtSnippet->deleteLater();
            LaySnippets->removeItem(Item);
        }
        LaySnippets->removeItem(LaySnippets->itemAt(2));
        createSnippetButtons();
        LaySnippets->addStretch();
    }
}

void MainWidget::appendClip()
{
    QClipboard *Clipboard = QApplication::clipboard();
    EdtMain->appendPlainText(Clipboard->text());

    //AutoScroll
    QTextCursor cursor = EdtMain->textCursor();
    cursor.movePosition(QTextCursor::End);
    EdtMain->setTextCursor(cursor);
}

void MainWidget::createNewEdit(QString Text)
{
    if(!Text.isEmpty())
    {
        disconnect(EdtSnippet, SIGNAL(textEdited(QString)), this, SLOT(createNewEdit(QString)));
        EdtSnippet = new QLineEdit();
        LaySnippets->insertWidget(LaySnippets->count()-1, EdtSnippet);
        connect(EdtSnippet, SIGNAL(textEdited(QString)), this, SLOT(createNewEdit(QString)));
    }
}

//Functions
void MainWidget::createSnippetButtons()
{
    for(int i = 0; i < SnippetsList.count(); i++)
    {
        QString SnippetText = SnippetsList.at(i);
        BtnCopySnippet = new DragButton(SnippetText);
        BtnCopySnippet->setToolTip(tr("<p>Durch Klick auf diesen Button wird der Text "
                                      "<i>\"%0\"</i> in die Zwischenablage kopiert.").arg(SnippetText));
        LaySnippets->addWidget(BtnCopySnippet);
        SnippetHandler *Handler = new SnippetHandler(SnippetsList.at(i));
        HandlerList.append(Handler);
        connect(BtnCopySnippet, SIGNAL(clicked()), Handler, SLOT(copyToClipboard()));
    }
}
