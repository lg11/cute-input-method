from QtImport import QtGui, QtCore, QtDeclarative

import sys
sys.path.append( "../pinyinLookup" )

from lookup import PinyinLookup
from t9lookup import T9PinyinLookup

class IMEngine( QtCore.QObject ) :
    needCommitChanged = QtCore.Signal( bool )
    @QtCore.Slot()
    def readNeedCommit( self ) :
        return len( self.selected ) > 0 and len( self.preeditString ) <= 0 and len( self.invaildCode ) <= 0
    needCommit = QtCore.Property( bool, readNeedCommit, notify = needCommitChanged )

    hasSelectedChanged = QtCore.Signal( bool )
    @QtCore.Slot()
    def readHasSelected( self ) :
        return len( self.selected ) > 0
        #self.preeditString_value = value
    hasSelected = QtCore.Property( bool, readHasSelected, notify = hasSelectedChanged )

    hasCodeChanged = QtCore.Signal( bool )
    @QtCore.Slot()
    def readHasCode( self ) :
        return len( self.lookup[self.mode].spliter.code ) > 0
        #self.preeditString_value = value
    hasCode = QtCore.Property( bool, readHasCode, notify = hasCodeChanged )

    codeChanged = QtCore.Signal( str )
    @QtCore.Slot()
    def readCode( self ) :
        return self.lookup[self.mode].spliter.code
    code = QtCore.Property( str, readCode, notify = codeChanged )

    #contextTextChanged = QtCore.Signal( str )
    #@QtCore.Slot()
    #def readContextText( self ) :
        #return self.contextText_value
    #def writeContextText( self, value ) :
        #self.contextText_value = value
    #contextText = QtCore.Property( str, readContextText, writeContextText, notify = contextTextChanged )

    selectedWordChanged = QtCore.Signal( str )
    @QtCore.Slot()
    def readSelectedWord( self ) :
        return self.selectedWord_value
    @QtCore.Slot( str )
    def writeSelectedWord( self, value ) :
        self.selectedWord_value = value
    selectedWord = QtCore.Property( str, readSelectedWord, writeSelectedWord, notify = selectedWordChanged )

    preeditStringChanged = QtCore.Signal( str )
    @QtCore.Slot()
    def readPreeditString( self ) :
        return self.preeditString_value
    @QtCore.Slot( str )
    def writePreeditString( self, value ) :
        self.preeditString_value = value
    preeditString = QtCore.Property( str, readPreeditString, writePreeditString, notify = preeditStringChanged )

    invaildCodeChanged = QtCore.Signal( str )
    @QtCore.Slot()
    def readInvaildCode( self ) :
        return self.invaildCode_value
    @QtCore.Slot( str )
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
        pinyinLookup = PinyinLookup()
        t9Lookup = T9PinyinLookup()
        self.lookup = [ pinyinLookup, t9Lookup ]
        self.candString_value = ""
        #self.contextText_value = ""
        self.selectedWord_value = ""
        self.preeditString_value = ""
        self.invaildCode_value = ""
        self.pageIndex = 0
        #self.selected = [ [], "", [], [] ]
        self.selected = []
        self.mode = 0
        self.pageLength = 5
    @QtCore.Slot( int )
    def setMode( self, mode ) :
        if mode == 0 :
            self.pageLength = 5
        elif mode == 1 :
            self.pageLength = 6
        self.mode = mode
        self.clear()
    def load( self, path ) :
        self.lookup[0].load( path )
        self.lookup[1].setParent( self.lookup[0] )
    def printCand( self ) :
        for i in range( self.pageLength ) :
            cand = self.lookup[self.mode].getCand( i )
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
        cand = self.lookup[self.mode].getCand( pageIndex * self.pageLength )
        if cand :
            self.pageIndex = pageIndex
    @QtCore.Slot( int )
    def updateCandString( self, index ) :
        word = ""
        cand = self.lookup[self.mode].getCand( self.pageIndex * self.pageLength + index )
        if cand :
            word = cand[1]
        self.candString = word
    @QtCore.Slot( int )
    def getPreeditString( self, index ) :
        preeditString = ""
        cand = self.lookup[self.mode].getCand( self.pageIndex * self.pageLength + index )
        if cand :
            preeditString = cand[3]
        #print preeditString
        return preeditString
    @QtCore.Slot( int )
    def getInvaildCode( self, index ) :
        invaildCode = ""
        cand = self.lookup[self.mode].getCand( self.pageIndex * self.pageLength + index )
        if cand :
            preeditString = cand[3]
            count = len( preeditString ) - preeditString.count( "'" )
        else :
            count = 0
        invaildCode = self.lookup[self.mode].spliter.code[count:]
        #print invaildCode
        return invaildCode
    @QtCore.Slot( int )
    def updatePreeditString( self, index ) :
        self.preeditString = self.getPreeditString( index )
        self.invaildCode = self.getInvaildCode( index )
    @QtCore.Slot( int )
    def select( self, index ) :
        candIndex = self.pageIndex * self.pageLength + index
        cand = self.lookup[self.mode].getCand( candIndex )
        invaildCode = self.getInvaildCode( index )
        if cand :
            #print candIndex
            key, word, freq, preeditString, candStartIndex = cand 
            #print key, word, freq, preeditString, candStartIndex
            freqArg = -1
            if len( self.selected ) <= 0 :
                halfIndex = ( candStartIndex + candIndex ) / 2
                halfCand = self.lookup[self.mode].getCand( halfIndex )
                halfKey, halfWord, halfFreq, halfPreeditString, halfCandStartIndex = halfCand
                #print halfKey, halfWord, halfFreq, halfPreeditString, halfCandStartIndex
                freqArg = halfFreq + 1
            keys = key.split( "'" )
            preeditStrings = preeditString.split( "'" )
            for i in range( len( word ) ) :
                self.selected.append( [ keys[i], word[i], -1, preeditStrings[i] ] )
            self.selectedWord += word
            self.selected[-1][2] = freqArg
            #print self.selected
            self.lookup[self.mode].clear()
            self.pageIndex = 0
            if len( invaildCode ) > 0 :
                for c in invaildCode :
                    self.lookup[self.mode].append( c )
        else :
            pass
    @QtCore.Slot()
    def cancel( self ) :
        if len( self.selected ) > 0 :
            item = self.selected[-1]
            code = item[3]
            if self.mode == 1 :
                code = code.translate( self.lookup[1].trans )
            code = code + self.lookup[self.mode].spliter.code
            self.lookup[self.mode].clear()
            self.pageIndex = 0
            for c in code :
                self.lookup[self.mode].append( c )
            self.selected.pop()
            self.selectedWord = self.selectedWord[:-1]
    @QtCore.Slot()
    def clear( self ) :
        self.lookup[0].clear()
        self.lookup[1].clear()
        self.pageIndex = 0
        self.selectedWord = ""
        self.preeditString = ""
        self.invaildCode = ""
        self.selected = []
    @QtCore.Slot( str )
    def appendCode( self, code ) :
        self.lookup[self.mode].append( code )
        self.pageIndex = 0
    @QtCore.Slot()
    def backspace( self ) :
        self.lookup[self.mode].pop()
        self.pageIndex = 0
    @QtCore.Slot()
    def commit( self ) :
        if len( self.selected ) > 0 :
            key = []
            word = self.selectedWord
            freq = self.selected[-1][2]
            for selected in self.selected :
                key.append( selected[0] )
            key = "'".join( key )
            self.lookup[0].update( key, word, freq )
            self.lookup[1].addKey( key ) 
            #print key, word, freq
        self.clear()
        
