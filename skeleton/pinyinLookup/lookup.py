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
        self.cache = [ [ [], [] ] ]
    def load( self, filePath ) :
        print "start load"
        load_dict( self.dict, filePath )
        print "loaded"
        for key in self.dict.keys() :
            self.dictTree.addKey( key )
        print "built"
    def append( self, code ) :
        self.spliter.append( code )
        fullFitList = []
        partFitList = []
        for pinyinString in lookup.spliter.stack :
            hasFullFit, keys = lookup.dictTree.fit( pinyinString.string )
            if hasFullFit :
                fullFitList.extend( keys )
            else :
                partFitList.extend( keys )
        if len( fullFitList ) > 0 :
            self.picker.set( fullFitList )
        else :
            self.picker.set( partFitList )
        cache = [ fullFitList, partFitList ] 
        self.cache.append( cache )
    def pop( self ) :
        if len( self.cache ) > 1 :
            self.spliter.pop()
            self.cache = self.cache[:-1]
            cache = self.cache[-1]
            fullFitList = cache[0]
            partFitList = cache[1]
            if len( fullFitList ) > 0 :
                self.picker.set( fullFitList )
            else :
                self.picker.set( partFitList )
    def clean( self ) :
        self.spliter.clean()
        self.cache = [ [ [], [] ] ]

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
        #print lookup.picker.list
        print lookup.picker.pick()
        for c in code :
            lookup.pop()
            #print lookup.cache[-1]
        #lookup.clean()

