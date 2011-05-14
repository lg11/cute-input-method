from QtImport import QtGui, QtCore, QtDeclarative

class Tracker( QtCore.QObject ) :
    endXChanged = QtCore.Signal( float )
    def readEndX( self ) :
        return self.endX_value
    def writeEndX( self, x ) :
        self.endX_value = x
    endX = QtCore.Property( float, readEndX, writeEndX, notify = endXChanged )

    endYChanged = QtCore.Signal( float )
    def readEndY( self ) :
        return self.endY_value
    def writeEndY( self, y ) :
        self.endY_value = y
    endY = QtCore.Property( float, readEndY, writeEndY, notify = endYChanged )

    def __init__( self, parent = None ) :
        QtCore.QObject.__init__( self, parent )
        self.stack = []
        self.time = QtCore.QTime()
        self.time.start()
        self.endX_value = 0
        self.endY_value = 0
    @QtCore.Slot()
    def reset( self ) :
        self.time.restart()
        self.stack = []
    @QtCore.Slot( float, float )
    def push( self, x, y ) :
        self.stack.append( ( x, y, self.time.elapsed() ) )
    @QtCore.Slot()
    def end( self ) :
        if len( self.stack ) > 1 :
            lastX, lastY, lastTime = self.stack[-1]
            i = len( self.stack ) - 1
            flag = False
            while i >= 0 and not flag:
                oldTime = self.stack[i][2]
                #print i, time - old_time, self.track[i]
                if lastTime - oldTime > 90 :
                    flag = True
                else :
                    i = i - 1
            if flag :
                prevX, prevY, prevTime = self.stack[i]
                nextX, nextY, nextTime = self.stack[i+1]
                r = float( lastTime - 90 - prevTime ) / float( nextTime - prevTime )
                dx = nextX - prevX
                dy = nextY - prevY
                #print "after 90"
                #print lastX, lastY
                #print prevX, prevY, nextX, nextY
                #print r, lastTime, nextTime, prevTime
                #print dx, dy
                dx = dx * r
                dy = dy * r
                #print dx, dy
                x = prevX + dx
                y = prevY + dy
                #print x, y
                #x = ( x + lastX ) / 2
                #y = ( y + lastY ) / 2
                self.endX = x
                self.endY = y
            else :
                #print "in 90"
                prevX, prevY, prevTime = self.stack[0]
                #x = prevX
                #y = prevY
                x = ( prevX + lastX ) / 2
                y = ( prevY + lastY ) / 2
                #print prevX, prevY, lastX, lastY
                #print x, y
                self.endX = x
                self.endY = y
        elif len( self.stack ) > 0 :
            #print "only One"
            lastX, lastX, lastTime = self.stack[0]
            x = lastX
            y = lastY
            #print x, y
            self.endX = x
            self.endY = y
