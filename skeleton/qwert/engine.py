from QtImport import QtGui, QtCore, QtDeclarative

import sys
sys.path.append( "../pinyinLookup" )
from lookup import PinyinLookup

class IMEngine( QtCore.QObject ) :
    preeditStringChanged = QtCore.Signal( str )
    @QtCore.Slot()
    def readPreeditString( self ) :
        return self.preeditString_value
    def writePreeditString( self, value ) :
        self.preeditString_value = value
    preeditString = QtCore.Property( str, readPreeditString, writePreeditString, notify = preeditStringChanged )

    candStringChanged = QtCore.Signal( str )
    @QtCore.Slot()
    def readCandString( self ) :
        return self.candString_value
    @QtCore.Slot( str )
    def writeCandString( self, value ) :
        self.candString_value = value
        #self.candStringChanged.emit( self.candString_value )
    candString = QtCore.Property( str, readCandString, writeCandString, notify = candStringChanged )

    def __init__( self, parent = None ) :
        QtCore.QObject.__init__( self, parent )
        self.pinyinLookup = PinyinLookup()
        self.load = self.pinyinLookup.load
        self.candString_value = ""
        self.preeditString_value = ""
    def printCand( self ) :
        for i in range( 5 ) :
            cand = self.pinyinLookup.getCand( i )
            if cand :
                key, word, freq = cand
                print key, word, freq
    @QtCore.Slot( int )
    def updateCandString( self, index ) :
        word = ""
        cand = self.pinyinLookup.getCand( index )
        if cand :
            word = cand[1]
        #word = "abc"
        self.candString = word
        #self.candStringChanged.emit( self.candString_value )
    @QtCore.Slot( str )
    def appendCode( self, code ) :
        self.pinyinLookup.append( code )
        self.preeditString = self.pinyinLookup.cache[-1][2]
    @QtCore.Slot()
    def backspace( self ) :
        self.pinyinLookup.pop()
        self.preeditString = self.pinyinLookup.cache[-1][2]
        
