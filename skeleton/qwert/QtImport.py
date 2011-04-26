try :
    from PySide import QtGui, QtCore, QtDeclarative
except ImportError :
    try :
        from PyQt4 import QtGui, QtCore, QtDeclarative
        QtCore.Signal = QtCore.pyqtSignal
        QtCore.Slot = QtCore.pyqtSlot
    except ImportError :
        pass
    

