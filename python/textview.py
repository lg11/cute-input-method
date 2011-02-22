#-!- coding=utf-8 -!-

from PySide import QtGui, QtCore

class Bumper( QtCore.QObject ) :
    changed = QtCore.Signal( int )
    DEFAULT_BUMP = 4
    def __init__( self ) :
        QtCore.QObject.__init__( self )
        self.timer = QtCore.QBasicTimer()
        self.value = 0
        self.target = 0
        self.bump = self.DEFAULT_BUMP
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
                self.flag = True
                self.timer.start( 40, self )
    def timerEvent( self, event ) :
        #print "timerEvent"
        d = abs( self.target - self.value )
        step = max( pow( d * self.bump, 0.5 ), 2 )
        if self.value > self.target :
            self.value = self.value - step
            if self.value <= self.target :
                self.value = self.target
                self.timer.stop()
        elif self.value < self.target :
            self.value = self.value + step
            if self.value >= self.target :
                self.value = self.target
                self.timer.stop()
        else :
            self.timer.stop()
        self.changed.emit( self.value )
        #print self.value, self.target

class Leveler :
    DEFAULT_VALVE = 30
    def __init__( self ) :
        self.level = 0
        self.valve = self.DEFAULT_VALVE
        self.offset = 0
        self.bumper = Bumper()
        self.bumper.changed.connect( self.check )
        #self.spring = Spring()
    def setOffset( self, offset ) :
        self.bumper.setTarget( offset )
    def setScale( self, scale ) :
        offset = scale * self.valve
        self.setOffset( offset )
    QtCore.Slot( int )
    def check( self, value ) :
        self.offset = value

        
    #def

Spring = Bumper

class TextDisplay( QtGui.QPlainTextEdit ) :
    cursorHeightChanged = QtCore.Signal( int, int )
    def __init__( self, parent = None ) :
        QtGui.QPlainTextEdit.__init__( self, parent )
        palette = self.palette()
        palette.setColor( QtGui.QPalette.Base, QtCore.Qt.transparent )
        palette.setColor( QtGui.QPalette.Text, palette.windowText().color() )
        self.setAttribute( QtCore.Qt.WA_TranslucentBackground, True )
        self.setPalette( palette )
        self.setFrameStyle( QtGui.QFrame.NoFrame)
        self.setCursorWidth( 0 )
        self.cursorPositionChanged.connect( self.checkCursorPosition )
        self.prevCursorRect = self.cursorRect()
    @QtCore.Slot()
    def checkCursorPosition( self ) :
        cursorRect = self.cursorRect()
        dy = cursorRect.y() - self.prevCursorRect.y()
        dx = cursorRect.x() - self.prevCursorRect.x()
        if dy != 0 or dx != 0 :
            self.cursorHeightChanged.emit( dx, dy )
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
        self.spring = Spring()
        self.cursorX = 0
    def paintEvent( self, event ) :
        painter = QtGui.QPainter( self )
        rect = self.rect()
        painter.fillRect( rect, QtGui.QColor( 255, 255, 0, 100 ) )
        self.cursorX = self.spring.value
        rect.setX( self.cursorX )
        rect.setWidth( 3 )
        painter.fillRect( rect, QtGui.QColor( 0, 255, 0, 100 ) )

class TextView( QtGui.QWidget ) :
    def __init__( self, parent = None ) :
        QtGui.QWidget.__init__( self, parent )
        self.display = TextDisplay( self )
        self.shadow = TextShadow( self )
        self.spring = Spring()
        #self.
        self.spring.changed.connect( self.vSpringChange )
        self.shadow.spring.changed.connect( self.vSpringChange )
        self.display.cursorHeightChanged.connect( self.cursorChange )
    @QtCore.Slot( int )
    def cursorChange( self, dx, dy ) :
        self.spring.addOffset( dy )
        cursorRect = self.display.cursorRect()
        self.shadow.spring.setTarget( cursorRect.x() )
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
        cursorRect = self.display.cursorRect()
        self.shadow.spring.setTarget( cursorRect.x() + dx )
        #print dx, dy, "scroll"
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
        self.moveDirection = 0
    def mousePressEvent( self, event ) :
        self.moveDirection = 0
        self.originPos = event.pos()
    def mouseReleaseEvent( self, event ) :
        self.moveDirection = 0
        self.stop.emit( 0, 0 )
    def mouseDoubleClickEvent( self, event ) :
        self.mousePressEvent( event )
    def mouseMoveEvent( self, event ) :
        pos = event.pos()
        dx = pos.x() - self.originPos.x()
        dy = pos.y() - self.originPos.y()
        if self.moveDirection == 0 : 
            if dx * dx >= dy * dy :
                self.moveDirection = 1
            else :
                self.moveDirection = -1
            #print dx, dy, self.moveDirection
        if self.moveDirection > 0 :
            self.move.emit( dx, 0 )
        else :
            self.move.emit( 0, dy )

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
