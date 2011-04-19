def __node_seek_child( node, code ) :
    """
    seek child node with code, only seek one layer
    return node
    if not find, return None
    """
    for child in node[1] :
        if child[0] == code :
            return child
    return None

def __node_seek_path( node, path ) :
    """
    seek path under node
    return true if seeked
    else return false
    """
    for code in path :
        node = __node_seek_child( node, code )
        if node == None :
            break
    return node

def __node_add_path( node, path ) :
    """
    add a new node in path under node
    if path existed, do nothing
    return node under path
    """
    for code in path :
        child = __node_seek_child( node, code )
        if child == None :
            node[1].append( [ code, [], False ] )
            node = node[1][-1]
        else :
            node = child
    return node


node_add_path = __node_add_path
node_seek_path = __node_seek_path

class Tree() :
    def __init__( self ) :
        """
        node in code_map contain 2 element :
        1. code - a string
        2. child_node_list - like it's name
        """
        self.entry = [ "", [], False ]

    def addPath( self, path ) :
        """
        add a new node in path
        if path existed, do nothing
        return node under path
        """
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

class DictTree( Tree ) :
    def __init__( self ) :
        Tree.__init__( self )
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


if __name__ == "__main__" :
    tree = Tree()
    tree.addPath( "wo" )
    print tree.seekPath( "w" )
    print tree.seekPath( "wo" )
    print tree.seekPath( "woi" )
