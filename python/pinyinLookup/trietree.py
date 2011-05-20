def __node_seek_child( node, code ) :
    for child in node[1] :
        if child[0] == code :
            return child
    return None

def __node_seek_path( node, path ) :
    for code in path :
        node = __node_seek_child( node, code )
        if node == None :
            break
    return node

def __node_add_path( node, path ) :
    for code in path :
        child = __node_seek_child( node, code )
        if child == None :
            node[1].append( [ code, [], False ] )
            node = node[1][-1]
        else :
            node = child
    return node

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

node_add_path = __node_add_path
node_seek_path = __node_seek_path
node_power_seek = __node_power_seek

class PinyinTree() :
    def __init__( self ) :
        self.entry = [ "", [], False ]

    def addPath( self, path ) :
        node = node_add_path( self.entry, path )
        node[2] = True
        return node

    def checkComplete( self, path ) :
        node = node_seek_path( self.entry, path )
        if node == None :
            return False
        else :
            return node[2]

    def checkVaild( self, path ) :
        node = node_seek_path( self.entry, path )
        if node == None :
            return False
        else :
            return True

class DictTree() :
    def __init__( self ) :
        self.entry = [ "", [], False ]
        #self.pinyinTree = pinyinTree
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


if __name__ == "__main__" :
    tree = Tree()
    tree.addPath( "wo" )
    print tree.checkComplete( "w" )
    print tree.checkComplete( "wo" )
    print tree.checkComplete( "woi" )
