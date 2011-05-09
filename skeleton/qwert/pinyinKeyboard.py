from QtImport import QtGui, QtCore, QtDeclarative
from engine import IMEngine
import config

class Clipboard( QtCore.QObject ) :
    def __init__( self, parent = None ) :
        QtCore.QObject.__init__( self, parent )
        self.clipboard = QtGui.QClipboard()
    @QtCore.Slot( str )
    def set( self, text ) :
        self.clipboard.setText( text )

class Keyboard( QtDeclarative.QDeclarativeView ) :
    commit = QtCore.Signal( str )
    def __init__( self, parent = None ) :
        QtDeclarative.QDeclarativeView.__init__( self, parent )
        self.daemonFlag = False
        if not parent :
            self.setWindowFlags( QtCore.Qt.Dialog | QtCore.Qt.FramelessWindowHint )
            self.daemonFlag = True
        self.setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, False )
        path = config.check_path( config.qml_qwert_path )
        self.setSource( QtCore.QUrl( path ) ) ;

        self.imEngine = IMEngine()
        context = self.rootContext()
        context.setContextProperty( "imEngine", self.imEngine )
        root = self.rootObject()
        self.setText = root.setText
        self.getText = root.getText

        self.load = self.imEngine.load
    def closeEvent( self, event ) :
        if self.daemonFlag :
            self.hide()
            text = self.getText()
            #print text
            self.commit.emit( text )
            #event.ignore()

PinyinKeyboard = Keyboard

if __name__ == "__main__" :
    import sys
    app = QtGui.QApplication( sys.argv )

    view = Keyboard()

    path = config.check_path( config.sysdict_path )
    print "load sysdict from :", path
    #view.load( path )

    view.show()

    sys.exit( app.exec_() )


