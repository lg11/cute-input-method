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
#from PyQt4 import QtCore, QtGui
#QtCore.Signal = QtCore.pyqtSignal
#QtCore.Slot = QtCore.pyqtSlot

class Rotater( QtGui.QWidget ) :
    rotateFinished = QtCore.Signal( int )
    def __init__( self, flag, desktop, parent = None ) :
        QtGui.QWidget.__init__( self, parent )
        self.setWindowFlags( QtCore.Qt.Dialog | QtCore.Qt.FramelessWindowHint )
        self.setFixedHeight( 1 )
        self.flag = flag
        self.desktop = desktop
    def resizeEvent( self, event ) :
        #print event.size().width(), event.size().height(), self.desktop.width(), self.desktop.height()
        if event.size().width() == self.desktop.width() :
            self.rotateFinished.emit( self.flag )
        #self.hide()
    def closeEvent( self, event ) :
        self.hide()
        event.ignore()

class Checker() :
    def __init__( self, engine, iface ) :
        self.land = None
        self.port = None
        self.engine = engine
        self.iface = iface
        self.flag = 0
        self.desktop = QtGui.QDesktopWidget()
        self.currentRotate = self.checkRotate()
        self.rotater = []
        self.rotater.append( Rotater( 0, self.desktop ) )
        self.rotater.append( Rotater( 1, self.desktop ) )
        self.rotater[0].setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, False )
        self.rotater[1].setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, True )
        self.rotater[0].rotateFinished.connect( self.recoverDone )
        self.rotater[1].rotateFinished.connect( self.recoverDone )
    def checkRotate( self ) :
        if self.desktop.width() > self.desktop.height() :
            return 0
        else :
            return 1
    def createLand( self ) :
        land = Keyboard( daemonFlag = True )
        land.setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, False )
        land.set( "./qml/qwert.qml", self.engine, "imEngine" )
        land.rotateSignal.connect( self.rotate )
        #land.commit.connect( self.iface.commit )
        land.commit.connect( self.recover )
        self.land = land
    def createPort( self ) :
        port = Keyboard( daemonFlag = True )
        port.setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, True )
        port.set( "./qml/vqwert.qml", self.engine, "imEngine" )
        port.rotateSignal.connect( self.rotate )
        #port.commit.connect( self.iface.commit )
        port.commit.connect( self.recover )
        self.port = port
    @QtCore.Slot( str )
    def active( self, text ) :
        self.currentRotate = self.checkRotate()
        if self.flag == 0 :
            if self.land == None :
                self.createLand()
            self.land.setText( text )
            self.land.show()
        elif self.flag == 1 :
            if self.port == None :
                self.createPort()
            self.port.setText( text )
            self.port.show()
    @QtCore.Slot()
    def rotate( self ) :
        if self.flag == 0 :
            self.flag = 1
            text = self.land.getText()
            self.land.hide()
        elif self.flag == 1 :
            self.flag = 0
            text = self.port.getText()
            self.port.hide()
        self.text = text
        self.active( text )
    @QtCore.Slot()
    def recover( self, text ) :
        self.text = text
        #print "recover", self.flag, self.currentRotate
        if self.flag != self.currentRotate :
            self.rotater[self.currentRotate].show()
        else :
            self.iface.commit( self.text )
    @QtCore.Slot( int )
    def recoverDone( self, flag ) :
        self.rotater[flag].hide()
        self.iface.commit( self.text )


if __name__ == "__main__" :
    app = QtGui.QApplication( sys.argv )
    DBusQtMainLoop( set_as_default=True )

    session_bus = dbus.SessionBus()
    name = dbus.service.BusName( "me.maemo.input.chinese", session_bus )
    #pad = InputPad( True )

    engine = IMEngine()
    engine.load( "./data/formated" )
    engine.load( "/home/user/.config/mcip/userdict.log" )
    engine.pinyinLookup.dict.logOn()

    iface = Interface( session_bus )
    
    checker = Checker( engine, iface )
    iface.active = checker.active

    print "done"
    
    #qwert.show()

    sys.exit( app.exec_() )
