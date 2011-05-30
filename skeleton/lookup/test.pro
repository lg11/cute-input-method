TEMPLATE = app
TARGET = test
;DEPENDPATH += .
;INCLUDEPATH += .

OBJECTS_DIR = tmp
CONFIG += release
;CONFIG += debug
QT += core
;QT += core gui declarative


;unix {
    ;CONFIG += link_pkgconfig
    ;PKGCONFIG += dbus-python
;}

;INCLUDEPATH += /usr/include/python2.5
;LIBS += -L/usr/lib/python2.5 -lpython2.5

# Input
HEADERS += dict.h split.h fit.h pick.h lookup.h trie.h
SOURCES += main.cpp
