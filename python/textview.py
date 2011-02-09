#-!- coding=utf-8 -!-

from PySide import QtGui, QtCore

class Spring( QtCore.QObject ) :
    changed = QtCore.Signal( int )
    def __init__( self ) :
        QtCore.QObject.__init__( self )
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect( self.recover )
        self.value = 0
        self.target = 0
    def setTarget( self, target ) :
        self.target = target
        if self.timer.isActive() :
            pass
        else :
            self.timer.start( 40 )
    def setOffset( self, offset ) :
        if offset != 0 :
            target = self.value + offset
            self.setTarget( target )
    @QtCore.Slot()
    def recover( self ) :
        d = abs( self.target - self.value )
        step = max( pow( d / 2, 0.5 ), 2 )
        self.timer.stop()
        if self.value > self.target :
            self.value = self.value - step
            if self.value <= self.target :
                self.value = self.target
            else :
                self.timer.start( 40 )
        elif self.value < self.target :
            self.value = self.value + step
            if self.value >= self.target :
                self.value = self.target
            else :
                self.timer.start( 40 )
        self.changed.emit( self.value )
        #print self.value, self.target

class TextView( QtGui.QTextEdit ) :
    def __init__( self, parent = None ) :
        QtGui.QTextEdit.__init__( self, parent )
        palette = self.palette()
        palette.setColor( QtGui.QPalette.Base, QtCore.Qt.transparent )
        palette.setColor( QtGui.QPalette.Text, QtCore.Qt.white )
        self.setAttribute( QtCore.Qt.WA_TranslucentBackground, True )
        self.setPalette( palette )
        self.setFrameStyle( QtGui.QFrame.NoFrame)
        #self.setCursorWidth( 0 )
        self.vSpring = Spring()
        self.vSpring.changed.connect( self.vSpringChange )
    def resizeEvent( self, event ) :
        QtGui.QTextEdit.resizeEvent( self, event )
        viewport = self.viewport()
        contentSize = viewport.size()
        contentSize.setHeight( contentSize.height() * 2 )
        viewport.resize( contentSize )
    @QtCore.Slot( int, int )
    def scroll( self, dx, dy ) :
        self.vSpring.setTarget( dy / 2 )
    @QtCore.Slot( int )
    def vSpringChange( self, offset ) :
        self.update()
    @QtCore.Slot( int )
    def vScroll( self, offset ) :
        areaSize = self.size()
        cursorRect = self.cursorRect()
        centerTop = areaSize.height() / 2 - cursorRect.height() / 2
        y = centerTop - cursorRect.y() + offset
        contentPos = self.viewport().pos()
        if y != contentPos.y() :
            self.viewport().move( 0, y )
    def paintEvent( self, event ) :
        self.vScroll( self.vSpring.value )
        painter = QtGui.QPainter()
        painter.begin( self.viewport() )
        painter.fillRect( self.viewport().rect(), QtGui.QColor( 255, 0, 0 ) )
        painter.end()

        QtGui.QTextEdit.paintEvent( self, event )
        
        painter.begin( self.viewport() )
        areaSize = self.size()
        cursorRect = self.cursorRect()
        centerTop = areaSize.height() / 2 - cursorRect.height() / 2
        cursorPos = cursorRect.topLeft()
        cursorPos = self.viewport().mapTo( self, cursorPos )
        cursorPos.setY( centerTop )
        cursorPos = self.viewport().mapFrom( self, cursorPos )
        cursorRect.moveTopLeft( cursorPos )
        cursorRect.setWidth( 2 )
        painter.fillRect( cursorRect, QtGui.QColor( 0, 0, 255 ) )
        painter.end()
    def mousePressEvent( self, event ) :
        pass
    def mouseReleaseEvent( self, event ) :
        pass
    def mouseDoubleClickEvent( self, event ) :
        self.mousePressEvent( event )
    def mouseMoveEvent( self, event ) :
        pass

class ControlPanel( QtGui.QWidget ) :
    move = QtCore.Signal( int, int )
    def __init__( self, parent = None ) :
        QtGui.QWidget.__init__( self, parent )
        self.originPos = QtCore.QPoint()
    def mousePressEvent( self, event ) :
        self.originPos = event.pos()
    def mouseReleaseEvent( self, event ) :
        self.move.emit( 0, 0 )
    def mouseDoubleClickEvent( self, event ) :
        self.mousePressEvent( event )
    def mouseMoveEvent( self, event ) :
        pos = event.pos()
        dx = pos.x() - self.originPos.x()
        dy = pos.y() - self.originPos.y()
        self.move.emit( dx, dy )

if __name__ == "__main__" :
    import sys

    app = QtGui.QApplication( sys.argv )

    win = ControlPanel()
    view = TextView( win )
    win.move.connect( view.scroll )

    win.show()

    sys.exit( app.exec_() )
