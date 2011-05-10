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
    new_keys = set()
    while line :
        #print line
        buffer = line[:-1].split()
        pinyin = buffer[0]
        word = buffer[1].decode( "utf-8" )
        freq = float( buffer[2] )
        if pinyin in d :
            word_list = d[pinyin]
            insert_word( word_list, [ word, freq ] )
        else :
            d[pinyin] = [ [ word, freq ] ]
            new_keys.add( pinyin )
        #print pinyin, word, freq
        line = file.readline()
    return new_keys

class Dictionary() :
    def __init__( self ) :
        self.dict = dict()

        self.pinyinSet = set()
        self.beginCharSet = set()
        #self.pinyinTree = PinyinTree()

        #self.dictTree = DictTree( self.pinyinTree )
        #self.fit = self.dictTree.fit
        self.__getitem__ = self.dict.__getitem__
        self.keys = self.dict.keys
    def load( self, filePath ) :
        print "start load"
        newKeys = load_dict( self.dict, filePath )
        print "loaded"
        return newKeys
    def update( self, key, word, freq ) :
        pass

if __name__ == "__main__" :
    tree = DictTree()
    tree.addKey( "wo" )
    tree.addKey( "zhi'dao" )
    print tree.getKeys( "w" )
    print tree.getKeys( "zd" )
    print tree.getKeys( "j" )
