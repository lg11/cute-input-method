#-!- coding=utf-8 -!-

from PySide import QtCore, QtGui
#from PyQt4 import QtCore, QtGui
#QtCore.Signal = QtCore.pyqtSignal
#QtCore.Slot = QtCore.pyqtSlot

#import time

#import rotate
from widget import Key
from port import Backend

class CharRoller( QtCore.QObject ) :
    ROLLER = [ "abcABC", "defDEF", "ghiGHI", "jklJKL", "mnoMNO", "pqrsPQRS" ,"tuvTUV", "wxyzWXYZ" ]
    timeout_interval = 900
    commit = QtCore.Signal( str )
    commit_preedit = QtCore.Signal( str )
    #timeout = QtCore.Signal()
    def __init__( self ) :
        QtCore.QObject.__init__( self )
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect( self.slot_timeout )
        self.roller = -1
        self.code = -1
    @QtCore.Slot()
    def slot_timeout( self ) :
        self.timer.stop()
        c = self.ROLLER[self.code][self.roller]
        self.code = -1
        self.roller = -1
        self.commit.emit( c )
        self.commit_preedit.emit( "" )
        #self.timeout.emit()
    def cancel( self ) :
        self.timer.stop()
        self.code = -1
        self.roller = -1
        self.commit_preedit.emit( "" )
    def stop( self ) :
        if self.code >= 0 :
            c = self.ROLLER[self.code][self.roller]
            self.code = -1
            self.roller = -1
            self.commit.emit( c )
        self.cancel()
    def roll( self, code ) :
        self.timer.stop()
        if code == self.code :
            if self.roller < len( self.ROLLER[code] ) - 1 :
                self.roller = self.roller + 1
            else :
                self.roller = 0
            self.commit_preedit.emit( self.ROLLER[self.code][self.roller] )
            self.timer.start( self.timeout_interval )
        else :
            if self.code >= 0 :
                self.commit.emit( self.ROLLER[self.code][self.roller] )
            self.code = code
            self.roller = 0
            self.commit_preedit.emit( self.ROLLER[self.code][self.roller] )
            self.timer.start( self.timeout_interval )
    def get( self ) :
        c = ""
        if self.code >= 0 :
            c = self.ROLLER[self.code][self.roller]
        return c

