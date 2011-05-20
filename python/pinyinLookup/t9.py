from lookup import PinyinLookup
from trietree import node_add_path, node_seek_path

import string

def __node_power_seek( node ) :
    current_stack = []
    deeper_stack = []
    result_list = []
    current_stack.extend( node[1] )
    while len( current_stack ) > 0 and len( result_list ) <= 0 :
        for child in current_stack :
            if child[2] :
                result_list.extend( child[2] )
            elif len( result_list ) <= 0 :
                deeper_stack.extend( child[1] )
        #print current_stack, deeper_stack, result_list
        current_stack = deeper_stack
    return result_list

node_power_seek = __node_power_seek

class T9Tree() :
    def __init__( self ) :
        self.entry = [ "", [], False ]
        chars = "abcdefghijklmnopqrstuvwxyz"
        nums  = "22233344455566677778889999"
        self.trans = string.maketrans( chars, nums )
    def addKey( self, key ) :
        t9Key = key.translate( self.trans )
        path = t9Key.replace( "'", "" )
        #print path, key
        node = node_add_path( self.entry, path )
        if node[2] :
            node[2].add( key )
        else :
            node[2] = set( [ key ] ) 
        return node
    def getKeys( self, path ) :
        node = node_seek_path( self.entry, path )
        if node == None :
            return -999, []
        else :
            if node[2] :
                return 0, list( node[2] )
            else :
                return -1, node_power_seek( node )
    def checkVaild( self, path ) :
        node = node_seek_path( self.entry, path )
        if node == None :
            return False
        else :
            return True

class T9Spliter () :
    def __init__( self ) :
        self.code = ""
    def append( self, code ) :
        self.code += code
    def pop( self ) :
        self.code = self.code[:-1]
    def clear( self ) :
        self.code = ""

class T9Fitter() :
    def __init__( self ) :
        self.dictTree = T9Tree()
    def fit( self, s ) :
        return self.dictTree.getKeys( s )

class T9PinyinLookup( PinyinLookup ) :
    def __init__( self ) :
        PinyinLookup.__init__( self )
        chars = "abcdefghijklmnopqrstuvwxyz"
        nums  = "22233344455566677778889999"
        self.trans = string.maketrans( chars, nums )
        self.spliter = T9Spliter()
        self.fitter = T9Fitter()
    def load( self, filePath ) :
        newKeys = self.dict.load( filePath )
        print "start build index"
        for key in newKeys :
            self.fitter.dictTree.addKey( key )
        print "built"
    def append( self, code ) :
        self.spliter.append( code )
        codeList = []
        fitPoint, keys = self.fitter.fit( self.spliter.code )
        for key in keys :
            codeList.append( self.spliter.code )
        self.picker.set( keys, codeList, True )
        cache = [ fitPoint, keys, codeList ] 
        self.cache.append( cache )
        self.candList = []
        self.candCacheIndex = len( self.cache ) - 1
        self.candStartIndex = 0


if __name__ == "__main__" :
    import sys
    lookup = T9PinyinLookup()
    lookup.load( "../../data/formated" )
    while (1) :
        code = sys.stdin.readline()[:-1]
        for c in code :
            #print lookup.cache[-1]
            lookup.append( c )
        #print lookup.cache[-1]
        for i in range( 1006 ) :
            cand = lookup.getCand( i )
            if cand :
                key, word, freq, i, j = cand
                print key, word, freq
        for c in code :
            lookup.pop()
            #print lookup.cache[-1]
        #lookup.clear()

