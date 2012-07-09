#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui>
#include "snippethandler.h"

class MainWidget : public QWidget
{
    Q_OBJECT
    
private:
    //Layout
    QVBoxLayout *LayMain;
    QTabWidget *TabMain;
    QHBoxLayout *LaySettings, *LayClipButtons;
    QCheckBox *ChkTransparent, *ChkOnTop;

    //Editor
    QWidget *WidEdit;
    QVBoxLayout *LayEdit;
    QPlainTextEdit *EdtMain;
    QPushButton *BtnCopy, *BtnAppend;

    //Snippets
    QWidget *WidSnippets;
    QVBoxLayout *LaySnippets;
    QStringList SnippetsList;
    QPushButton *BtnEditSnippets;
    QLineEdit *EdtSnippet;
    QPushButton *BtnCopySnippet;
    QList<SnippetHandler*> HandlerList;

    //Settings
    QSettings *Settings;

    //Functions
    void createSnippetButtons();

private slots:
    void setOpacity(int);
    void setOnTop(int);
    void copyClip();
    void appendClip();
    void editSnippets(bool);
    void createNewEdit(QString);


public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
};

#endif // MAINWIDGET_H
