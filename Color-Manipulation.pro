#-------------------------------------------------
#
# Project created by QtCreator 2014-04-21T18:20:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Color-Manipulation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clrman.cpp \
    pseudomanwindow.cpp

HEADERS  += mainwindow.h \
    clrman.h \
    pseudomanwindow.h

win32 {
# put windows configuration below
# PLEASE MODIFY THESE DEFINITIONS BEFORE YOU COMPILE
message("Using windows configuration")
OPENCV_PATH = /usr/local/include
LIBS_PATH = /usr/local/lib

LIBS     += -L$$LIBS_PATH \
            -lopencv_core \
            -lopencv_highgui
}

unix {
message("Using unix configuration")

OPENCV_PATH = /usr/local/include
LIBS_PATH = /usr/local/lib

LIBS     += -L$$LIBS_PATH \
            -lopencv_core \
            -lopencv_highgui \
            -lopencv_imgproc
}

INCLUDEPATH += $$OPENCV_PATH

RESOURCES += \
    Resource.qrc
