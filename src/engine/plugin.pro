TEMPLATE = lib
CONFIG += qt plugin
CONFIG += release
QT += declarative

TARGET = engine

OBJECTS_DIR = tmp
MOC_DIR = tmp


HEADERS += plugin.h engine.h ../lookup/dict.h ../lookup/fit.h ../lookup/lookup.h ../lookup/pick.h ../lookup/split.h ../lookup/t9.h ../lookup/trie.h 
SOURCES += plugin.cpp engine.cpp
