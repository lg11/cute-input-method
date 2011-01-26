#-!- coding=utf-8 -!-

#MMM 那算了…… #MMM 那算了…… #MMM 那算了…… #MMM 那算了…… #MMM 那算了…… #MMM 那算了…… #MMM 那算了…… #MMM 那算了…… #MMM 那算了…… #MMM 那算了……
from PySide import QtGui, QtCore, QtOpenGL

class PaperContext() :
    def __init__( self, text = "" ) :
        self.text = text
        self.cursor = len( text )
        self.currentLineCursor = [ -1, -1 ]
        self.checkCurrentLine()
    def setText( self, text ) :
        self.text = text
        self.cursor = len( text )
        self.checkCurrentLine()
    def setCursor( self, cursor ) :
        if cursor > len( self.text ) :
            self.cursor = len( self.text )
        elif cursor < 0 :
            self.cursor = 0
        else :
            self.cursor = cursor
        self.checkCurrentLine()
    def checkCurrentLine( self ) :
        if len( self.text ) > 0 :
            if self.cursor == len( self.text ) :
                start_pos = self.text.rfind( "\n" )
                end_pos = -1
            elif self.cursor == 0 :
                start_pos = -1
                end_pos = self.text.find( "\n" )
            else :
                start_pos = self.text.rfind( "\n", 0, self.cursor )
                end_pos = self.text.find( "\n", self.cursor )
            self.currentLineCursor[0] = start_pos
            self.currentLineCursor[1] = end_pos
        else :
            self.currentLineCursor[0] = -1
            self.currentLineCursor[1] = -1
    def currentLineCursorOffset( self ) :
        start_pos = self.currentLineCursor[0]
        offset = 0
        if start_pos >= 0 :
            offset = self.cursor - self.currentLineCursor[0] - 1
        else :
            offset = self.cursor
        return offset
    def currentLine( self ) :
        start_pos = self.currentLineCursor[0]
        end_pos = self.currentLineCursor[1]
        if start_pos >= 0 and end_pos >= 0 :
            start_pos = start_pos + 1
            text = self.text[start_pos:end_pos]
        elif start_pos >= 0 :
            start_pos = start_pos + 1
            text = self.text[start_pos:]
        elif end_pos >= 0 :
            text = self.text[:end_pos]
        else :
            text = self.text
        return text

class PaperChar() :
    def __init__( self, char = "", length = 0 ) :
        self.char = char
        self.length = length
    def set( self, char, length ) :
        self.char = char
        self.length = length

class PaperLine() :
    def __init__( self, paper ) :
        self.paper = paper
        self.charList = []
        self.warpLineCount = 0
        self.currentWarpLine = -1
        self.currentWarpCursor = -1
    def genLine( self, line, cursorOffset = -1 ) :
        self.charList = []
        self.warpLineCount = 0
        self.currentWarpLine = -1
        self.currentWarpCursor = -1

        index = 0
        while index < len( line ) :
            i = 0
            while index < len( line ) and i < self.paper.lineLenght :
                if index == cursorOffset :
                    count = len( self.charList )
                    self.currentWarpLine = count / self.paper.lineLenght
                    self.currentWarpCursor = count % self.paper.lineLenght
                ch = line[index]
                #print ch, i, index
                charWidth = self.paper.charMetrics.width( ch ) 
                if charWidth > self.paper.charWidth :
                    if i + 1 >= self.paper.lineLenght :
                        self.charList.append( PaperChar( ">", 0 ) )
                        self.charList.append( PaperChar( ch, 2 ) )
                        self.charList.append( PaperChar() )
                    else :
                        self.charList.append( PaperChar( ch, 2 ) )
                        self.charList.append( PaperChar() )
                    i = i + 2
                else :
                    self.charList.append( PaperChar( ch, 1 ) )
                    i = i + 1
                index = index + 1

        count = len( self.charList )
        self.warpLineCount = count / self.paper.lineLenght
        if count % self.paper.lineLenght > 0 :
            self.warpLineCount = self.warpLineCount + 1

