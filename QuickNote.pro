#-------------------------------------------------
#
# Project created by QtCreator 2012-05-31T11:35:54
#
#-------------------------------------------------

QT       += core gui

TARGET = QuickNote
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    snippethandler.cpp \
    dragbutton.cpp

HEADERS  += mainwidget.h \
    snippethandler.h \
    dragbutton.h

RC_FILE = QuickNote.rc

OTHER_FILES += \
    QuickNote.rc

RESOURCES += \
    QuickNote.qrc
