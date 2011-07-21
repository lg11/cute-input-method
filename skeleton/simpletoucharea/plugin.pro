TEMPLATE = lib
CONFIG += qt plugin
CONFIG += release
QT += declarative

TARGET = simpletoucharea

OBJECTS_DIR = tmp
MOC_DIR = tmp


HEADERS += plugin.h simpletoucharea.h
SOURCES += plugin.cpp
