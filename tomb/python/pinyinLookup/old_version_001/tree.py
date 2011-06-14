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
            return False
    return True

def __node_add_path( node, path ) :
    """
    add a new node in path under node
    if path existed, do nothing
    return node under path
    """
    for code in path :
        child = __node_seek_child( node, code )
        if child == None :
            node[1].append( [ code, [] ] )
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
        self.entry = [ "", [] ]

    def add( self, path ) :
        """
        add a new node in path
        if path existed, do nothing
        return node under path
        """
        return node_add_path( self.entry, path )

    def check( self, path ) :
        """
        seek path
        path is some code like "944"
        each code of path is "9", "4", "4"
        return seeked_path and node
        """
        return node_seek_path( self.entry, path )

if __name__ == "__main__" :
    tree = Tree()
    tree.addPath( "wo" )
    print tree.seekPath( "w" )
    print tree.seekPath( "wo" )
    print tree.seekPath( "woi" )
