#ifndef SNIPPET_H
#define SNIPPET_H

#include <QtGui>

class snippet : public QWidget
{
    Q_OBJECT
public:
    explicit snippet(QWidget *parent = 0);

private:
    QHBoxLayout *LayMain;
    QPushButton *BtnCopy, *BtnEdit, *BtnDelete;

signals:

public slots:

};

#endif // SNIPPET_H
