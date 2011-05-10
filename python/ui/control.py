#-!- coding=utf-8 -!-

from PySide import QtCore, QtGui
#from PyQt4 import QtCore, QtGui
#QtCore.Signal = QtCore.pyqtSignal
#QtCore.Slot = QtCore.pyqtSlot

class Control( QtGui.QWidget ) :
    take = QtCore.Signal()
    move = QtCore.Signal( int, int )
    command = QtCore.Signal( int, int )
    def __init__( self, parent = None, flags = QtCore.Qt.WindowFlags() ) :
        QtGui.QWidget.__init__( self, parent, flags )
        self.flag = False
        self.check = self.__check
        self.origin = QtCore.QPoint( 0, 0 )
        self.start = QtCore.QPoint( 0, 0 )
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect( self.timeout )
        self.check_timer = QtCore.QTimer()
        self.check_timer.timeout.connect( self.check_timeout )
        self.command_timer = QtCore.QTimer()
        self.command_timer.timeout.connect( self.command_timeout )
        self.time = QtCore.QTime()
        self.time.start()
        self.track = []
    def eventFilter( self, target, event ) :
        if event.type() == QtCore.QEvent.MouseButtonPress :
            self.mousePressEvent( event )
        elif event.type() == QtCore.QEvent.MouseButtonDblClick :
            self.mousePressEvent( event )
        elif event.type() == QtCore.QEvent.MouseButtonRelease :
            self.mouseReleaseEvent( event )
        elif event.type() == QtCore.QEvent.MouseMove :
            self.mouseMoveEvent( event )
        return QtGui.QWidget.eventFilter( self, target, event )
    def mousePressEvent( self, event ) :
        #print "press"
        self.flag = False
        self.origin = event.globalPos()
        self.timer.start( 320 )
        self.check_timer.start( 120 )
        self.command_timer.start( 250 )
        self.time.restart()
        self.track = []
        #self.track.append( ( event.pos(), self.time.elapsed() ) )
    def mouseReleaseEvent( self, event ) :
        #print "release"
        self.check_timer.stop()
        self.timer.stop()
        if self.command_timer.isActive() :
            self.command_timer.stop()
            if self.check() :
                pos = event.globalPos()
                dx = pos.x() - self.origin.x()
                dy = pos.y() - self.origin.y()
                d = dx * dx + dy * dy
                if d > 1024 * 4.0 :
                    self.take.emit()
                    self.command.emit( dx, dy )
        else :
            if self.check() :
                if len( self.track ) > 0 :
                    pos = event.globalPos()
                    current_time = self.time.elapsed()
                    self.track.append( ( pos, current_time ) )
                    i = len( self.track ) - 1
                    flag = False
                    while i > 0 and not flag:
                        old_time = self.track[i][1]
                        #print i, time - old_time, self.track[i]
                        if current_time - old_time > 90 :
                            flag = True
                        else :
                            i = i - 1
                    #print i
                    pos = self.track[i][0]
                    time = self.track[i][1]
                    if flag :
                        next_pos = self.track[i+1][0]
                        next_time = self.track[i+1][1]
                        r = float( current_time - 90 - time ) / float( next_time - time )
                        v = next_pos - pos
                        #print "====="
                        #print r, current_time, next_time, time
                        #print v
                        v = v * r
                        #print v
                        pos = pos + v
                    dx = pos.x() - self.start.x()
                    dy = pos.y() - self.start.y()
                    self.move.emit( dx, dy )

    def __check( self ) :
        return True
    def mouseMoveEvent( self, event ) :
        if self.check() :
            pos = event.globalPos()
            if self.flag :
                #print self.time.elapsed()
                dx = pos.x() - self.start.x()
                dy = pos.y() - self.start.y()
                self.move.emit( dx, dy )
                self.track.append( ( pos, self.time.elapsed() ) )
            else :
                if self.timer.isActive() :
                    dx = pos.x() - self.origin.x()
                    dy = pos.y() - self.origin.y()
                    d = dx * dx + dy * dy
                    if d > 1024 * 1.5 :
                        if not self.check_timer.isActive() :
                            self.start = ( pos + self.origin ) / 2
                            #print "move", dx, dy
                            self.take.emit()
                            self.flag = True
                            self.track.append( ( pos, self.time.elapsed() ) )
                    elif d > 1024 * 3.0 :
                        self.start = self.origin
                        #print "move", dx, dy
                        self.take.emit()
                        self.flag = True
                        self.track.append( ( pos, self.time.elapsed() ) )
    @QtCore.Slot()
    def timeout( self ) :
        self.timer.stop()
    @QtCore.Slot()
    def check_timeout( self ) :
        self.check_timer.stop()
    @QtCore.Slot()
    def command_timeout( self ) :
        self.command_timer.stop()
