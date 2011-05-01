from tree import node_add_path, node_seek_path
from pinyin import pinyinTree

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

class DictTree() :
    def __init__( self ) :
        self.entry = [ "", [], False ]
    def addKey( self, key ) :
        path = key[0]
        i = key.find( "'" )
        while i > 0 :
            path = path + key[ i + 1 ]
            i = key.find( "'", i + 1 )
        #print key, path
        node = node_add_path( self.entry, path )
        if node[2] :
            node[2].add( key )
        else :
            node[2] = set( [ key ] ) 
        return node
    def getKeys( self, path ) :
        node = node_seek_path( self.entry, path )
        if node == None :
            return []
        else :
            if node[2] :
                return list( node[2] )
            else :
                return []
    def checkVaild( self, path ) :
        node = node_seek_path( self.entry, path )
        if node == None :
            return False
        else :
            return True
    def fit( self, pinyinString ) :
        path = ""
        for pinyin in pinyinString :
            path += pinyin[0]
        keys = self.getKeys( path )
        results = []
        #hasFullFit = False
        fitPoint = -999
        for key in keys :
            flag = True
            #fitFlag = True
            currentFitPoint = 0
            s = key.split( "'" )
            for i in range( len(s) ) :
                #print s[i], pinyinString[i]
                if s[i] == pinyinString[i] :
                    pass
                else :
                    currentFitPoint -= 1
                    l = len( pinyinString[i] )
                    if l > len( s[i] ) :
                        flag = False
                        break
                    elif pinyinTree.checkComplete( pinyinString[i])  and i < len(s) - 1 :
                        flag = False
                        break
                    else :
                        #print s[i][:l], pinyinString[i][:l]
                        if s[i][:l] != pinyinString[i][:l] :
                            flag = False
                            break
            #print currentFitPoint, key, flag
            if flag :
                if currentFitPoint >= 0 :
                    results = [ key ]
                    fitPoint = 0
                    #hasFullFit = True
                    break
                elif currentFitPoint > fitPoint :
                    results = [ key ]
                    fitPoint = currentFitPoint
                elif currentFitPoint == fitPoint :
                    results.append( key )
        #print "-----end-----"
        return fitPoint, results

class Dictionary() :
    def __init__( self ) :
        self.dict = dict()
        self.dictTree = DictTree()
        self.fit = self.dictTree.fit
        self.__getitem__ = self.dict.__getitem__
    def load( self, filePath ) :
        print "start load"
        load_dict( self.dict, filePath )
        print "loaded"
        for key in self.dict.keys() :
            self.dictTree.addKey( key )
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
