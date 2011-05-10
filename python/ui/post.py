#-!- coding=utf-8 -!-

from PySide import QtCore, QtGui
#from PyQt4 import QtCore, QtGui
#QtCore.Signal = QtCore.pyqtSignal
#QtCore.Slot = QtCore.pyqtSlot

#from widget import Key

class Post( QtGui.QPushButton ) :
    HEIGHT = 55
    longpressed = QtCore.Signal( int )
    clicked = QtCore.Signal( int )
    sticked = QtCore.Signal( int )
    unsticked = QtCore.Signal( int )
    DEFAULT_LONGPRESS_INTERVAL = 350
    def __init__( self, id, parent = None ) :
        QtGui.QPushButton.__init__( self, parent )

        self.PALETTE = self.palette()
        color = self.PALETTE.text().color()
        color.setAlpha( 125 )
        self.PALETTE.setColor( QtGui.QPalette.ButtonText, color )
        
        self.label = QtGui.QLabel( self )
        self.stick = QtGui.QLabel( self )

        layout = QtGui.QHBoxLayout()
        layout.setSpacing( 3 )
        layout.setContentsMargins( 8, 0, 15, 0 )
        layout.addWidget( self.stick )
        layout.addWidget( self.label )
        layout.addStretch()
        self.setLayout( layout )

        self.stick.setText( u"◇" )
        self.stick.setPalette( self.PALETTE )

        self.start_pos = QtCore.QPoint( 0, 0 )
        self.flag = False
        self.id = id
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect( self.timeout )
        self.longpress_interval = self.DEFAULT_LONGPRESS_INTERVAL
        self.setText = self.label.setText
    def mousePressEvent( self, event ) :
        self.setDown( True )
        self.timer.start( self.longpress_interval )
        self.start_pos = event.pos()
    def set( self, flag ) :
        if flag :
            self.stick.setText( u"◆" )
            self.flag = True
            self.sticked.emit( self.id )
        else :
            self.stick.setText( u"◇" )
            self.flag = False
            self.unsticked.emit( self.id )
    def mouseReleaseEvent( self, event ) :
        if self.timer.isActive() :
            self.setDown( False )
            self.timer.stop()
            pos = event.pos()
            if pos.x() < self.HEIGHT * 1.5 or self.start_pos.x() < self.HEIGHT * 1.5 :
                self.set( not self.flag )
            else :
                self.clicked.emit( self.id )
    @QtCore.Slot()
    def timeout( self ) :
        self.timer.stop()
        self.setDown( False )
        self.longpressed.emit( self.id )
    @QtCore.Slot()
    def stop( self ) :
        self.timer.stop()
        self.setDown( False )

class PostPad( QtGui.QWidget ) :
    set = QtCore.Signal( str )
    commit = QtCore.Signal( str )
    MAX = 16
    def __init__( self, parent = None ) :
        QtGui.QWidget.__init__( self, parent )
        self.record = []
        self.post_list = []
        for i in range( self.MAX ) :
            post = Post( i , self ) 
            post.sticked.connect( self.stick )
            post.unsticked.connect( self.unstick )
            post.clicked.connect( self.__commit )
            post.longpressed.connect( self.__set )
            post.hide()
            self.post_list.append( post )
    def __access_record( self ) :
        #把sticked的记录上移一位
        index = 0
        while index < len( self.record ) :
            if self.record[index][1] :
                prev_index = index - 1
                tail_index = index + 1
                while tail_index < len( self.record ) :
                    if self.record[tail_index][1] :
                        tail_index = tail_index + 1
                    else :
                        break
                if prev_index > 0 :
                    record = self.record.pop( prev_index )
                    self.record.insert( tail_index - 1, record )
                index = tail_index
            index = index + 1
    @QtCore.Slot( int )
    def stick( self, id ) :
        self.record[id][1] = True
        #print self.record
    @QtCore.Slot( int )
    def unstick( self, id ) :
        self.record[id][1] = False
        #print self.record
    def __add( self, text ) :
        if len( self.record ) < self.MAX :
            pass
        else :
            index = len( self.record ) - 1
            while index >= 0 :
                if self.record[index][1] :
                    index = index - 1
                else :
                    break
            if index >= 0 :
                self.record.pop( index )
        if len( self.record ) < self.MAX :
            self.record.insert( 0, [ text, False ] )
            self.__access_record()
    @QtCore.Slot( str )
    def add( self, text ) :
        if len( text ) > 0 :
            if not self.check( text ) :
                self.__add( text )
                self.__remap()
    def setFocusProxy( self, proxy ) :
        for post in self.post_list :
            post.setFocusProxy( proxy )
        QtGui.QWidget.setFocusProxy( self, proxy )
    def __remap( self ) :
        width = self.width()
        index  = 0
        while index < self.MAX :
            post = self.post_list[index]
            if index < len( self.record ) :
                post.show()
                post.setText( self.record[index][0] )
                post.resize( width, post.HEIGHT )
                post.move( 0, index * post.HEIGHT )
            else :
                post.hide()
            index = index + 1
    def resizeEvent( self, event ) :
        self.__remap()
    def check( self, text ) :
        flag = False
        for post in self.record :
            if post[0] == text :
                flag = True
                break
        return flag
    @QtCore.Slot()
    def stop( self ) :
        for post in self.post_list :
            post.stop()
    @QtCore.Slot( int )
    def __commit( self, id ) :
        text = self.record[id][0]
        self.commit.emit( text )
    @QtCore.Slot( int )
    def __set( self, id ) :
        text = self.record[id][0]
        self.set.emit( text )


if __name__ == "__main__" :
    import sys
    app = QtGui.QApplication( sys.argv )

    pad = PostPad()

    cb = app.clipboard()
    text = cb.text( cb.Clipboard )
    pad.add( text )
    text = cb.text( cb.Selection )
    pad.add( text )
    pad.add( "1" )
    pad.add( "2" )
    post = pad.post_list[1]
    post.set( True )
    pad.add( "3" )
    pad.add( "4" )
    post = pad.post_list[3]
    post.set( True )
    pad.add( "5" )
    pad.add( "6" )
    pad.add( "7" )
    pad.add( "8" )
    pad.add( "9" )
    pad.add( "10" )
    pad.add( "11" )
    pad.add( "12" )
    pad.add( "13" )
    pad.add( "14" )
    pad.add( "15" )
    pad.add( "16" )
    pad.add( "17" )
    pad.add( "18" )

    pad.show()
    sys.exit( app.exec_() )
