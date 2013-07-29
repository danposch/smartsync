! include( $$_PRO_FILE_PWD_/common.pri ){
    error( "Couldn't find the common.pri file!" )
}

TEMPLATE = app

CONFIG += console
CONFIG -= qt
CONFIG += warn_on

DESTDIR = bin
OBJECTS_DIR = build

INCLUDEPATH += /usr/include/ \
               ./libdash/libdash/libdash/include

HEADERS += \
    smartsyncdaemon.h \
    simpledownloader.h

SOURCES += main.cpp \
    smartsyncdaemon.cpp \
    simpledownloader.cpp

LIBS += -L/usr/lib \
        -lccn \
        -lcrypto \
        -lboost_thread \
        -lboost_system \
        -lboost_filesystem \
        -L./libdash/libdash/build/bin/ -ldash

