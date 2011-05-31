TEMPLATE = lib
CONFIG += qt plugin
CONFIG += release
QT += declarative

TARGET = clipboard

OBJECTS_DIR = tmp
MOC_DIR = tmp


HEADERS += plugin.h clipboard.h
SOURCES += plugin.cpp
