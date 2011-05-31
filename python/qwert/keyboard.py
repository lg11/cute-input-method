from QtImport import QtGui, QtCore, QtDeclarative
#from mouseTracker import Tracker

class Clipboard( QtCore.QObject ) :
    textChanged = QtCore.Signal( str )
    @QtCore.Slot()
    def readText( self ) :
        return self.clipboard.text()
    @QtCore.Slot( str )
    def writeText( self, value ) :
        self.clipboard.setText( value )
    text = QtCore.Property( str, readText, writeText, notify = textChanged )
    def __init__( self, parent = None ) :
        QtCore.QObject.__init__( self, parent )
        self.clipboard = QtGui.QApplication.clipboard()

class Keyboard( QtDeclarative.QDeclarativeView ) :
    commit = QtCore.Signal( str )
    def __init__( self, parent = None, daemonFlag = False ) :
        QtDeclarative.QDeclarativeView.__init__( self, parent )
        self.setAttribute( QtCore.Qt.WA_InputMethodEnabled, False )
        self.daemonFlag = False
        if ( not parent ) and daemonFlag :
            self.setWindowFlags( QtCore.Qt.Dialog | QtCore.Qt.FramelessWindowHint )
            self.daemonFlag = daemonFlag

        self.setAttribute( QtCore.Qt.WA_TranslucentBackground, True )
        palette = QtGui.QPalette()
        palette.setColor( QtGui.QPalette.Base, QtCore.Qt.transparent )
        self.setPalette( palette )

        self.root = None
        self.sceneResized.connect( self.keepSize )

        self.desktop = QtGui.QApplication.desktop()
        self.desktop.resized.connect( self.checkRotate )
        #self.clipboard = Clipboard()
    def set( self, qmlSourcePath, engine = None, engineName = "" ) :
        self.setSource( QtCore.QUrl( qmlSourcePath ) ) ;
        context = self.rootContext()
        if engine :
            self.engine = engine
            if engineName == "" :
                context.setContextProperty( "imEngine", self.engine )
            else :
                context.setContextProperty( engineName, self.engine )
        #context.setContextProperty( "clipboard", self.clipboard )
        root = self.rootObject()
        self.setText = root.setText
        self.getText = root.getText
        self.setRotate = root.setRotate
        self.root = root
    @QtCore.Slot( QtCore.QSize)
    def keepSize( self, size ) :
        if ( self.daemonFlag ) :
            width = self.size().width()
            height = self.size().height()
            keepedWidth = self.root.width()
            keepedHeight = self.root.height()
            #print width, height, self.keepedWidth, self.keepedHeight
            if height != keepedHeight or width != keepedWidth :
                self.resize( keepedWidth, keepedHeight )
    def closeEvent( self, event ) :
        if self.daemonFlag :
            self.engine.lookup[0].dict.flush()
            #self.hide()
            text = self.getText()
            self.commit.emit( text )
            event.ignore()
    @QtCore.Slot()
    def checkRotate( self ) :
        desktopWidth = self.desktop.width()
        desktopHeight = self.desktop.height()
        if desktopWidth >= desktopHeight :
            self.setRotate( 0 )
        else :
            self.setRotate( 1 )


if __name__ == "__main__" :
    import sys
    #from engine import IMEngine
    app = QtGui.QApplication( sys.argv )

    #view = Keyboard( daemonFlag = True )
    view = Keyboard( daemonFlag = False )
    #engine = IMEngine()
    #view.set( "./qml/qwert.qml", engine )
    view.set( "./qml/qwert.qml" )
    #view.setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, True )

    path = "../../data/formated"
    print "load sysdict from :", path
    #engine.load( path )
    #engine.lookup[0].dict.logOn()


    #view.setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, True )
    view.show()

    sys.exit( app.exec_() )


