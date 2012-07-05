#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui>
#include "snippet.h"

class MainWidget : public QWidget
{
    Q_OBJECT
    
private:
    //Layout
    QVBoxLayout *LayMain;
    QTabWidget *TabMain;
    QHBoxLayout *LaySettings;
    QCheckBox *ChkTransparent, *ChkOnTop;

    //Editor
    QWidget *WidEdit;
    QVBoxLayout *LayEdit;
    QHBoxLayout *LayEditButtons;
    QPlainTextEdit *EdtMain;
    QPushButton *BtnCopy, *BtnPaste;

    //Snippets
    QWidget *WidTabSnippets;
    QVBoxLayout *LaySnippets;
    snippet *Snippet;
    QPushButton *BtnAddSnippet;


    //Settings
    QSettings *Settings;

private slots:
    void copyClip();
    void pasteClip();
    void setOpacity(int);
    void setOnTop(int);
    void addSnippet();

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
};

#endif // MAINWIDGET_H
