from trietree import DictTree

class Fitter() :
    def __init__( self ) :
        self.dictTree = DictTree()
        self.pinyinSet = set()
        self.extraSet = set( [ "m", "n", "a", "o", "e" ] )
    def fit( self, pinyinString ) :
        path = ""
        for pinyin in pinyinString :
            path += pinyin[0]
        keys = self.dictTree.getKeys( path )
        #print pinyinString, keys
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
                    elif pinyinString[i] in self.pinyinSet and i < len(s) - 1 :
                        if pinyinString[i] in self.extraSet :
                            if s[i][:l] != pinyinString[i][:l] :
                                flag = False
                                break
                        else :
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
