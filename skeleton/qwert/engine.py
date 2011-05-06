from QtImport import QtGui, QtCore, QtDeclarative

import sys
sys.path.append( "../pinyinLookup" )

from lookup import PinyinLookup

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
        return len( self.pinyinLookup.spliter.code ) > 0
        #self.preeditString_value = value
    hasCode = QtCore.Property( bool, readHasCode, notify = hasCodeChanged )

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
    def writeSelectedWord( self, value ) :
        self.selectedWord_value = value
    selectedWord = QtCore.Property( str, readSelectedWord, writeSelectedWord, notify = selectedWordChanged )

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
        #self.contextText_value = ""
        self.selectedWord_value = ""
        self.preeditString_value = ""
        self.invaildCode_value = ""
        self.pageIndex = 0
        #self.selected = [ [], "", [], [] ]
        self.selected = []
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
    def getPreeditString( self, index ) :
        preeditString = ""
        cand = self.pinyinLookup.getCand( self.pageIndex * 5 + index )
        if cand :
            preeditString = cand[3]
        #print preeditString
        return preeditString
    @QtCore.Slot( int )
    def getInvaildCode( self, index ) :
        invaildCode = ""
        cand = self.pinyinLookup.getCand( self.pageIndex * 5 + index )
        if cand :
            preeditString = cand[3]
            count = len( preeditString ) - preeditString.count( "'" )
            invaildCode = self.pinyinLookup.spliter.code[count:]
        #print invaildCode
        return invaildCode
    @QtCore.Slot( int )
    def updatePreeditString( self, index ) :
        self.preeditString = self.getPreeditString( index )
        self.invaildCode = self.getInvaildCode( index )
    @QtCore.Slot( int )
    def select( self, index ) :
        candIndex = self.pageIndex * 5 + index
        cand = self.pinyinLookup.getCand( candIndex )
        invaildCode = self.getInvaildCode( index )
        if cand :
            #print candIndex
            key, word, freq, preeditString, candStartIndex = cand 
            #print key, word, freq, preeditString, candStartIndex
            freqArg = -1
            if len( self.selected ) <= 0 :
                halfIndex = ( candStartIndex + candIndex ) / 2
                halfCand = self.pinyinLookup.getCand( halfIndex )
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
            self.pinyinLookup.clear()
            self.pageIndex = 0
            if len( invaildCode ) > 0 :
                for c in invaildCode :
                    self.pinyinLookup.append( c )
        else :
            pass
    @QtCore.Slot()
    def cancel( self ) :
        if len( self.selected ) > 0 :
            item = self.selected[-1]
            code = item[3] + self.pinyinLookup.spliter.code
            self.pinyinLookup.clear()
            self.pageIndex = 0
            for c in code :
                self.pinyinLookup.append( c )
            self.selected.pop()
            self.selectedWord = self.selectedWord[:-1]
    @QtCore.Slot()
    def clear( self ) :
        self.pinyinLookup.clear()
        self.pageIndex = 0
        self.selectedWord = ""
        self.preeditString = ""
        self.invaildCode = ""
        self.selected = []
    @QtCore.Slot( str )
    def appendCode( self, code ) :
        self.pinyinLookup.append( code )
        self.pageIndex = 0
    @QtCore.Slot()
    def backspace( self ) :
        self.pinyinLookup.pop()
        self.pageIndex = 0
        