class Paper( QtGui.QGraphicsItem ) :
    def __init__( self, parent = None, scene = None ) :
        QtGui.QGraphicsItem.__init__( self, parent, scene )
        self.charFont = QtGui.QFont( "Monospace" )
        self.charFont.setPointSize( 16 )
        #self.charFont = QtGui.QFont()
        self.charMetrics = QtGui.QFontMetrics( self.charFont )
        self.charWidth = self.charMetrics.width( "M" ) 
        self.charHeight = self.charMetrics.height()
        #print self.charWidth, self.charHeight
        self.lineLenght = 30
        self.lineCount = 9
        self.prevLineCount = 4
        self.nextLineCount = 4
        self.drawedPrevLine = 0
        self.drawedNextLine = 0
        self.textOption = QtGui.QTextOption( QtCore.Qt.AlignHCenter )
        self.context = PaperContext()
        self.line = PaperLine( self )
    def boundingRect( self ) :
        return QtCore.QRectF( 0, 0, ( self.charWidth + 1 ) * self.lineLenght, self.charHeight * self.lineCount )
    def setText( self, text ) :
        self.context.setText( text )
        #self.lines = text.split( "\n" )
        #print self.context.currentLine()
        self.update()
    def setCursor( self, cursor ) :
        self.context.setCursor( cursor )
        #print self.context.currentLine()
        self.update()
    def drawCurrentLine( self, painter, line, offset ) :
        self.line.genLine( line, offset )

        startPos = 0
        startLine = self.prevLineCount - self.line.currentWarpLine
        if startLine < 0 :
            startPos = ( self.line.currentWarpLine - self.prevLineCount ) * self.lineLenght
            startline = 0
        warpLine = startLine + self.line.currentWarpLine
        
        index = startPos
        i = startLine
        while index < len( self.line.charList ) and i < self.lineCount :
            j = 0
            while index < len( self.line.charList ) and j < self.lineLenght :
                ch = self.line.charList[index].char
                length = self.line.charList[index].length
                if length > 0 :
                    rect = QtCore.QRect( QtCore.QPoint( j * self.charWidth, i * self.charHeight ), QtCore.QSize( self.charWidth * length, self.charHeight ) )
                    #painter.begin( self )

                    #print i ,warpLine, j, self.line.currentWarpCursor
                    if i == warpLine and j == self.line.currentWarpCursor :
                        #print "get"
                        painter.setPen( QtCore.Qt.cyan )
                    else :
                        painter.setPen( QtCore.Qt.white )
                    painter.drawText( rect, ch, self.textOption )
                    j = j + length
                else :
                    if len( ch ) > 0 :
                        rect = QtCore.QRect( QtCore.QPoint( j * self.charWidth, i * self.charHeight ), QtCore.QSize( self.charWidth, self.charHeight ) )
                        painter.setPen( QtCore.Qt.blue )
                        painter.drawText( rect, ch, self.textOption )
                        j = j + 1
                #print i, j, index, ch, length
                index = index + 1
            i = i + 1

    def paint( self, painter, option, widget ) :
        painter.setFont( self.charFont )
        currentLine = self.context.currentLine()
        self.drawedPrevLine = 0
        self.drawedNextLine = 0
        #print currentLine
        print self.context.text[self.context.cursor]
        self.drawCurrentLine( painter, currentLine, self.context.currentLineCursorOffset() )

class Controlor( QtGui.QGraphicsItem ) :
    def __init__( self, parent = None, scene = None ) :
        QtGui.QGraphicsItem.__init__( self, parent, scene )
    def boundingRect( self ) :
        return QtCore.QRectF( 0, 0, 300, 300 )
    def paint( self, painter, option, widget ) :
        #painter.setBrush( QtCore.Qt.cyan )
        painter.fillRect( self.boundingRect(), QtCore.Qt.cyan )
class Background( QtGui.QGraphicsItem ) :
    def __init__( self, parent = None, scene = None ) :
        QtGui.QGraphicsItem.__init__( self, parent, scene )
    def boundingRect( self ) :
        return QtCore.QRectF( 0, 0, 800, 480 )
    def paint( self, painter, option, widget ) :
        pass

if __name__ == "__main__" :
    import sys
    app = QtGui.QApplication( sys.argv )

    #palette = QtGui.QPalette()
    #palette.setColor( QtGui.QPalette.Base, QtCore.Qt.transparent )
    
    win = QtGui.QWidget()
    #win.setAttribute( QtCore.Qt.WA_TranslucentBackground, True )

    scene = QtGui.QGraphicsScene()
    view = QtGui.QGraphicsView( win )
    view.setScene( scene )
    #view.setAttribute( QtCore.Qt.WA_TranslucentBackground, True )
    #view.setPalette( palette )
    #view.setViewport( QtOpenGL.QGLWidget() )

    paper = Paper()
    file = open( "./graphic.py" )
    s = file.read()
    paper.setText( s.decode( "utf-8" ) )
    paper.setCursor( 62 )
    scene.addItem( paper )
    controlor = Controlor()
    controlor.moveBy( 450, 50 )
    scene.addItem( controlor )
    scene.addItem( Background() )

    view.setFixedSize( 800, 480 )
    #layout = QtGui.QHBoxLayout()
    #win.setLayout( layout )
    #layout.addWidget( view )

    win.show()

    sys.exit( app.exec_() )
