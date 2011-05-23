#!/usr/bin/python
#-!- coding=utf-8 -!-

import sys
sys.path.append( "./pinyinLookup" )
sys.path.append( "./qwert" )
sys.path.append( "./ui" )
sys.path.append( "./utils" )

from interface import Interface
#from inputpad import InputPad
from keyboard import Keyboard
from engine import IMEngine

import dbus
import dbus.service
from dbus.mainloop.qt import DBusQtMainLoop

from PySide import QtCore, QtGui

#class Rotater( QtGui.QWidget ) :
    #rotateFinished = QtCore.Signal( int )
    #def __init__( self, flag, desktop, parent = None ) :
        #QtGui.QWidget.__init__( self, parent )
        #self.setWindowFlags( QtCore.Qt.Dialog | QtCore.Qt.FramelessWindowHint )
        #self.setFixedHeight( 1 )
        #self.flag = flag
        #self.desktop = desktop
    #def resizeEvent( self, event ) :
        #print event.size().width(), event.size().height(), self.desktop.width(), self.desktop.height()
        #if event.size().width() == self.desktop.width() :
            #self.rotateFinished.emit( self.flag )
    #def closeEvent( self, event ) :
        #self.hide()
        #event.ignore()

class Checker( QtCore.QObject ) :
    def __init__( self, engine, iface, parent = None ) :
        QtCore.QObject.__init__( self, parent )
        self.port = None
        self.engine = engine
        self.iface = iface
        self.keyboard = self.createKeyboard()
        self.commitTimer = QtCore.QTimer()
        self.commitTimer.setSingleShot( True )
        self.commitTimer.timeout.connect( self.commit )
        self.commitText = ""
    def createKeyboard( self ) :
        keyboard = Keyboard( daemonFlag = True )
        keyboard.set( "./qml/qwert.qml", self.engine, "imEngine" )
        keyboard.commit.connect( self.checkCommit )
        return keyboard
    @QtCore.Slot( str )
    def active( self, text ) :
        self.keyboard.setText( text )
        self.keyboard.show()
    @QtCore.Slot( str )
    def checkCommit( self, text ) :
        self.commitText = text
        self.keyboard.hide()
        self.commitTimer.start( 10 )
    @QtCore.Slot()
    def commit( self ) :
        self.commitTimer.stop()
        #print "delay commit test"
        text = self.commitText
        if len( text ) > 0 :
            if text[-1] == "\n" :
                self.iface.commit( text[:-1] )
                self.iface.enter()
            else :
                self.iface.commit( text )
        else :
            self.iface.commit( text )

if __name__ == "__main__" :
    app = QtGui.QApplication( sys.argv )
    DBusQtMainLoop( set_as_default=True )

    session_bus = dbus.SessionBus()
    name = dbus.service.BusName( "me.maemo.input.chinese", session_bus )
    #pad = InputPad( True )

    engine = IMEngine()
    engine.load( "./data/formated" )
    engine.load( "/home/user/.config/mcip/userdict.log" )
    engine.lookup[0].dict.logOn()

    iface = Interface( session_bus )
    
    checker = Checker( engine, iface )
    iface.active = checker.active

    desktop = app.desktop()

    print "done"
    
    #qwert.show()

    sys.exit( app.exec_() )
