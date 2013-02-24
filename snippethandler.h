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

#ifndef SNIPPETHANDLER_H
#define SNIPPETHANDLER_H

#include <QtGui>

class SnippetHandler : public QObject
{
    Q_OBJECT
public:
    explicit SnippetHandler(QString Text, QObject *parent = 0);

private:
    QString sContent;
signals:

public slots:
    void copyToClipboard();

};

#endif // SNIPPETHANDLER_H
