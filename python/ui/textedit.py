#-!- coding=utf-8 -!-

from PySide import QtCore, QtGui
#from PyQt4 import QtCore, QtGui
#QtCore.Signal = QtCore.pyqtSignal
#QtCore.Slot = QtCore.pyqtSlot

class TextEdit( QtGui.QPlainTextEdit ) :
    clicked = QtCore.Signal( int )
    DEFAULT_LONGPRESS_INTERVAL = 350
    DEFAULT_AUTO_REPEAT_INTERVAL = 65
    def __init__( self, keycode, parent = None ) :
        QtGui.QPlainTextEdit.__init__( self, parent )
        self.setAttribute( QtCore.Qt.WA_InputMethodEnabled, False )
        #self.setCursorWidth( 5 )
        self.keycode = keycode
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect( self.timeout )
        self.longpress_interval = self.DEFAULT_LONGPRESS_INTERVAL
        self.preedit_start_pos = -1
        self.preedit_end_pos = -1
        self.preedit = ""
        self.origin_pos = self.textCursor()
        self.moveDirection = 0

        self.auto_repeat_timer = QtCore.QTimer()
        self.auto_repeat_interval = self.DEFAULT_AUTO_REPEAT_INTERVAL
        self.auto_repeat_timer.timeout.connect( self.auto_repeat )

        self.normal_format = QtGui.QTextCharFormat()
        self.preedit_format = QtGui.QTextCharFormat()
        self.preedit_format.setFontUnderline( True )
        self.check = self.__check
        desktop = QtGui.QDesktopWidget()
        self.screenLenght = min( desktop.width(), desktop.height() )
    def __check( self ) :
        return True
    def __clear_preedit( self ) :
        if not ( self.preedit_start_pos < 0 ) :
            cursor = self.textCursor()
            cursor.setPosition( self.preedit_end_pos )
            while cursor.position() > self.preedit_start_pos :
                cursor.deletePreviousChar()
        self.preedit = ""
        self.preedit_start_pos = -1
        self.preedit_end_pos = -1
    def __insert_preedit( self, text ) :
        cursor = self.textCursor()
        self.preedit = text
        self.preedit_start_pos = cursor.position()
        cursor.insertText( text, self.preedit_format )
        self.preedit_end_pos = cursor.position()
        self.ensureCursorVisible()
    @QtCore.Slot( str )
    def commit_preedit( self, text ) :
        self.__clear_preedit()
        if len( text ) > 0 :
            self.__insert_preedit( text )
    @QtCore.Slot( str )
    def set( self, c ) :
        self.setPlainText( c )
        self.moveCursor( QtGui.QTextCursor.End )
        self.ensureCursorVisible()
    @QtCore.Slot( str )
    def commit( self, c ) :
        self.textCursor().insertText( c, self.normal_format )
        self.ensureCursorVisible()
    @QtCore.Slot( int, int )
    def command( self, dx, dy ) :
        #if abs( dx ) > abs( dy ) :
        self.setTextCursor( self.origin_pos )
        if self.moveDirection == 0 :
            #if abs( dx ) > abs( dy ) :
            #if float( abs( dx ) ) > float( abs( dy ) ) * 1.6 :
            if abs( dx ) > abs( dy ) * 2 :
                self.moveDirection = 1
            else :
                self.moveDirection = -1
        if self.moveDirection == 1 :
            if dx >= 0 :
                self.__move_end()
            else :
                self.__move_start()
        elif self.moveDirection == -1 :
            if dy >= 0 :
                cursor = self.textCursor()
                cursor.movePosition( cursor.End )
                self.setTextCursor( cursor )
            else :
                cursor = self.textCursor()
                cursor.movePosition( cursor.Start )
                self.setTextCursor( cursor )
    @QtCore.Slot( int, int )
    def move( self, dx, dy ) :
        if self.moveDirection == 0 :
            #if float( abs( dx ) ) > float( abs( dy ) ) * 1.6 :
            if abs( dx ) > abs( dy ) * 2 :
                self.moveDirection = 1
            else :
                self.moveDirection = -1
        if self.moveDirection == 1 :
            self.moveH( dx )
        elif self.moveDirection == -1 :
            self.moveV( dy )
    def moveH( self, dx ) :
        d = float( dx ) / float( self.screenLenght )
        d = 8 * d
        new_pos = self.origin_pos.position() + d
        cursor = self.textCursor()
        if new_pos < 0 :
            new_pos = 0
        else :
            cursor.movePosition( QtGui.QTextCursor.End )
            end_pos = cursor.position() 
            if new_pos > end_pos :
                new_pos = end_pos
        cursor.setPosition( new_pos )
        self.setTextCursor( cursor )
        self.ensureCursorVisible()
    def moveV( self, dy ) :
        d = float( dy ) / float( self.screenLenght )
        d = 5 * d
        #print "moveV", d
        cursor = self.textCursor()
        cursor.setPosition( self.origin_pos.position() )
        if d > 0 :
            d = abs( int( round( d ) ) )
            #print "moveV", d
            for i in range( d ) :
                cursor.movePosition( cursor.Down )
        elif d < 0 :
            d = abs( int( round( d ) ) )
            #print "moveV", d
            for i in range( d ) :
                cursor.movePosition( cursor.Up )
        self.setTextCursor( cursor )
        self.ensureCursorVisible()
    def __move_end( self ) :
        pos = self.textCursor()
        end_pos = self.textCursor()
        end_pos.movePosition( QtGui.QTextCursor.EndOfLine )
        if pos == end_pos :
            self.moveCursor( QtGui.QTextCursor.Right )
        self.moveCursor( QtGui.QTextCursor.EndOfLine )
    def __move_start( self ) :
        pos = self.textCursor()
        start_pos = self.textCursor()
        start_pos.movePosition( QtGui.QTextCursor.StartOfLine )
        if pos == start_pos :
            self.moveCursor( QtGui.QTextCursor.Left )
        self.moveCursor( QtGui.QTextCursor.StartOfLine )
    def __delete( self ) :
        cursor = self.textCursor()
        if cursor.atStart() :
            cursor.deleteChar()
        else :
            cursor.deletePreviousChar()
    def mouseMoveEvent( self, event ) :
        pass
    def mouseDoubleClickEvent( self, event ) :
        self.mousePressEvent( event )
    def mousePressEvent( self, event ) :
        #print "text press"
        self.auto_repeat_timer.stop()
        self.origin_pos = self.textCursor()
        self.timer.start( self.longpress_interval )
    def mouseReleaseEvent( self, event ) :
        self.auto_repeat_timer.stop()
        if self.timer.isActive() :
            self.timer.stop()
            if self.check() :
                self.clicked.emit( self.keycode )
            else :
                self.__delete()
            self.ensureCursorVisible()
    @QtCore.Slot()
    def auto_repeat( self ) :
        self.auto_repeat_timer.stop()
        self.auto_repeat_timer.start( self.auto_repeat_interval )
        if self.check() :
            self.clicked.emit( self.keycode )
        else :
            self.__delete()
        self.ensureCursorVisible()
    @QtCore.Slot()
    def timeout( self ) :
        self.timer.stop()
        if self.check() :
            self.clicked.emit( self.keycode )
        else :
            self.__delete()
        self.ensureCursorVisible()
        self.auto_repeat_timer.start( self.auto_repeat_interval )
    def installEventFilter( self, filter ) :
        self.viewport().installEventFilter( filter )
        QtGui.QTextEdit.installEventFilter( self, filter )
    @QtCore.Slot()
    def stop( self ) :
        self.origin_pos = self.textCursor()
        self.moveDirection = 0
        if self.timer.isActive() :
            self.timer.stop()


