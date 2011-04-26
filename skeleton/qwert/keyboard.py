from QtImport import QtGui, QtCore, QtDeclarative

class QMLInterface( QtCore.QObject ) :
    def __init__( self, parent = None ) :
        QtCore.QObject.__init__( self, parent )
    @QtCore.Slot( int )
    def keyEvent( self, keycode ) :
        print keycode

if __name__ == "__main__" :
    import sys
    app = QtGui.QApplication( sys.argv )

    view = QtDeclarative.QDeclarativeView()
    view.setSource( QtCore.QUrl("./qml/qwert.qml") ) ;

    qmlInterface = QMLInterface()
    context = view.rootContext()
    context.setContextProperty( "qmlInterface", qmlInterface )

    view.show()

    sys.exit( app.exec_() )


