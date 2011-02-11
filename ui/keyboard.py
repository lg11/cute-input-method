#-!- coding=utf-8 -!-

from PySide import QtCore, QtGui
#from PyQt4 import QtCore, QtGui
#QtCore.Signal = QtCore.pyqtSignal
#QtCore.Slot = QtCore.pyqtSlot

from widget import Key


class KeyPad( QtGui.QWidget ) :
    #DEFAULT_HEIGHT = 400
    commit = QtCore.Signal( str )
    FONT_SUB = QtGui.QFont()
    FONT_SUB.setPointSize( FONT_SUB.pointSize() + 1 )
    def __init__( self, key_map, parent = None ) :
        QtGui.QWidget.__init__( self, parent, )

        self.sub_palette = self.palette()
        self.sub_palette.setColor( QtGui.QPalette.ButtonText, self.sub_palette.mid().color() )

        self.key_map = key_map
        self.key_list = []

        keycode = 0
        self.key_list.append( [] )
        for ch in self.key_map[0] :
            key_list = self.key_list[-1] 
            if ch == "\n" :
                self.key_list.append( [] )
            elif ch == "\0" :
                key_list.append( None )
            else :
                key = Key( keycode, self )
                key.clicked.connect( self.slot_key_clicked )
                key.longpressed.connect( self.slot_key_longpressed )
                key.setText( self.key_map[0][keycode] )
                key_list.append( key )
                key_layout = QtGui.QVBoxLayout()
                key.setLayout( key_layout )
                label = QtGui.QLabel( self )
                key_layout.addWidget( label )
                label.setAlignment( QtCore.Qt.AlignTop | QtCore.Qt.AlignRight )
                label.setPalette( self.sub_palette )
                label.setFont( self.FONT_SUB )
                label.setText( self.key_map[1][keycode] )
            keycode = keycode + 1
        self.__remap_key()
    def __remap_key( self ) :
        width = self.width()
        height = self.height()
        base_key_count = len( self.key_list[0] )
        key_width = width / base_key_count
        key_height = height / len( self.key_list )
        if key_height > key_width * 1.6 :
            key_height = int( key_width * 1.6 )


        y = 0
        for key_list in self.key_list :
            x = 0
            for key in key_list :
                if key :
                    key.resize( key_width, key_height )
                    key.move( x, y )
                x = x + key_width
            y = y + key_height
    def resizeEvent( self, event ) :
        self.__remap_key()
    def slot_key_clicked( self, keycode ) :
        self.commit.emit( self.key_map[0][keycode] )
    def slot_key_longpressed( self, keycode ) :
        self.commit.emit( self.key_map[1][keycode] )
    def mousePressEvent( self, event ) :
        pass
    def mouseReleaseEvent( self, event ) :
        pass
    def mouseMoveEvent( self, event ) :
        pass
    def mouseDoubleClickEvent( self, event ) :
        pass
    def installEventFilter( self, filter ) :
        for key_list in self.key_list :
            for key in key_list :
                if key :
                    key.installEventFilter( filter )
        QtGui.QWidget.installEventFilter( self, filter )
    @QtCore.Slot()
    def stop( self ) :
        for key_list in self.key_list :
            for key in key_list :
                if key :
                    key.stop()

KEYPAD_MAP = []
KEYPAD_MAP_NAME = [ "abc", "あ".decode( "utf-8" ), "ア".decode( "utf-8" ), "dic" ]

KEYPAD_MAP.append( [ \
        "1234567890\nqwertyuiop\nasdfghjkl\0\n\0zxcvbnm\0\0" , \
        "*#+-/=,.@ \nQWERTYUIOP\nASDFGHJKL\0\n\0ZXCVBNM\0\0" \
        ] )

KEYPAD_MAP.append( [ \
        "あいうえおまみむめも\nかきくけこはひふへほ\nさしすせそたちつてと\nなにぬねのらりるれろ\nやゆよ\0っをんわ\0ゐ".decode( "utf-8" ) \
        , \
        "ぁぃぅぇぉぱぴぷぺぽ\nがぎぐげごばびぶべぼ\nざじずぜぞだぢづでど\n          \nゃゅょ\0   ゎ\0ゑ".decode( "utf-8" ) \
        ] )

KEYPAD_MAP.append( [ \
        "アイウエオマミムメモ\nカキクケコハヒフヘホ\nサシスセソタチツテト\nナニヌネノラリルレロ\nヤユヨ\0ッヲンワヴヱ".decode( "utf-8" ) \
        , \
        "ァィゥェォパピプペポ\nガギグゲゴバビブベボ\nザジズゼゾダヂヅデド\nヵ         \nャュョ\0   ヮ ヰ".decode( "utf-8" ) \
        ] )

#KEYPAD_MAP.append( [ \
        #[ "orz", "-_-!", ":]", ":[", "OJL", "\n", "-o-", "\n", "\n", "\n", "\n" ] \
        #, \
        #[ "", "", "", "", "", "", "", "", "", "", "", "" ] \
        #] )

"""
あいうえお まみむめも
かきくけこ はひふへほ
さしすせそ たちつてと
なにぬねの らりるれろ
やゆよ  っ をんわ  ゐ

ぁぃぅぇぉ ぱぴぷぺぽ
がぎぐげご ばびぶべぼ
ざじずぜぞ だぢづでど 
                 
ゃゅょ         ゎ  ゑ
"""
"""
アイウエオ マミムメモ
カキクケコ ハヒフヘホ
サシスセソ タチツテト
ナニヌネノ ラリルレロ
ヤユヨ  ッ ヲンワヴヱ

ァィゥェォ パピプペポ
ガギグゲゴ バビブベボ
ザジズゼゾ ダヂヅデド
ヵ
ャュョ         ヮ  ヰ
"""

class Keyboard( QtGui.QWidget ) :
    commit = QtCore.Signal( str )
    def __init__( self, parent = None ) :
        QtGui.QWidget.__init__( self, parent )
        self.setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, True )
        
        self.pad_stack = QtGui.QStackedWidget( self )

        self.pad = []

        #pad = KeyPad( KEYPAD_MAP["japanese"], self )
        pad = KeyPad( KEYPAD_MAP[0], self )
        pad.commit.connect( self.commit )
        self.pad_stack.addWidget( pad )
        self.pad.append( pad )

    def resizeEvent( self, event ) :
        height = self.height()
        width = self.width()

        self.pad_stack.move( 0, 0 )
        self.pad_stack.resize( width, height )


if __name__ == "__main__" :
    import sys
    def p( s ) :
        print s.toUtf8()
    app = QtGui.QApplication( sys.argv )

    kb = Keyboard()
    kb.commit.connect( p )
    kb.show()
    sys.exit( app.exec_() )


