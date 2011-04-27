from QtImport import QtGui, QtCore, QtDeclarative
from engine import IMEngine

if __name__ == "__main__" :
    import sys
    app = QtGui.QApplication( sys.argv )

    view = QtDeclarative.QDeclarativeView()
    view.setSource( QtCore.QUrl("./qml/qwert.qml") ) ;

    imEngine = IMEngine()
    imEngine.load( "../../data/formated" )
    context = view.rootContext()
    context.setContextProperty( "imEngine", imEngine )

    view.show()

    sys.exit( app.exec_() )


