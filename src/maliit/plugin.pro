TEMPLATE = lib

#MEEGO_IM_PLUGINS_DIR = $$system( pkgconfig --variable pluginsdir MeegoImFramework )

CONFIG += plugin
CONFIG += meegoimframework
CONFIG += meegoimquick

QT = core gui declarative

TARGET = cuteinputmethod

OBJECTS_DIR = tmp
MOC_DIR = tmp

#INCLUDEPATH += /usr/include/meegoimquick /usr/include/meegoimframework /usr/include/meego-keyboard

HEADERS += plugin.h inputmethod.h
SOURCES += plugin.cpp inputmethod.cpp
