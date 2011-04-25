from tree import node_add_path, node_seek_path
from pinyin import pinyinTree

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

if __name__ == "__main__" :
    tree = DictTree()
    tree.addKey( "wo" )
    tree.addKey( "zhi'dao" )
    print tree.getKeys( "w" )
    print tree.getKeys( "zd" )
    print tree.getKeys( "j" )
