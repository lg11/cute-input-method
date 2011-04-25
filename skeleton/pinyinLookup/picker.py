
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
        for i in range( len( self.list ) ) :
            l = self.list[i]
            key = l[0]
            wordList = l[1]
            index = l[2]
            if index < len( wordList ) :
                record = wordList[index]
                word = record[0]
                freq = record[1]
                if freq > highestFreq :
                    highestIndex = i
                    highestFreq = freq
                #print key, word, freq
        if highestIndex >= 0 :
            l = self.list[highestIndex]
            key = l[0]
            wordList = l[1]
            index = l[2]
            record = wordList[index]
            word = record[0]
            freq = record[1]
            l[2] += 1
            return key, word, freq
        else :
            return None, None, 0


