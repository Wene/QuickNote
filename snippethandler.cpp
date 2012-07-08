#include "snippethandler.h"

SnippetHandler::SnippetHandler(QString Text, QObject *parent) :
    QObject(parent)
{
    sContent = Text;
}

void SnippetHandler::copyToClipboard()
{
    QClipboard *Clipboard = QApplication::clipboard();
    Clipboard->setText(sContent);
}
