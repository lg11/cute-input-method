
class Picker() :
    def __init__( self, d ) :
        self.dict = d
        self.list = []
    def set( self, keys ) :
        self.list = []
        for key in keys :
            wordList = self.dict[key]
            self.list.append( [ key, wordList, 0 ] )
    def pick( self ) :
        highestFreq = -1
        highestIndex = -1
        for l in self.list :
            key = l[0]
            wordList = l[1]
            index = l[2]
            if index < len( wordList ) :
                record = wordList[index]
                word = record[0]
                freq = record[1]
                print key, word, freq


