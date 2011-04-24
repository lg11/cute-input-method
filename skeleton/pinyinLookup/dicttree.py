from tree import node_add_path, node_seek_path

def __node_find_key( node, key ) :
    l = node[2]
    flag = False
    i = 0
    while ( not flag ) and i < len( l ) :
        if key == l[i] :
            flag = True
        i = i + 1
    return flag

node_find_key = __node_find_key

class DictTree() :
    def __init__( self ) :
        self.entry = [ "", [], [] ]
    def addKey( self, key ) :
        path = key[0]
        i = key.find( "'" )
        while i > 0 :
            path = path + key[ i + 1 ]
            i = key.find( "'", i + 1 )
        #print key, path
        node = node_add_path( self.entry, path )
        if node[2] :
            if not node_find_key( node, key ) :
                node[2].append( key )
        else :
            node[2] = [ key ]
        return node
    def getKeys( self, path ) :
        node = node_seek_path( self.entry, path )
        if node == None :
            return []
        else :
            return node[2]
    def checkVaild( self, path ) :
        node = node_seek_path( self.entry, path )
        if node == None :
            return False
        else :
            return True

if __name__ == "__main__" :
    tree = DictTree()
    tree.addKey( "wo" )
    tree.addKey( "zhi'dao" )
    print tree.getKeys( "w" )
    print tree.getKeys( "zd" )
    print tree.getKeys( "j" )
