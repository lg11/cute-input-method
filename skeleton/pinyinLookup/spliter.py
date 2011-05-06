from trietree import PinyinTree

class PinyinString () :
    def __init__( self, spliter, parent = None ) :
        self.spliter = spliter
        if parent :
            self.string = list( parent.string )
            self.length = parent.length
            self.start = parent.length
            #self.vaild = True
            #self.completeFlag = parent.completeFlag
        else :
            self.string = [ "" ]
            self.length = 0
            self.start = 0
            #self.vaild = True
            #self.completeFlag = True
    def append( self, code ) :
        newPinyinString = None
        prevStringTail = self.string[-1]
        newStringTail = self.string[-1] + code
        if self.spliter.pinyinTree.checkVaild( newStringTail ) :
            completeFlag = self.spliter.pinyinTree.checkComplete( prevStringTail )
            if completeFlag and code in self.spliter.beginCharSet :
                newPinyinString = PinyinString( self.spliter, self )
                newPinyinString.space()
                newPinyinString.append( code )
            self.string[-1] = newStringTail
            self.length += 1
        else :
            if code in self.spliter.beginCharSet :
                #self.completeFlag = self.completeFlag and pinyinTree.checkComplete( prevStringTail )
                self.string.append( code )
                self.length += 1
            else :
                #self.vaild = False
                pass
        return newPinyinString
    def pop( self ) :
        if self.length > 0 :
            if len( self.string[-1] ) > 1 :
                self.string[-1] = self.string[-1][:-1]
            else :
                self.string.pop()
            self.length -= 1
    def space( self ) :
        self.string.append( "" )
    def length( self ) :
        return len( self.string )
    def clear( self ) :
        self.string = [ "" ]
        #self.vaild = True
        #self.completeFlag = True
    def __str__( self ) :
        s = "'".join( self.string )
        return s

class PinyinSpliter () :
    def __init__( self ) :
        self.code = ""
        self.stack = []
        self.pinyinTree = PinyinTree()
        self.beginCharSet = set()
    def append( self, code ) :
        self.code += code 
        if len( self.stack ) > 0 :
            newStack = []
            for s in self.stack :
                #if s.vaild :
                if s.length >= len( self.code ) - 1 :
                    newPinyinString = s.append( code )
                    if newPinyinString != None :
                        newStack.append( newPinyinString )
            self.stack.extend( newStack )
        else :
            pinyinString = PinyinString( self )
            #print pinyinString
            pinyinString.append( code )
            #if pinyinString.vaild :
            if pinyinString.length >= len( self.code ) :
                self.stack.append( pinyinString )
    def pop( self ) :
        self.code = self.code[:-1]
        removeList = []
        for pinyinString in self.stack :
            if pinyinString.length > len( self.code ) :
                pinyinString.pop()
                if pinyinString.length <= pinyinString.start :
                    removeList.append( pinyinString )
        for pinyinString in removeList :
            self.stack.remove( pinyinString )
            #pass
    def clear( self ) :
        self.code = ""
        self.stack = []
    def __str__( self ) :
        s = "["
        for string in self.stack :
            #s = s + " \"" + str(string) + "\"" + ", " + str(string.completeFlag) + ";"
            #s = s + " \"" + str(string) + "\""
            s = s + " \"" + str(string) + "\"" + ", " + str(string.length) + ", " + str(string.start) + " ;"
        s = s + " ]"
        return s

if __name__ == "__main__" :
    import sys
    seeker = PinyinSpliter()
    
    print "done"
    while (1) :
        code = sys.stdin.readline()[:-1]
        for c in code :
            seeker.append( c )
            print seeker
        #print len( seeker.stack )
        while len( seeker.code ) > 0 :
            seeker.pop()
            print seeker
        #seeker.clear()

