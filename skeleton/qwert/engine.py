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
    def __init__( self, parent = None ) :
        QtCore.QObject.__init__( self, parent )
        self.pinyinLookup = PinyinLookup()
        self.load = self.pinyinLookup.load
    @QtCore.Slot( int )
    def keyEvent( self, keycode ) :
        if keycode >= 97 and keycode <= 122 :
            code = self.keysym[keycode]
            self.pinyinLookup.append( code )
            for i in range( 5 ) :
                cand = self.pinyinLookup.getCand( i )
                if cand :
                    key, word, freq = cand
                    print key, word, freq
        
