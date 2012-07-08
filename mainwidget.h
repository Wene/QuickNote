#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui>

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
    QPlainTextEdit *EdtMain;
    QPushButton *BtnCopy;

    //Snippets
    QWidget *WidSnippets;
    QVBoxLayout *LaySnippets;
    QStringList SnippetsList;
    QPushButton *BtnEditSnippets;
    QLineEdit *EdtSnippet;
    QPushButton *BtnCopySnippet;

    //Settings
    QSettings *Settings;

private slots:
    void setOpacity(int);
    void setOnTop(int);
    void copyClip();
    void editSnippets(bool);

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
};

#endif // MAINWIDGET_H
