from QtImport import QtGui, QtCore, QtDeclarative
from engine import IMEngine

class Document( QtCore.QObject ) :
    def __init__( self, parent = None ) :
        QtCore.QObject.__init__( self, parent )
        self.text_value = ""
        self.cursorPosition_value = 0
    @QtCore.Slot( str )
    def insert( self, text ) :
        self.text_value = self.text_value[:self.cursorPosition_value] + text + self.text_value[self.cursorPosition_value:]
        self.cursorPosition_value += len( text )
        print self.cursorPosition_value
        self.textChanged.emit( self.text_value )
        self.cursorPositionChanged.emit( self.cursorPosition_value )

    @QtCore.Slot()
    def readText( self ) :
        return self.text_value
    @QtCore.Slot( str )
    def writeText( self, text ) :
        self.text_value = text
        self.cursorPosition_value = len( text )
        self.textChanged.emit( self.text_value )
        self.cursorPositionChanged.emit( self.cursorPosition_value )
    textChanged = QtCore.Signal( str )
    text = QtCore.Property( str, readText, writeText, notify = textChanged )

    @QtCore.Slot()
    def readCorsorPositon( self ) :
        return self.cursorPosition_value
    @QtCore.Slot( int )
    def writeCursorPosition( self, pos ) :
        self.text_value = pos
        self.cursorPositionChanged.emit( self.cursorPosition_value )
    @QtCore.Slot( int )
    def setCursorPosition( self, pos ) :
        self.cursorPosition_value = pos
        #self.cursorPositionChanged.emit( self.cursorPosition_value )
    cursorPositionChanged = QtCore.Signal( int )
    cursorPosition = QtCore.Property( int, readCorsorPositon, writeCursorPosition, notify = cursorPositionChanged )

    @QtCore.Slot()
    def slotUpdate( self ) :
        print self.text_value

if __name__ == "__main__" :
    import sys
    app = QtGui.QApplication( sys.argv )

    view = QtDeclarative.QDeclarativeView()
    view.setSource( QtCore.QUrl("./qml/qwert.qml") ) ;

    document = Document()
    imEngine = IMEngine()
    #imEngine.load( "../../data/formated" )
    context = view.rootContext()
    context.setContextProperty( "imEngine", imEngine )
    context.setContextProperty( "document", document )
    imEngine.candStringChanged.connect( document.slotUpdate )

    document.text = "test"
    view.show()

    sys.exit( app.exec_() )


