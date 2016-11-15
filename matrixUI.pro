#-------------------------------------------------
#
# Project created by QtCreator 2016-10-17T21:21:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = matrixUI
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp \
    maxrectangle.cpp \
    dominantpoints.cpp \
    boundedrectangle.cpp \
    range_tree.cpp \
    segment_tree.cpp \
    class_4_rect.cpp \
    class_3_rect.cpp \
    class_2_rect.cpp \
    class_1_rect.cpp

HEADERS  += mainwindow.h \
    renderarea.h \
    maxrectangle.h \
    utility.h \
    dominantpoints.h \
    boundedrectangle.h \
    range_tree.h \
    binarysearchtree.h \
    segment_tree.h \
    segment_tree_new.h \
    node.h \
    interval.h \
    utils.h \
    class_4_rect.h \
    range_tree_node.h \
    class_3_rect.h \
    class_2_rect.h \
    class_1_rect.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/cgal/4.9/lib/release/ -lCGAL.12.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/cgal/4.9/lib/debug/ -lCGAL.12.0.0
else:unix: LIBS += -L$$PWD/../../../../usr/local/Cellar/cgal/4.9/lib/ -lCGAL.12.0.0

INCLUDEPATH += $$PWD/../../../../usr/local/Cellar/cgal/4.9/include
DEPENDPATH += $$PWD/../../../../usr/local/Cellar/cgal/4.9/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/boost/1.62.0/lib/release/ -lboost_filesystem
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/boost/1.62.0/lib/debug/ -lboost_filesystem
else:unix: LIBS += -L$$PWD/../../../../usr/local/Cellar/boost/1.62.0/lib/ -lboost_filesystem

INCLUDEPATH += $$PWD/../../../../usr/local/Cellar/boost/1.62.0/include
DEPENDPATH += $$PWD/../../../../usr/local/Cellar/boost/1.62.0/include
