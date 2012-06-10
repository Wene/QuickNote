#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui>

class MainWidget : public QWidget
{
    Q_OBJECT
    
private:
    //Widgets
    QVBoxLayout *LayMain;
    QTabWidget *Tabs;
    QWidget *FlatWidget;
    QScrollArea *ScrollArea;
    QGridLayout *GridLayout;
    QHBoxLayout *LaySettings;
    QTextEdit *EdtMain;
    QCheckBox *ChkTransparent, *ChkOnTop;

    //Objects
    QSettings *Settings;

private slots:
    void setOpacity(int);
    void setOnTop(int);

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
};

#endif // MAINWIDGET_H
