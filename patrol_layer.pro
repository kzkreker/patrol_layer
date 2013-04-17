#-------------------------------------------------
#
# Project created by QtCreator 2013-04-16T10:00:56
#
#-------------------------------------------------

QT       += core gui xml network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = patrol_layer
TEMPLATE = app

INCLUDEPATH += . ../libmaia/
LIBS += ../libmaia/libmaia.a
#LIBS += /home/kreker/SMBmount/QTdiplom/libmaia/libmaia.a


SOURCES += main.cpp\
        layerwindow.cpp \
    server.cpp \
    database.cpp

HEADERS  += layerwindow.h \
    server.h \
    database.h

FORMS    += layerwindow.ui
