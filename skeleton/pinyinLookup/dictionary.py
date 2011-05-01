from tree import PinyinTree, DictTree

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
        word = buffer[1].decode( "utf-8" )
        freq = float( buffer[2] )
        if pinyin in d :
            word_list = d[pinyin]
            insert_word( word_list, [ word, freq ] )
        else :
            d[pinyin] = [ [ word, freq ] ]
        #print pinyin, word, freq
        line = file.readline()

class Dictionary() :
    def __init__( self ) :
        self.dict = dict()

        self.pinyinSet = set()
        self.beginCharSet = set()
        self.pinyinTree = PinyinTree()

        self.dictTree = DictTree( self.pinyinTree )
        self.fit = self.dictTree.fit

        self.__getitem__ = self.dict.__getitem__
    def load( self, filePath ) :
        print "start load"
        load_dict( self.dict, filePath )
        print "loaded"
        for key in self.dict.keys() :
            if key.count( "'" ) <= 0 :
                self.pinyinSet.add( key )
            self.dictTree.addKey( key )
        for pinyin in self.pinyinSet :
            self.beginCharSet.add( pinyin[0] ) 
            self.pinyinTree.addPath( pinyin )
        print "built"
    def update( self, key, word, freq ) :
        pass

if __name__ == "__main__" :
    tree = DictTree()
    tree.addKey( "wo" )
    tree.addKey( "zhi'dao" )
    print tree.getKeys( "w" )
    print tree.getKeys( "zd" )
    print tree.getKeys( "j" )
