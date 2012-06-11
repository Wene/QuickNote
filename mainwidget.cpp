#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    //create Widgets
    LayMain = new QVBoxLayout(this);
    TabMain = new QTabWidget();
    LaySettings = new QHBoxLayout();
    EdtMain = new QTextEdit();
    ChkTransparent = new QCheckBox(tr("Transparent"));
    ChkOnTop = new QCheckBox(tr("Immer im Vordergrund"));

    //create Layout
    LayMain->addWidget(TabMain);
    TabMain->addTab(EdtMain, tr("Editor"));
    LayMain->addLayout(LaySettings);
    LaySettings->addWidget(ChkTransparent);
    LaySettings->addWidget(ChkOnTop);
    LaySettings->addStretch();

    //create Snippets Tab
    WidTabSnippets = new QWidget();
    TabMain->addTab(WidTabSnippets, tr("Schnippsel"));

    //Dummy Settings
    StrSnippets = new QStringList();
    for(int i = 0; i < 20; i++)
    {
        StrSnippets->append(tr("Zeile %0").arg(i+1));
    }

    this->showButtons();

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
    Settings->endGroup();
    Settings->beginGroup("content");
    EdtMain->setPlainText(Settings->value("text","").toString());
    Settings->endGroup();

    //connect signals and slots
    connect(ChkTransparent, SIGNAL(stateChanged(int)), this, SLOT(setOpacity(int)));
    connect(ChkOnTop, SIGNAL(stateChanged(int)), this, SLOT(setOnTop(int)));

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
    Settings->endGroup();

    Settings->beginGroup("content");
    Settings->setValue("text",EdtMain->toPlainText());
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

void MainWidget::editList()
{
    if(WidTabSnippets->layout())
    {
        delete WidTabSnippets->layout();
    }
    LaySnippets = new QVBoxLayout();
    WidTabSnippets->setLayout(LaySnippets);
    BtnToggleEdit = new QPushButton(tr("Bearbeitung abgeschlossen"));
    LaySnippets->addWidget(BtnToggleEdit);
    connect(BtnToggleEdit, SIGNAL(clicked()), this, SLOT(showButtons()));
    EdtSnippets = new QTextEdit;
    LaySnippets->addWidget(EdtSnippets);
    QString str;
    foreach(str, *StrSnippets)
    {
        EdtSnippets->append(str);
    }
}

void MainWidget::showButtons()
{
    if(WidTabSnippets->layout())
    {
        delete WidTabSnippets->layout();
    }
    LaySnippets = new QVBoxLayout();
    WidTabSnippets->setLayout(LaySnippets);
    BtnToggleEdit = new QPushButton(tr("Liste Bearbeiten"));
    LaySnippets->addWidget(BtnToggleEdit);
    connect(BtnToggleEdit, SIGNAL(clicked()), this, SLOT(editList()));
    QString str;
    foreach(str, *StrSnippets)
    {
        LaySnippets->addWidget(new QPushButton(str));
    }
}
