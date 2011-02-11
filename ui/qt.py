#-!- coding=utf-8 -!-
import sys

#from PySide import QtGui, QtCore
from PyQt4 import QtGui, QtCore
QtCore.Signal = QtCore.pyqtSignal

class NumArea():
    def __init__( self ):
        self.x = 300
        self.y = 0
        self.button_width = 144
        self.button_height = 120
        self.track = []
    def check( self, x, y ):
        x = x - self.x
        y = y - self.y
        i = x / self.button_width
        j = y / self.button_height
        idx = i + j * 3 + 1
        if len( self.track ) == 0 :
            self.track.append( idx )
        else:
            print idx
            print self.track[-1]
            if idx != self.track[-1]:
                self.track.append( idx )
        print self.track
    def reset( self ):
        self.track = []

class InputPad( QtGui.QWidget ):
    request_quit = QtCore.Signal()
    def __init__( self, parent = None ):
        QtGui.QWidget.__init__( self, parent )
        self.longpress_stamp = 0
        self.mouse_track = QtGui.QPainterPath()
        self.num_area = NumArea()
    def mousePressEvent( self, event ):
        print "press %d, %d" %( event.x(), event.y() )
        self.longpress_stamp = self.longpress_stamp + 1
        if self.longpress_stamp > 65535:
            self.longpress_stamp = 0
        self.mouse_track = QtGui.QPainterPath()
        self.mouse_track.moveTo( event.x(), event.y() )
        self.num_area.reset()
        self.num_area.check( event.x(), event.y() )
        self.repaint()
    def mouseReleaseEvent( self, event ):
        print "release %d, %d" %( event.x(), event.y() )
        self.longpress_stamp = self.longpress_stamp + 1
        if self.longpress_stamp > 65535:
            self.longpress_stamp = 0
        self.mouse_track.lineTo( event.x(), event.y() )
        self.num_area.check( event.x(), event.y() )
        self.repaint()
    def mouseMoveEvent( self, event ):
        print "move %d, %d" %( event.x(), event.y() )
        #self.track = QtGui.QPaintPath( event.pos )
        self.longpress_stamp = self.longpress_stamp + 1
        if self.longpress_stamp > 65535:
            self.longpress_stamp = 0
        self.mouse_track.lineTo( event.x(), event.y() )
        self.num_area.check( event.x(), event.y() )
        self.repaint()
    #@QtCore.Slot(int)
    #def slot_int(i):
        #print i
    def mouseDoubleClickEvent( self, event ):
        print "double click"
        #self.request_quit.emit()
    #def draw( self, painter ):
    def draw_num_area( self, painter ):
        painter.translate( self.num_area.x, self.num_area.y )
        painter.fillRect( 0, 0, self.num_area.button_width * 3 + 1 , self.num_area.button_height * 3 + 1, QtGui.QColor("blue") )
        for i in range(3):
            for j in range(3):
                painter.fillRect( i * self.num_area.button_width + 1, j * self.num_area.button_height + 1, self.num_area.button_width - 1 , self.num_area.button_height - 1, QtGui.QColor("gray") )
        painter.translate( -self.num_area.x, -self.num_area.y )
    def paintEvent( self, event ):
        print "paint_event"
        painter = QtGui.QPainter(self)
        #painter.setPen( QtGui.QColor("blue") )
        #painter.setRenderHint( QtGui.QPainter.Antialiasing, True )
        #brush = QtGui.QBrush()
        self.draw_num_area( painter )
        painter.drawPath( self.mouse_track )

if __name__ == "__main__":
    app = QtGui.QApplication( sys.argv )

    win = QtGui.QWidget()
    pad = InputPad(win)
    pad.move(0,0)
    pad.resize(800,424)
    pad.request_quit.connect( app.quit )

    #b = QtGui.QPushButton(win)
    #b.resize(144,72)

    win.show()
    #pad.grabMouse()
    sys.exit(app.exec_())
