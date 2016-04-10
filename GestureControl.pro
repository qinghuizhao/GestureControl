#-------------------------------------------------
#
# Project created by QtCreator 2015-08-24T18:28:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = handobject
TEMPLATE = app
PRJ_PATH = $${PWD}
DESTDIR = $${PRJ_PATH}/build

#win cv lib,replace with your lib location
CV_INC = /usr/local/include
CV_LIB = /usr/local/lib
INCLUDEPATH += /usr/include
INCLUDEPATH += /usr/local/freetype/include
INCLUDEPATH += /usr/local/freetype/include/freetype2
INCLUDEPATH += /usr/local/freetype/include/freetype2
POINTGREY_LIB = $${PRJ_PATH}/libs/unix/POINTGREY

LIBS += -L$${CV_LIB} -lopencv_ml -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video  -lopencv_legacy -lopencv_contrib
LIBS+=/usr/local/freetype/lib/libfreetype.a


SOURCES += main.cpp\
        mainwindow.cpp \
    reghand.cpp \
    videodlg.cpp \
    src/cvxtext.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/reghand.cpp \
    src/videodlg.cpp

HEADERS  += mainwindow.h \
    reghand.h \
    videodlg.h \
    src/cvxtext.h \
    src/mainwindow.h \
    src/reghand.h \
    src/videodlg.h

FORMS    += mainwindow.ui \
    videodlg.ui \
    src/mainwindow.ui \
    src/videodlg.ui
