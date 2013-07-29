! include( $$_PRO_FILE_PWD_/common.pri ){
    error( "Couldn't find the common.pri file!" )
}

TEMPLATE = app

CONFIG += console
CONFIG -= qt
CONFIG += warn_on

DESTDIR = bin
OBJECTS_DIR = build

HEADERS +=

SOURCES += main.cpp

LIBS += -lccn -L./libdash/libdash/lib/build/bin/libdash.so \

