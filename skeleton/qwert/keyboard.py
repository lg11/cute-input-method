from QtImport import QtGui, QtCore, QtDeclarative
from engine import IMEngine

class Clipboard( QtCore.QObject ) :
    def __init__( self, parent = None ) :
        QtCore.QObject.__init__( self, parent )
        self.clipboard = QtGui.QClipboard()
    @QtCore.Slot( str )
    def set( self, text ) :
        self.clipboard.setText( text )

if __name__ == "__main__" :
    import sys
    app = QtGui.QApplication( sys.argv )

    view = QtDeclarative.QDeclarativeView()
    view.setSource( QtCore.QUrl("./qml/qwert.qml") ) ;

    clipboard = Clipboard()
    imEngine = IMEngine()
    #imEngine.load( "../../data/formated" )
    context = view.rootContext()
    context.setContextProperty( "imEngine", imEngine )
    context.setContextProperty( "clipboard", clipboard )

    view.show()

    sys.exit( app.exec_() )


