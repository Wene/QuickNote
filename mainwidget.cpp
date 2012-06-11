#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    //create Widgets
    LayMain = new QVBoxLayout(this);
    Tabs = new QTabWidget();
    FlatWidget = new QWidget();
    ScrollArea = new QScrollArea();
    GridLayout = new QGridLayout();
    LaySettings = new QHBoxLayout();
    EdtMain = new QTextEdit();
    ChkTransparent = new QCheckBox(tr("Transparent"));
    ChkOnTop = new QCheckBox(tr("Immer im Vordergrund"));

    //create Layout
    LayMain->addWidget(Tabs);
    Tabs->addTab(EdtMain, tr("Editor"));
    FlatWidget->setLayout(GridLayout);
    Tabs->addTab(ScrollArea, tr("Schnipsel"));
    LayMain->addLayout(LaySettings);
    LaySettings->addWidget(ChkTransparent);
    LaySettings->addWidget(ChkOnTop);
    LaySettings->addStretch();

    //Test
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            QPushButton *BtnTemp = new QPushButton(tr("Knopf X%0, Y%1")
                                                    .arg(j)
                                                    .arg(i));
            GridLayout->addWidget(BtnTemp, i, j);
        }
    }

    ScrollArea->setWidget(FlatWidget);

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
