#-!- coding=utf-8 -!-

from PySide import QtCore, QtGui
#from PyQt4 import QtCore, QtGui
#QtCore.Signal = QtCore.pyqtSignal
#QtCore.Slot = QtCore.pyqtSlot

#import time

#import rotate
from textedit import TextEdit
from numpad import NumPad
from keyboard import KeyPad, KEYPAD_MAP, KEYPAD_MAP_NAME
#from port import Backend
from control import Control
from post import PostPad

class Rotater( QtGui.QWidget ) :
    def __init__( self, parent = None ) :
        QtGui.QWidget.__init__( self, parent, QtCore.Qt.Dialog | QtCore.Qt.FramelessWindowHint )
        self.setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, False )
        self.setFixedHeight( 1 )
    def resizeEvent( self, event ) :
        if event.size().width() >= 800 :
            self.hide()
    def closeEvent( self, event ) :
        self.hide()
        event.ignore()


class InputPad( Control ) :
    request_commit = QtCore.Signal( str )
    NUMPAD_HEIGHT = 440
    PAD_HEIGHT = 700
    TEXTEDIT_HEIGHT = 140
    LAYOUT_SPACING = 0
    def __init__( self, daemon_flag = False, parent = None ) :
        if daemon_flag :
            Control.__init__( self, parent, QtCore.Qt.Dialog | QtCore.Qt.FramelessWindowHint )
        else :
            Control.__init__( self, parent )

        self.setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, True )

        self.sub_palette = self.palette()
        self.sub_palette.setColor( QtGui.QPalette.ButtonText, self.sub_palette.mid().color() )
        self.text_palette = self.palette()
        self.text_palette.setColor( QtGui.QPalette.Text, self.sub_palette.windowText().color() )
        #self.text_palette.setColor( QtGui.QPalette.Base, self.sub_palette.window().color() )

        self.rotater = Rotater()

        self.layout = QtGui.QVBoxLayout()
        self.layout.setSpacing( 0 )
        self.layout.setContentsMargins( 0, 0, 0, 0 )
        self.setLayout( self.layout )

        self.textedit = TextEdit( NumPad.KEYCODE_BACKSPACE, self )
        #self.textedit.setStyleSheet( "QTextEdit { border-width : 0px ; padding : 0px }" )
        #self.textedit.setPalette( self.text_palette )
        self.textedit.setFixedHeight( self.TEXTEDIT_HEIGHT )
        self.textedit.setAttribute( QtCore.Qt.WA_TranslucentBackground, True )
        #self.take.connect( self.textedit.stop )
        #self.layout.addWidget( self.textedit )
        layout = QtGui.QGridLayout()
        layout.setContentsMargins( 8, 0, 8, 0 )
        layout.addWidget( self.textedit, 0, 0 )
        self.layout.addLayout( layout )
        
        self.stack = QtGui.QStackedLayout()
        self.layout.addLayout( self.stack )
        self.keypad_list = []
        
        keypad = NumPad( self )
        keypad.setFixedHeight( self.NUMPAD_HEIGHT )
        self.keypad_list.append( keypad )
        keypad.commit.connect( self.textedit.commit )
        keypad.commit_preedit.connect( self.textedit.commit_preedit )
        self.textedit.clicked.connect( keypad.slot_key_click )
        for key in keypad.key_list :
            key.setFocusProxy( self.textedit )
            #self.take.connect( key.stop )
        #self.stack.addWidget( keypad )
        widget = QtGui.QWidget( self )
        layout = QtGui.QVBoxLayout()
        layout.setContentsMargins( 8, 0, 8, 0 )
        layout.addWidget( keypad )
        layout.addStretch()
        widget.setLayout( layout )
        self.stack.addWidget( widget )

        #self.layout.addStretch()
        self.tab = QtGui.QTabBar( self )
        self.tab.addTab( "中".decode( "utf-8" ) )
        self.layout.addWidget( self.tab )

        for i in range( len( KEYPAD_MAP ) ) :
            keypad = KeyPad( KEYPAD_MAP[i] )
            keypad.commit.connect( self.textedit.commit )
            for row in keypad.key_list :
                for key in row :
                    if key :
                        key.setFocusProxy( self.textedit )
                        #self.take.connect( key.stop )
            self.keypad_list.append( keypad )
            self.stack.addWidget( keypad )
            self.tab.addTab( KEYPAD_MAP_NAME[i] )

        post = PostPad( self )
        post.setFocusProxy( self.textedit )
        post.commit.connect( self.textedit.commit )
        post.commit.connect( self.q_commit )
        post.set.connect( self.textedit.set )
        post.set.connect( self.q_commit )
        self.request_commit.connect( post.add )
        self.keypad_list.append( post )
        self.stack.addWidget( post )
        self.tab.addTab( "Q" )
        self.q = post

        self.tab.currentChanged.connect( self.change )
        self.prev_tab = 0

        self.textedit.installEventFilter( self )
        for keypad in self.keypad_list :
            keypad.installEventFilter( self )

        self.move.connect( self.slot_move )
        self.command.connect( self.slot_command )
        self.take.connect( self.stop )
        self.textedit.check = self.check_mode
        self.check = self.check_move

        self.daemon_flag = daemon_flag
        if self.daemon_flag :
            self.desktop = QtGui.QApplication.desktop()
            rect = self.desktop.screenGeometry()
            if rect.height() < rect.width() :
                self.portrait = False
            else :
                self.portrait = True
    @QtCore.Slot( int )
    def change( self, index ) :
        if index < len( self.keypad_list ) - 1 :
            self.prev_tab = index
            self.textedit.show()
            self.stack.setCurrentIndex( self.prev_tab )
            self.textedit.setFocus()
        else :
            self.textedit.hide()
            self.stack.setCurrentIndex( index )
    @QtCore.Slot( str )
    def q_commit( self, text ) :
        self.textedit.show()
        self.stack.setCurrentIndex( self.prev_tab )
        self.tab.setCurrentIndex( self.prev_tab )
        self.textedit.setFocus()
    @QtCore.Slot()
    def stop( self ) :
        if self.tab.currentIndex() < len( self.keypad_list ) - 1 :
            index = self.tab.currentIndex()
            self.keypad_list[index].stop()
            self.textedit.stop()
    @QtCore.Slot( int, int )
    def slot_command( self, dx, dy ) :
        if self.tab.currentIndex() < len( self.keypad_list ) - 1 :
            self.textedit.command( dx, dy )
    @QtCore.Slot( int, int )
    def slot_move( self, dx, dy ) :
        if self.tab.currentIndex() < len( self.keypad_list ) - 1 :
            self.textedit.move( dx, dy )
    def check_mode( self ) :
        flag = False
        if len( self.textedit.preedit ) > 0 :
            flag = True
        elif not ( self.keypad_list[0].mode == NumPad.MODE_NORMAL ) and not ( self.keypad_list[0].mode == NumPad.MODE_ROLLER ) :
            flag = True
        return flag
    def check_move( self ) :
        flag = True
        if len( self.textedit.preedit ) > 0 :
            flag = False
        elif not ( self.keypad_list[0].mode == NumPad.MODE_NORMAL ) and not ( self.keypad_list[0].mode == NumPad.MODE_ROLLER ) :
            flag = False
        return flag
    def callback_show( self, string ) :
        self.textedit.setText( string )
        self.textedit.moveCursor( QtGui.QTextCursor.End )
        self.textedit.ensureCursorVisible()
        rect = self.desktop.screenGeometry()
        if rect.height() < rect.width() :
            self.portrait = False
        else :
            self.portrait = True
        clip = QtGui.QApplication.clipboard()
        text = clip.text( clip.Clipboard )
        self.q.add( text )
        text = clip.text( clip.Selection )
        self.q.add( text )
        self.show()
    def resizeEvent( self, event ) :
        #print self.width(), self.height(), self.isVisible()
        if self.height() < self.PAD_HEIGHT :
            self.resize( 480, self.PAD_HEIGHT )
    def closeEvent( self, event ) :
        if self.daemon_flag :
            self.hide()
            event.ignore()
            if not self.portrait :
                self.rotater.resize( 1, 1 )
                self.rotater.show()
            self.textedit.commit_preedit( "" )
            self.keypad_list[0].set_mode( self.keypad_list[0].MODE_NORMAL )
            self.keypad_list[0].backend.set_code( "" )
            text = self.textedit.toPlainText()
            self.request_commit.emit( text )
        else :
            event.accept()
        #self.backend.backend.save()

if __name__ == "__main__" :
    import sys
    app = QtGui.QApplication( sys.argv )

    pad = InputPad()
    pad.show()
    sys.exit( app.exec_() )


