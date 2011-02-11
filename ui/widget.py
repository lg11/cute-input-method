#-!- coding=utf-8 -!-

from PySide import QtCore, QtGui
#from PyQt4 import QtCore, QtGui
#QtCore.Signal = QtCore.pyqtSignal
#QtCore.Slot = QtCore.pyqtSlot

class Key( QtGui.QPushButton ) :
    longpressed = QtCore.Signal( int )
    clicked = QtCore.Signal( int )
    DEFAULT_LONGPRESS_INTERVAL = 350
    def __init__( self, keycode, parent = None ) :
        QtGui.QPushButton.__init__( self, parent )
        self.keycode = keycode
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect( self.timeout )
        self.longpress_interval = self.DEFAULT_LONGPRESS_INTERVAL
        #self.stop = self.timer.stop
    def mousePressEvent( self, event ) :
        self.setDown( True )
        self.timer.start( self.longpress_interval )
    def mouseReleaseEvent( self, event ) :
        if self.timer.isActive() :
            self.setDown( False )
            self.timer.stop()
            self.clicked.emit( self.keycode )
    @QtCore.Slot()
    def timeout( self ) :
        self.timer.stop()
        self.setDown( False )
        self.longpressed.emit( self.keycode )
    @QtCore.Slot()
    def stop( self ) :
        self.timer.stop()
        self.setDown( False )
