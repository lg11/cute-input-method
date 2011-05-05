from spliter import PinyinSpliter
from picker import Picker
from dictionary import Dictionary

class PinyinLookup() :
    def __init__( self ) :
        self.dict = Dictionary()
        self.spliter = PinyinSpliter( self.dict )
        self.picker = Picker( self.dict )
        #self.picker.set( [], [] )
        self.cache = [ [ 0, [], "" ] ]
        self.candCacheIndex = 0
        self.candStartIndex = 0
        self.candList = []
        self.load = self.dict.load
    def append( self, code ) :
        self.spliter.append( code )
        fitList = []
        preeditList = []
        fitPoint = -999
        for pinyinString in self.spliter.stack :
            currentFitPoint, keys = self.dict.fit( pinyinString.string )
            #print currentFitPoint, keys
            if currentFitPoint > fitPoint :
                fitList = []
                fitList.extend( keys )
                fitPoint = currentFitPoint
                preeditList = []
                preeditList.extend( [ str( pinyinString ) ] * len( keys ) )
            elif currentFitPoint == fitPoint :
                fitList.extend( keys )
                preeditList.extend( [ str( pinyinString ) ] * len( keys ) )
        self.picker.set( fitList, preeditList )
        cache = [ fitPoint, fitList, preeditList ] 
        self.cache.append( cache )
        self.candList = []
        self.candCacheIndex = len( self.cache ) - 1
        self.candStartIndex = 0
    def pop( self ) :
        if len( self.cache ) > 1 :
            self.spliter.pop()
            self.cache = self.cache[:-1]
            cache = self.cache[-1]
            fitList = cache[1]
            preeditList = cache[2]
            self.picker.set( fitList, preeditList )
            self.candList = []
            self.candCacheIndex = len( self.cache ) - 1
            self.candStartIndex = 0
    def checkCache( self ) :
        fitList = []
        cache = self.cache[self.candCacheIndex]
        currentFitPoint = cache[0]
        while self.candCacheIndex >= 1 :
            self.candCacheIndex -= 1
            cache = self.cache[self.candCacheIndex]
            fitPoint = cache[0]
            fitList = cache[1]
            preeditList = cache[2]
            #print self.candCacheIndex, fitList
            if len( fitList ) >= 0 :
                if len( self.candList ) <= 0 :
                    break 
                elif fitPoint >= currentFitPoint :
                    break
        if self.candCacheIndex >= 1 :
            self.picker.set( fitList, preeditList )
            return True
        else :
            return False
    def getCand( self, index ) :
        flag = True
        while flag and len( self.candList ) <= index :
            key, word, freq, preeditString = self.picker.pick()
            if key :
                self.candList.append( [ key, word, freq, preeditString, self.candStartIndex ] )
            else :
                flag = self.checkCache()
                self.candStartIndex = len( self.candList )
        if flag :
            return self.candList[index]
        else :
            return None
        #print candList
    def clean( self ) :
        self.spliter.clean()
        self.picker.set( [], [] )
        self.cache = [ [ 0, [], "" ] ]
        self.candList = []
        self.candCacheIndex = 0
        self.candStartIndex = 0

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