class NumPad( QtGui.QWidget ) :
    commit = QtCore.Signal( str )
    commit_preedit = QtCore.Signal( str )
    KEY_TEXT = [ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "", "" ]
    KEY_SUB = [ "undefined", "sym", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz", "mode", "undefined" ]
    PUNC_MAP = [ \
            [ " ", "\n", u"，", u"。", u"？", u"……", u"～", u"！", ] \
            , \
            [ u"、", u"；", u"：", u"“", u"”", u"——", u"（", u"）", ] \
            , \
            [ "@", "&", "_", u"《", u"》", u"%", u"‘", u"’", ] \
            , \
            [ "*", "#", "\\", "+", "-", "=", "*", "/", ] \
            , \
            ]
    MODE_NORMAL = 0
    MODE_SELECT = 1
    MODE_FILTER = 2
    MODE_PUNC = 3
    MODE_ROLLER = 4

    FONT_NORMAL = QtGui.QFont()
    FONT_UNDERLINE = QtGui.QFont()
    FONT_UNDERLINE.setUnderline( True )
    FONT_SUB = QtGui.QFont()
    FONT_SUB.setPointSize( FONT_SUB.pointSize() + 2 )
    FONT_LAGER = QtGui.QFont()
    FONT_LAGER.setPointSize( FONT_LAGER.pointSize() + 17 )
    FONT_LAGER.setBold( True )
    KEYCODE_BACKSPACE = 21
    KEYCODE_MODE = 10
    KEYCODE_NAVIGATE = 11
    def __init__( self, parent = None ) :
        QtGui.QWidget.__init__( self, parent )

        self.sub_palette = self.palette()
        self.sub_palette.setColor( QtGui.QPalette.ButtonText, self.sub_palette.mid().color() )

        self.key_list = []
        self.key_label_list = []
        for keycode in range( 12 ) :
            key = Key( keycode, self )
            #key.setText( self.KEY_TEXT[keycode][0] )
            self.key_list.append( key )
            key.clicked.connect( self.slot_key_click )
            key.longpressed.connect( self.slot_key_longpress )

            key_layout = QtGui.QGridLayout()
            key_layout.setSpacing( 0 )
            key_layout.setContentsMargins( 0, 0, 0, 0 )
            key.setLayout( key_layout )

            label = QtGui.QLabel()
            label.setAlignment( QtCore.Qt.AlignCenter )
            label.setMargin( 0 )
            key_layout.addWidget( label, 0, 0, 2, 1 )
            label.setFont( self.FONT_LAGER )
            label.setText( self.KEY_TEXT[keycode] )
            self.key_label_list.append( label )
            
            label = QtGui.QLabel()
            label.setAlignment( QtCore.Qt.AlignHCenter | QtCore.Qt.AlignTop )
            label.setMargin( 0 )
            key_layout.addWidget( label, 2, 0, 1, 1 )
            label.setFont( self.FONT_SUB )
            label.setPalette( self.sub_palette )
            label.setText( self.KEY_SUB[keycode] )


        self.backend = Backend()
        self.mode = self.MODE_NORMAL
        self.pinyin_list = []
        self.pinyin_index = 0
        self.punc_index = 0
        self.update_stamp = []
        self.roller = CharRoller()
        self.roller.commit.connect( self.commit )
        self.roller.commit_preedit.connect( self.commit_preedit )
        for i in range( 12 ) :
            self.update_stamp.append( False )
        self.__remap()
    def __remap( self ) :
        key_width = self.width() / 3
        key_height = self.height() / 4

        y = 0
        for i in range( 3 ) :
            x = 0
            for j in range( 3 ) :
                index = i * 3 + j + 1
                key = self.key_list[index]
                key.resize( key_width, key_height )
                key.move( x, y )
                x = x + key_width
            y = y + key_height
        
        x = 0
        key = self.key_list[10]
        key.resize( key_width, key_height )
        key.move( x, y )

        x = x + key_width
        key = self.key_list[0]
        key.resize( key_width, key_height )
        key.move( x, y )

        x = x + key_width
        key = self.key_list[11]
        key.resize( key_width, key_height )
        key.move( x, y )
    def resizeEvent( self, event ) :
        self.__remap()
    def context_update( self ) :
        for i in range( 12 ) :
            self.key_label_list[i].setFont( self.FONT_LAGER )
            self.update_stamp[i] = False
        if self.mode == self.MODE_NORMAL :
            index = 1
            for item in self.backend.cand_list :
                self.key_label_list[index].setFont( self.FONT_NORMAL )
                self.key_label_list[index].setText( item[2] )
                #print item
                self.update_stamp[index] = True
                index = index + 1
            text = self.backend.get_selected() + self.backend.code()
            self.commit_preedit.emit( text )
        elif self.mode == self.MODE_SELECT :
            index = 1
            for item in self.backend.cand_list :
                self.key_label_list[index].setFont( self.FONT_UNDERLINE )
                self.key_label_list[index].setText( item[2] )
                self.update_stamp[index] = True
                index = index + 1
            text = self.backend.get_selected() + self.backend.code()
            self.commit_preedit.emit( text )
        elif self.mode == self.MODE_FILTER :
            index = 1
            pinyin_index = self.pinyin_index
            while pinyin_index < len( self.pinyin_list ) and index < 7 :
                self.key_label_list[index].setFont( self.FONT_NORMAL )
                self.key_label_list[index].setText( self.pinyin_list[pinyin_index] )
                self.update_stamp[index] = True
                index = index + 1
                pinyin_index = pinyin_index + 1
        elif self.mode == self.MODE_PUNC :
            index = 2
            punc_list = self.PUNC_MAP[self.punc_index]
            for punc in punc_list :
                self.key_label_list[index].setText( punc )
                self.update_stamp[index] = True
                index = index + 1
        elif self.mode == self.MODE_ROLLER :
            pass
        for i in range( 12 ) :
            if not self.update_stamp[i] :
                self.key_label_list[i].setText( self.KEY_TEXT[i] )
    def __reset_mode_setting( self ) :
        self.key_list[self.KEYCODE_NAVIGATE].setDown( False )
        self.key_list[self.KEYCODE_MODE].setDown( False )
    def set_mode( self, mode ) :
        self.__reset_mode_setting()
        self.mode = mode

        if mode == self.MODE_NORMAL :
            pass
        elif mode == self.MODE_SELECT :
            pass
        elif mode == self.MODE_FILTER :
            pass
        elif mode == self.MODE_PUNC :
            self.punc_index = 0
        elif mode == self.MODE_ROLLER :
            self.key_list[self.KEYCODE_MODE].setDown( True )
    @QtCore.Slot( int )
    def slot_key_click( self, code ) :
        if self.mode == self.MODE_NORMAL :
            if code >= 2 and code <= 9 :
                self.backend.append( str( code ) )
                self.backend.gen_cand_list()
                self.context_update()
            elif code == self.KEYCODE_BACKSPACE :
                if len( self.backend.code() ) > 0 :
                    c = self.backend.pop()
                    self.backend.gen_cand_list()
                    self.context_update()
            elif code == 1 :
                if len( self.backend.code() ) > 0 :
                    self.set_mode( self.MODE_SELECT )
                    self.context_update()
                else :
                    self.set_mode( self.MODE_PUNC )
                    self.context_update()
            elif code == self.KEYCODE_MODE :
                if len( self.backend.code() ) > 0 :
                    pass
                else :
                    self.set_mode( self.MODE_ROLLER )
        elif self.mode == self.MODE_SELECT :
            if code >= 1 and code <= 6 :
                self.backend.select( code - 1 )
                self.backend.gen_cand_list()
                if len( self.backend.code() ) <= 0 :
                    text = self.backend.get_selected()
                    self.backend.commit()
                    self.commit.emit( text )
                    self.set_mode( self.MODE_NORMAL )
                self.context_update()
            elif code == self.KEYCODE_BACKSPACE :
                c = self.backend.deselect()
                self.backend.gen_cand_list()
                if c == "" :
                    self.set_mode( self.MODE_NORMAL )
                self.context_update()
            elif code == 8 :
                self.pinyin_list = self.backend.get_pinyin_list()
                self.pinyin_list.reverse()
                self.pinyin_index = 0
                self.set_mode( self.MODE_FILTER )
                self.context_update()
            elif code == 7 :
                self.backend.page_prev()
                self.backend.gen_cand_list()
                self.context_update()
            elif code == 9 :
                self.backend.page_next()
                self.backend.gen_cand_list()
                self.context_update()
        elif self.mode == self.MODE_FILTER :
            if code >= 1 and code <= 6 :
                pinyin_index = self.pinyin_index + code - 1
                if pinyin_index < ( self.pinyin_list ) :
                    self.backend.set_filter( self.pinyin_list[pinyin_index] )
                    self.backend.gen_cand_list()
                    self.set_mode( self.MODE_SELECT )
                    self.context_update()
            elif code == 8 :
                self.backend.set_filter( "" )
                self.backend.gen_cand_list()
                self.set_mode( self.MODE_SELECT )
                self.context_update()
            elif code == 7 :
                if self.pinyin_index > 0 :
                    self.pinyin_index = self.pinyin_index - 6
                self.context_update()
            elif code == 9 :
                if ( self.pinyin_index + 6 ) < len( self.pinyin_list ) :
                    self.pinyin_index = self.pinyin_index + 6
                self.context_update()
        elif self.mode == self.MODE_PUNC :
            if code >= 2 and code <= 9 :
                index = code - 2
                punc_list = self.PUNC_MAP[self.punc_index]
                self.commit.emit( punc_list[index] )
                self.set_mode( self.MODE_NORMAL )
                self.context_update()
            elif code == self.KEYCODE_BACKSPACE :
                self.set_mode( self.MODE_NORMAL )
                self.context_update()
            elif code == 1 :
                self.punc_index = self.punc_index + 1
                if self.punc_index < len( self.PUNC_MAP ) :
                    pass
                else :
                    self.set_mode( self.MODE_NORMAL )
                    self.punc_index = 0
                self.context_update()
        elif self.mode == self.MODE_ROLLER :
            if code >= 2 and code <= 9 :
                self.roller.roll( code - 2 )
                #self.context_update()
            elif code == self.KEYCODE_BACKSPACE :
                if self.roller.code > 0 :
                    self.roller.cancel()
                #self.context_update()
            elif code == 0 :
                if self.roller.code > 0 :
                    self.roller.stop()
            elif code == self.KEYCODE_MODE :
                if self.roller.code > 0 :
                    self.roller.stop()
                self.set_mode( self.MODE_NORMAL )
                #self.context_update()
    @QtCore.Slot( int )
    def slot_key_longpress( self, code ) :
        if self.mode == self.MODE_NORMAL :
            if code >= 0 and code <= 9 :
                if len( self.backend.code() ) > 0 :
                    pass
                else :
                    self.commit.emit( str( code ) )
        elif self.mode == self.MODE_ROLLER :
            if code >= 0 and code <= 9 :
                if self.roller.code > 0 :
                    self.roller.stop()
                self.commit.emit( str( code ) )
    def mousePressEvent( self, event ) :
        pass
    def mouseReleaseEvent( self, event ) :
        pass
    def mouseDoubleClickEvent( self, event ) :
        pass
    def mouseMoveEvent( self, event ) :
        pass
    def installEventFilter( self, filter ) :
        for key in self.key_list :
            key.installEventFilter( filter )
        QtGui.QWidget.installEventFilter( self, filter )
    @QtCore.Slot()
    def stop( self ) :
        for key in self.key_list :
            key.stop()
        if self.mode == self.MODE_ROLLER :
            self.key_list[self.KEYCODE_MODE].setDown( True )

if __name__ == "__main__" :
    import sys
    def p( text ) :
        print text.toUtf8()
    app = QtGui.QApplication( sys.argv )

    pad = NumPad()
    pad.commit.connect( p )
    pad.commit_preedit.connect( p )
    pad.show()
    sys.exit( app.exec_() )


