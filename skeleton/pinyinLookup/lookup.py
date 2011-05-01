from spliter import PinyinSpliter
from picker import Picker
from dictionary import Dictionary

class PinyinLookup() :
    def __init__( self ) :
        self.dict = Dictionary()
        self.spliter = PinyinSpliter( self.dict )
        self.picker = Picker( self.dict )
        self.cache = [ [ 0, [], "" ] ]
        self.candCacheIndex = 0
        self.candList = []
        self.load = self.dict.load
    def append( self, code ) :
        self.spliter.append( code )
        preedit = ""
        fitList = []
        fitPoint = -999
        for pinyinString in self.spliter.stack :
            currentFitPoint, keys = self.dict.fit( pinyinString.string )
            #print currentFitPoint, keys
            if currentFitPoint > fitPoint :
                fitList = []
                fitList.extend( keys )
                fitPoint = currentFitPoint
                preedit = str( pinyinString )
                #print preedit, pinyinString.string
            elif currentFitPoint == fitPoint :
                fitList.extend( keys )
        self.picker.set( fitList )
        cache = [ fitPoint, fitList, preedit ] 
        self.cache.append( cache )
        self.candList = []
        self.candCacheIndex = len( self.cache ) - 1
    def pop( self ) :
        if len( self.cache ) > 1 :
            self.spliter.pop()
            self.cache = self.cache[:-1]
            cache = self.cache[-1]
            fitList = cache[1]
            self.picker.set( fitList )
            self.candList = []
            self.candCacheIndex = len( self.cache ) - 1
    def getPreeditString( self ) :
        #print self.candCacheIndex
        cache = self.cache[self.candCacheIndex]
        s = cache[2]
        count = len( s ) - s.count( "'" )
        invaildCode = self.spliter.code[count:]
        #print self.spliter.code, s, invaildCode
        return s, invaildCode
    def checkCache( self ) :
        fitList = []
        while self.candCacheIndex >= 1 :
            self.candCacheIndex -= 1
            cache = self.cache[self.candCacheIndex]
            fitPoint = cache[0]
            fitList = cache[1]
            #print self.candCacheIndex, fitList
            if len( fitList ) >= 0 :
                if len( self.candList ) <= 0 :
                    break 
                elif fitPoint >= 0 :
                    break
        if self.candCacheIndex >= 1 :
            self.picker.set( fitList )
            return True
        else :
            return False
    def getCand( self, index ) :
        flag = True
        while flag and len( self.candList ) <= index :
            key, word, freq = self.picker.pick()
            if key :
                self.candList.append( [ key, word, freq ] )
            else :
                flag = self.checkCache()
        if flag :
            return self.candList[index]
        else :
            return None
    def clean( self ) :
        self.spliter.clean()
        self.cache = [ [ 0, [], "" ] ]
        self.candList = []
        self.candCacheIndex -= 0

if __name__ == "__main__" :
    import sys
    lookup = PinyinLookup()
    lookup.load( "../../data/formated" )
    while (1) :
        code = sys.stdin.readline()[:-1]
        for c in code :
            #print lookup.cache[-1]
            lookup.append( c )
        #print lookup.cache[-1]
        for i in range( 6 ) :
            cand = lookup.getCand( i )
            if cand :
                key, word, freq = cand
                print key, word, freq
        for c in code :
            lookup.pop()
            #print lookup.cache[-1]
        #lookup.clean()

