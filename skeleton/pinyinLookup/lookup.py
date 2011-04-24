from dicttree import DictTree
from spliter import PinyinSpliter

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
    def load( self, filePath ) :
        print "start load"
        load_dict( self.dict, filePath )
        print "loaded"
        for key in self.dict.keys() :
            self.dictTree.addKey( key )
        print "built"
    #def append( self, code ) :


if __name__ == "__main__" :
    import sys
    lookup = PinyinLookup()
    lookup.load( "../../data/formated" )
    while (1) :
        code = sys.stdin.readline()[:-1]
        keys = lookup.dictTree.getKeys( code )
        print keys
        print len( keys )

