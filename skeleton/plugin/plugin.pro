TEMPLATE = lib
CONFIG += qt plugin
CONFIG += release
QT += declarative

TARGET = engine

OBJECTS_DIR = tmp
MOC_DIR = tmp


HEADERS += plugin.h engine.h
SOURCES += plugin.cpp
