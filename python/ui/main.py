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
    #check = QtCore.Signal()
    def __init__( self, engine, iface, parent = None ) :
        QtCore.QObject.__init__( self, parent )
        self.land = None
        self.port = None
        self.engine = engine
        self.iface = iface
        self.activeFlag = False
        self.rotateFlag = 0
        self.currentRotate = 0
        self.desktop = QtGui.QApplication.desktop()
        self.desktop.resized.connect( self.desktopResized )
    @QtCore.Slot()
    def checkRotate( self ) :
        #print "check", self.desktop.width(), self.desktop.height()
        if self.desktop.width() > self.desktop.height() :
            return 0
        else :
            return 1
    @QtCore.Slot()
    def desktopResized( self ) :
        rotateFlag = self.checkRotate()
        if self.rotateFlag != rotateFlag :
            self.rotateFlag = rotateFlag
            if self.activeFlag :
                self.rotate()
    def createLand( self ) :
        land = Keyboard( daemonFlag = True )
        #land.setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, False )
        land.set( "./qml/qwert.qml", self.engine, "imEngine" )
        #land.rotateSignal.connect( self.rotate )
        land.commit.connect( self.checkCommit )
        self.land = land
    def createPort( self ) :
        port = Keyboard( daemonFlag = True )
        #port.setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, True )
        port.set( "./qml/vqwert.qml", self.engine, "imEngine" )
        #port.rotateSignal.connect( self.rotate )
        port.commit.connect( self.checkCommit )
        self.port = port
    @QtCore.Slot( str )
    def active( self, text ) :
        self.activeFlag = True
        if self.rotateFlag == 0 :
            if self.land == None :
                self.createLand()
            self.land.setText( text )
            self.land.show()
            self.currentRotate = 0
        elif self.rotateFlag == 1 :
            if self.port == None :
                self.createPort()
            self.port.setText( text )
            self.port.show()
            self.currentRotate = 1
    @QtCore.Slot()
    def rotate( self ) :
        if self.currentRotate == 0 :
            text = self.land.getText()
            self.land.hide()
        elif self.currentRotate == 1 :
            text = self.port.getText()
            self.port.hide()
        self.text = text
        self.active( text )
    @QtCore.Slot( str )
    def checkCommit( self, text ) :
        self.activeFlag = False
        if self.currentRotate == 0 :
            self.land.hide()
        elif self.currentRotate == 1 :
            self.port.hide()
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
    engine.pinyinLookup.dict.logOn()

    iface = Interface( session_bus )
    
    checker = Checker( engine, iface )
    iface.active = checker.active

    desktop = app.desktop()

    print "done"
    
    #qwert.show()

    sys.exit( app.exec_() )
