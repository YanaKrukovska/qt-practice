QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimplePaint
TEMPLATE = app


SOURCES += main.cpp\
    canvas.cpp \
    canvascreator.cpp \
    mainwindow.cpp

HEADERS  += \
    canvas.h \
    canvascreator.h \
    mainwindow.h

FORMS += \
    canvascreator.ui \
    mainwindow.ui
