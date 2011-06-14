TEMPLATE = lib
CONFIG += qt plugin
QT += dbus

DEPENDPATH += .
INCLUDEPATH += .

TARGET = cuteinputmethod

OBJECTS_DIR = tmp
MOC_DIR = tmp

;unix {
    ;CONFIG += link_pkgconfig
    ;PKGCONFIG += pkg-config gtk+-2.0 sunpinyin-2.0 sqlite3 
;}

# Input
HEADERS += context.h adaptor.h plugin.h
SOURCES += context.cpp adaptor.cpp plugin.cpp
