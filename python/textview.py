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
        self.check()
    def setValue( self, value ) :
        self.value = value
        self.check()
    def addOffset( self, offset ) :
        self.value = self.value + offset
        self.check()
    def check( self ) :
        if self.target != self.value :
            if self.timer.isActive() :
                pass
            else :
                self.timer.start( 40 )
    @QtCore.Slot()
    def recover( self ) :
        d = abs( self.target - self.value )
        step = max( pow( d, 0.8 ), 2 )
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

class TextDisplay( QtGui.QPlainTextEdit ) :
    cursorHeightChanged = QtCore.Signal( int )
    def __init__( self, parent = None ) :
        QtGui.QPlainTextEdit.__init__( self, parent )
        palette = self.palette()
        palette.setColor( QtGui.QPalette.Base, QtCore.Qt.transparent )
        palette.setColor( QtGui.QPalette.Text, palette.windowText().color() )
        self.setAttribute( QtCore.Qt.WA_TranslucentBackground, True )
        self.setPalette( palette )
        self.setFrameStyle( QtGui.QFrame.NoFrame)
        #self.setCursorWidth( 0 )
        self.cursorPositionChanged.connect( self.checkCursorPosition )
        self.prevCursorRect = self.cursorRect()
    @QtCore.Slot()
    def checkCursorPosition( self ) :
        cursorRect = self.cursorRect()
        dy = cursorRect.y() - self.prevCursorRect.y()
        if dy != 0 :
            self.cursorHeightChanged.emit( dy )
        self.centerCursor()
        cursorRect = self.cursorRect()
        self.prevCursorRect = cursorRect
    def paintEvent( self, event ) :
        painter = QtGui.QPainter( self.viewport() )
        painter.fillRect( self.viewport().rect(), QtGui.QColor( 0, 0, 255 ) )
        QtGui.QPlainTextEdit.paintEvent( self, event )
    def mousePressEvent( self, event ) :
        pass
    def mouseReleaseEvent( self, event ) :
        pass
    def mouseDoubleClickEvent( self, event ) :
        self.mousePressEvent( event )
    def mouseMoveEvent( self, event ) :
        pass

class TextShadow( QtGui.QWidget ) :
    def __init__( self, parent = None ) :
        QtGui.QWidget.__init__( self, parent )
        palette = self.palette()
        palette.setColor( QtGui.QPalette.Base, QtCore.Qt.transparent )
        self.setPalette( palette )
        self.setAttribute( QtCore.Qt.WA_TranslucentBackground, True )
    def paintEvent( self, event ) :
        painter = QtGui.QPainter( self )
        painter.fillRect( self.rect(), QtGui.QColor( 255, 255, 0, 100 ) )

class TextView( QtGui.QWidget ) :
    def __init__( self, parent = None ) :
        QtGui.QWidget.__init__( self, parent )
        self.display = TextDisplay( self )
        self.shadow = TextShadow( self )
        self.spring = Spring()
        self.spring.changed.connect( self.vSpringChange )
        self.display.cursorHeightChanged.connect( self.cursorChange )
    @QtCore.Slot( int )
    def cursorChange( self, dy ) :
        self.spring.addOffset( dy )
    @QtCore.Slot( int )
    def vSpringChange( self, offset ) :
        self.update()
    def resizeEvent( self, event ) :
        QtGui.QWidget.resizeEvent( self, event )
        size = event.size()
        size.setHeight( size.height() * 3 )
        self.display.resize( size )
    @QtCore.Slot( int, int )
    def scrollStop( self, dx, dy ) :
        centerPos = self.rect().bottomLeft()
        centerPos.setY( centerPos.y() / 2 )
        centerPos = self.display.mapFrom( self, centerPos )
        #print centerPos
        cursor = self.display.cursorForPosition( centerPos )
        self.display.setTextCursor( cursor )
        self.spring.setTarget( 0 )
        #centerPos.setHei
        #self.spring.setTarget( dy / 2 )
    @QtCore.Slot( int, int )
    def scroll( self, dx, dy ) :
        self.spring.setTarget( dy / 3 )
    @QtCore.Slot( int )
    def vScroll( self, offset ) :
        areaSize = self.size()
        cursorRect = self.display.cursorRect()
        centerTop = areaSize.height() / 2 - cursorRect.height() / 2
        y = centerTop - cursorRect.y() + offset
        contentPos = self.display.pos()
        if y != contentPos.y() :
            self.display.move( 0, y )
        areaSize.setHeight( cursorRect.height() )
        self.shadow.resize( areaSize )
        self.shadow.move( 0, centerTop )
    def paintEvent( self, event ) :
        self.vScroll( self.spring.value )
        painter = QtGui.QPainter( self )
        painter.fillRect( self.rect(), QtGui.QColor( 255, 0, 0 ) )
        
class ControlPanel( QtGui.QWidget ) :
    stop = QtCore.Signal( int, int )
    move = QtCore.Signal( int, int )
    def __init__( self, parent = None ) :
        QtGui.QWidget.__init__( self, parent )
        self.originPos = QtCore.QPoint()
    def mousePressEvent( self, event ) :
        self.originPos = event.pos()
    def mouseReleaseEvent( self, event ) :
        self.stop.emit( 0, 0 )
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
    view.resize( 300, 300 )
    win.move.connect( view.scroll )
    win.stop.connect( view.scrollStop )

    win.show()
    view.resize( 300, 300 )

    sys.exit( app.exec_() )
