from QtImport import QtGui, QtCore, QtDeclarative

if __name__ == "__main__" :
    import sys
    app = QtGui.QApplication( sys.argv )

    view = QtDeclarative.QDeclarativeView()
    view.setSource( QtCore.QUrl("./qml/qwert.qml") ) ;

    view.show()

    sys.exit( app.exec_() )


