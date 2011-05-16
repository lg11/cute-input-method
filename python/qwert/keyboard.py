from QtImport import QtGui, QtCore, QtDeclarative
from mouseTracker import Tracker

#class Clipboard( QtCore.QObject ) :
    #def __init__( self, parent = None ) :
        #QtCore.QObject.__init__( self, parent )
        #self.clipboard = QtGui.QClipboard()
    #@QtCore.Slot( str )
    #def set( self, text ) :
        #self.clipboard.setText( text )

class Keyboard( QtDeclarative.QDeclarativeView ) :
    commit = QtCore.Signal( str )
    def __init__( self, parent = None, daemonFlag = False ) :
        QtDeclarative.QDeclarativeView.__init__( self, parent )
        self.setAttribute( QtCore.Qt.WA_InputMethodEnabled, False )
        self.daemonFlag = False
        #self.setWindowFlags( QtCore.Qt.X11BypassWindowManagerHint )
        #self.show = self.showFullScreen
        #self.setWindowFlags( QtCore.Qt.Dialog | QtCore.Qt.FramelessWindowHint )
        if ( not parent ) and daemonFlag :
            self.setWindowFlags( QtCore.Qt.Dialog | QtCore.Qt.FramelessWindowHint )
            self.daemonFlag = daemonFlag
        #self.setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, False )

        #self.setAttribute( QtCore.Qt.WA_TranslucentBackground, True )
        #palette = QtGui.QPalette()
        #palette.setColor( QtGui.QPalette.Base, QtCore.Qt.transparent )
        #self.setPalette( palette )

        #self.keepedWidth = 800
        #self.keepedHeight = 480

        self.mouseTracker = Tracker()
        self.sceneResized.connect( self.keepSize )
    def set( self, qmlSourcePath, engine = None, engineName = "" ) :
        self.setSource( QtCore.QUrl( qmlSourcePath ) ) ;
        if engine :
            self.engine = engine
            context = self.rootContext()
            if engineName == "" :
                context.setContextProperty( "imEngine", self.engine )
            else :
                context.setContextProperty( engineName, self.engine )
        context.setContextProperty( "mouseTracker", self.mouseTracker )
        root = self.rootObject()
        self.setText = root.setText
        self.getText = root.getText
        self.keepedWidth = root.width()
        self.keepedHeight = root.height()
        self.rotateSignal = root.rotateSignal
        #root.close.connect( self.close )
    @QtCore.Slot( QtCore.QSize)
    def keepSize( self, size ) :
        #print "keep"
        if ( self.daemonFlag ) :
            width = self.size().width()
            height = self.size().height()
            #print width, height, self.keepedWidth, self.keepedHeight
            if height != self.keepedHeight or width != self.keepedWidth :
                #print width, height, self.keepedWidth, self.keepedHeight
                self.resize( self.keepedWidth, self.keepedHeight )
    def closeEvent( self, event ) :
        if self.daemonFlag :
            self.hide()
            text = self.getText()
            #print text
            self.commit.emit( text )
            event.ignore()


if __name__ == "__main__" :
    def r() :
        print "r"
    import config
    import sys
    from engine import IMEngine
    app = QtGui.QApplication( sys.argv )

    view = Keyboard()
    engine = IMEngine()
    view.set( "./qml/qwert.qml", engine )
    #view.setAttribute( QtCore.Qt.WA_Maemo5PortraitOrientation, True )
    view.rotateSignal.connect( r )

    path = config.check_path( config.sysdict_path )
    print "load sysdict from :", path
    #engine.load( path )
    #engine.pinyinLookup.dict.logOn()

    view.show()

    sys.exit( app.exec_() )


