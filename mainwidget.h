#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui>
#include <QtGlobal>

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
    QTextEdit *EdtMain;

    //Snippets
    QWidget *WidTabSnippets;
    QVBoxLayout *LaySnippets;
    QTextEdit *EdtSnippets;
    QPushButton *BtnToggleEdit, *BtnSnippet;
    QStringList *StrSnippets;

    //Settings
    QSettings *Settings;

private slots:
    void setOpacity(int);
    void setOnTop(int);
    void editList();
    void showButtons();

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
};

#endif // MAINWIDGET_H
