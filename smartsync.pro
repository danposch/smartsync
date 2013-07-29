! include( $$_PRO_FILE_PWD_/common.pri ){
    error( "Couldn't find the common.pri file!" )
}

TEMPLATE = app

CONFIG += console
CONFIG -= qt
CONFIG += warn_on

DESTDIR = bin
OBJECTS_DIR = build

INCLUDEPATH += /usr/include/

HEADERS += \
    smartsyncdaemon.h

SOURCES += main.cpp \
    smartsyncdaemon.cpp

LIBS += -L/usr/lib \
        -lccn \
        -lcrypto \
        -lboost_thread \
        -L./libdash/libdash/lib/build/bin/libdash.so \

