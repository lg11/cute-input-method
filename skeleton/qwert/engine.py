from QtImport import QtGui, QtCore, QtDeclarative

import sys
sys.path.append( "../pinyinLookup" )
from lookup import PinyinLookup

class IMEngine( QtCore.QObject ) :
    keysym = [ "" ] * 256
    keysym[97] = "a"
    keysym[98] = "b"
    keysym[99] = "c"
    keysym[100] = "d"
    keysym[101] = "e"
    keysym[102] = "f"
    keysym[103] = "g"
    keysym[104] = "h"
    keysym[105] = "i"
    keysym[106] = "j"
    keysym[107] = "k"
    keysym[108] = "l"
    keysym[109] = "m"
    keysym[110] = "n"
    keysym[111] = "o"
    keysym[112] = "p"
    keysym[113] = "q"
    keysym[114] = "r"
    keysym[115] = "s"
    keysym[116] = "t"
    keysym[117] = "u"
    keysym[118] = "v"
    keysym[119] = "w"
    keysym[120] = "x"
    keysym[121] = "y"
    keysym[122] = "z"

    keycode_backspace = 201

    def readCandString( self ) :
        return self.candString_value
    def writeCandString( self, value ) :
        self.candString_value = value
    candStringChanged = QtCore.Signal()
    candString = QtCore.Property( str, readCandString, writeCandString, notify = candStringChanged )

    def __init__( self, parent = None ) :
        QtCore.QObject.__init__( self, parent )
        self.pinyinLookup = PinyinLookup()
        self.load = self.pinyinLookup.load
        self.candString_value = [ "" ] * 5
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
            word = cand[1].decode( "utf-8" )
        #word = "abc"
        self.candString = word
    @QtCore.Slot( int )
    def keyEvent( self, keycode ) :
        if keycode == self.keycode_backspace :
            self.pinyinLookup.pop()
            #self.printCand()
        elif keycode >= 97 and keycode <= 122 :
            code = self.keysym[keycode]
            self.pinyinLookup.append( code )
            #self.printCand()
        
