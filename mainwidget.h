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
    QScrollArea *ScrollSnippets;
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
