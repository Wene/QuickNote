#ifndef SNIPPET_H
#define SNIPPET_H

#include <QtGui>

class snippet : public QWidget
{
    Q_OBJECT
public:
    explicit snippet(QWidget *parent = 0);
    explicit snippet(QString content, QWidget *parent = 0);
    QString getContent();

private:
    QHBoxLayout *LayMain;
    QPushButton *BtnCopy, *BtnEdit, *BtnDelete;
    QLineEdit *edit;

    QString sContent;

    void initialize();

signals:

public slots:
    void copyContent();
    void toggleEdit(bool editMode);
    void setContent(QString content);

};

#endif // SNIPPET_H
