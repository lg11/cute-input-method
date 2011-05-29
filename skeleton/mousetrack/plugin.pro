TEMPLATE = lib
CONFIG += qt plugin
CONFIG += release
QT += declarative

TARGET = mousetrack

OBJECTS_DIR = tmp
MOC_DIR = tmp


HEADERS += plugin.h track.h
SOURCES += plugin.cpp
