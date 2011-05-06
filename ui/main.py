#!/usr/bin/python
#-!- coding=utf-8 -!-

import sys
sys.path.append( "./pinyinLookup" )
sys.path.append( "./qwert" )
sys.path.append( "./ui" )
sys.path.append( "./utils" )

from interface import Interface
from inputpad import InputPad
from pinyinKeyboard import PinyinKeyboard

import dbus
import dbus.service
from dbus.mainloop.qt import DBusQtMainLoop

from PySide import QtCore, QtGui
#from PyQt4 import QtCore, QtGui
#QtCore.Signal = QtCore.pyqtSignal
#QtCore.Slot = QtCore.pyqtSlot

class Checker() :
    def __init__( self, num, qwert ) :
        self.numInput = num
        self.qwertInput = qwert
        self.desktop = QtGui.QDesktopWidget()
    def active( self, text ) :
        rect = self.desktop.screenGeometry()
        if rect.height() < rect.width() :
            self.qwertInput.come( text )
        else :
            self.numInput.callback_show( text )

if __name__ == "__main__" :
    app = QtGui.QApplication( sys.argv )
    DBusQtMainLoop( set_as_default=True )

    session_bus = dbus.SessionBus()
    name = dbus.service.BusName( "me.maemo.input.chinese", session_bus )
    pad = InputPad( True )
    qwert = PinyinKeyboard()
    iface = Interface( session_bus, pad )
    
    checker = Checker( pad, qwert )
    iface.active = checker.active

    pad.request_commit.connect( iface.commit )

    print "done"
    
    qwert.show()

    sys.exit( app.exec_() )
