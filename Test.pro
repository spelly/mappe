#-------------------------------------------------
#
# Project created by QtCreator 2013-03-29T20:15:34
#
#-------------------------------------------------

QT += sql widgets printsupport core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    querybuilder.cpp \
    qcustomplot.cpp \
    graph.cpp

HEADERS  += mainwindow.h \
    querybuilder.h \
    qcustomplot.h \
    graph.h

FORMS    +=
