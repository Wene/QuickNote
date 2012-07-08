#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    //create Widgets
    LayMain = new QVBoxLayout(this);
    TabMain = new QTabWidget();
    LaySettings = new QHBoxLayout();
    EdtMain = new QPlainTextEdit();
    BtnCopy = new QPushButton(tr("Kopiere Plain Text"));
    ChkTransparent = new QCheckBox(tr("Transparent"));
    ChkOnTop = new QCheckBox(tr("Immer im Vordergrund"));
    WidSnippets = new QWidget();
    WidEdit = new QWidget();
    LaySnippets = new QVBoxLayout();
    LayEdit = new QVBoxLayout();
    BtnEditSnippets = new QPushButton(tr("Bearbeiten"));

    //create Layout
    LayMain->addWidget(TabMain);
    TabMain->addTab(WidEdit, tr("Editor"));
    WidEdit->setLayout(LayEdit);
    LayEdit->addWidget(EdtMain);
    LayEdit->addWidget(BtnCopy);
    LayMain->addLayout(LaySettings);
    LaySettings->addWidget(ChkTransparent);
    LaySettings->addWidget(ChkOnTop);
    LaySettings->addStretch();
    TabMain->addTab(WidSnippets, tr("Schnipsel"));
    WidSnippets->setLayout(LaySnippets);
    LaySnippets->addWidget(BtnEditSnippets);
    LaySnippets->addSpacing(3);

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
    SnippetsList.append(Settings->value("snippets").toStringList());
    for(int i = 0; i < SnippetsList.count(); i++)
    {
        BtnCopySnippet = new QPushButton(SnippetsList.at(i));
        LaySnippets->addWidget(BtnCopySnippet);
    }
    LaySnippets->addStretch();
    Settings->endGroup();

    //connect signals and slots
    connect(ChkTransparent, SIGNAL(stateChanged(int)), this, SLOT(setOpacity(int)));
    connect(ChkOnTop, SIGNAL(stateChanged(int)), this, SLOT(setOnTop(int)));
    connect(BtnCopy, SIGNAL(clicked()), this, SLOT(copyClip()));
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

void MainWidget::copyClip()
{
    QClipboard *Clip = QApplication::clipboard();
    Clip->setText(EdtMain->textCursor().selectedText());
}
