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
