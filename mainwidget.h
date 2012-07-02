#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui>

class MainWidget : public QWidget
{
    Q_OBJECT
    
private:
    //Widgets
    QVBoxLayout *LayMain;
    QHBoxLayout *LaySettings;
    QPlainTextEdit *EdtMain;
    QCheckBox *ChkTransparent, *ChkOnTop;
    QPushButton *BtnCopy;

    //Objects
    QSettings *Settings;

private slots:
    void setOpacity(int);
    void setOnTop(int);
    void copyClip();

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
};

#endif // MAINWIDGET_H
