#include <QtGui/QApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("qt_de", ":/system");
    a.installTranslator(&translator);

    MainWidget w;
    w.show();
    
    return a.exec();
}
