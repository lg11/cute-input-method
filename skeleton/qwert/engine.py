from QtImport import QtGui, QtCore, QtDeclarative

import sys
sys.path.append( "../pinyinLookup" )
from lookup import PinyinLookup

class IMEngine( QtCore.QObject ) :
    hasCodeChanged = QtCore.Signal( bool )
    @QtCore.Slot()
    def readHasCode( self ) :
        return len( self.pinyinLookup.spliter.code ) > 0
    #def writePreeditString( self, value ) :
        #self.preeditString_value = value
    hasCode = QtCore.Property( bool, readHasCode, notify = hasCodeChanged )

    preeditStringChanged = QtCore.Signal( str )
    @QtCore.Slot()
    def readPreeditString( self ) :
        return self.preeditString_value
    def writePreeditString( self, value ) :
        self.preeditString_value = value
    preeditString = QtCore.Property( str, readPreeditString, writePreeditString, notify = preeditStringChanged )

    invaildCodeChanged = QtCore.Signal( str )
    @QtCore.Slot()
    def readInvaildCode( self ) :
        return self.invaildCode_value
    def writeInvaildCode( self, value ) :
        self.invaildCode_value = value
    invaildCode = QtCore.Property( str, readInvaildCode, writeInvaildCode, notify = invaildCodeChanged )

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
        self.invaildCode_value = ""
        self.pageIndex = 0
    def printCand( self ) :
        for i in range( 5 ) :
            cand = self.pinyinLookup.getCand( i )
            if cand :
                key, word, freq = cand
                print key, word, freq
    @QtCore.Slot()
    def prevPage( self ) :
        if self.pageIndex > 0 :
            self.pageIndex -= 1
    @QtCore.Slot()
    def nextPage( self ) :
        pageIndex = self.pageIndex + 1
        cand = self.pinyinLookup.getCand( pageIndex * 5 )
        if cand :
            self.pageIndex = pageIndex
    @QtCore.Slot( int )
    def updateCandString( self, index ) :
        word = ""
        cand = self.pinyinLookup.getCand( self.pageIndex * 5 + index )
        if cand :
            word = cand[1]
        self.candString = word
    @QtCore.Slot( int )
    def updatePreeditString( self, index ) :
        self.preeditString, self.invaildCode = self.pinyinLookup.getPreeditString( self.pageIndex * 5 + index )
        #print self.preeditString, invaildCode
        #self.candStringChanged.emit( self.candString_value )
    @QtCore.Slot( str )
    def appendCode( self, code ) :
        self.pinyinLookup.append( code )
        self.pageIndex = 0
    @QtCore.Slot()
    def backspace( self ) :
        self.pinyinLookup.pop()
        self.pageIndex = 0
        
