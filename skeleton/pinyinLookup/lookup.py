from dicttree import DictTree
from spliter import PinyinSpliter
from picker import Picker

def insert_word( word_list, word ) :
    i = 0 
    while i < len( word_list ) :
        if word[1] > word_list[i][1] :
            break
        i = i + 1
    word_list.insert( i, word )
        
def load_dict( d, file_path ) :
    file = open( file_path )
    line = file.readline()
    while line :
        buffer = line[:-1].split()
        pinyin = buffer[0]
        word = buffer[1]
        freq = float( buffer[2] )
        if pinyin in d :
            word_list = d[pinyin]
            insert_word( word_list, [ word, freq ] )
        else :
            d[pinyin] = [ [ word, freq ] ]
        #print pinyin, word, freq
        line = file.readline()

class PinyinLookup() :
    def __init__( self ) :
        self.dict = dict()
        self.dictTree = DictTree()
        self.spliter = PinyinSpliter()
        self.picker = Picker( self.dict )
        self.cache = [ [ 0, 0, [] ] ]
        self.candList = []
    def load( self, filePath ) :
        print "start load"
        load_dict( self.dict, filePath )
        print "loaded"
        for key in self.dict.keys() :
            self.dictTree.addKey( key )
        print "built"
    def append( self, code ) :
        self.spliter.append( code )
        fitList = []
        fitPoint = -999
        unfitPos = -999
        for pinyinString in lookup.spliter.stack :
            currentFitPoint, currentUnfitPos, keys = lookup.dictTree.fit( pinyinString.string )
            if currentFitPoint > fitPoint :
                fitList = []
                fitList.extend( keys )
                fitPoint = currentFitPoint
                unfitPos = currentUnfitPos
            elif currentFitPoint == fitPoint :
                if currentUnfitPos > unfitPos :
                    fitList = []
                    fitList.extend( keys )
                    unfitPos = currentUnfitPos
                elif currentUnfitPos == unfitPos :
                    fitList.extend( keys )
        self.picker.set( fitList )
        cache = [ fitPoint, unfitPos, fitList ] 
        self.cache.append( cache )
        self.candList = []
    def pop( self ) :
        if len( self.cache ) > 1 :
            self.spliter.pop()
            self.cache = self.cache[:-1]
            cache = self.cache[-1]
            fitList = cache[2]
            self.picker.set( fitList )
            self.candList = []
    def getCand( self, index ) :
        flag = True
        while flag and len( self.candList ) <= index :
            key, word, freq = lookup.picker.pick()
            if key :
                self.candList.append( [ key, word, freq ] )
            else :
                flag = False
        if flag :
            return self.candList[index]
        else :
            return None
    def clean( self ) :
        self.spliter.clean()
        self.cache = [ [ 0, 0, [] ] ]
        self.candList = []

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

