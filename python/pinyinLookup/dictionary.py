#-!- coding=utf-8 -!-

def find_word( word_list, word ) :
    i = 0 
    while i < len( word_list ) :
        if word == word_list[i][0] :
            return i
        i = i + 1
    return -1

def insert_record( word_list, record ) :
    i = 0 
    while i < len( word_list ) :
        if record[1] > word_list[i][1] :
            break
        i = i + 1
    word_list.insert( i, record )
        
def load_dict( d, file_path ) :
    flag = len( d ) > 0
    file = open( file_path )
    line = file.readline()
    new_keys = set()
    highestFreq = -1
    while line :
        #print line
        buffer = line[:-1].split()
        if len( buffer ) == 3 :
            pinyin = buffer[0]
            word = buffer[1].decode( "utf-8" )
            freq = float( buffer[2] )
            if freq > highestFreq :
                highestFreq = freq
            if pinyin in d :
                word_list = d[pinyin]
                if flag :
                    i = find_word( word_list, word )
                    if i < 0 :
                        insert_record( word_list, [ word, freq ] )
                    else :
                        record = word_list.pop( i )
                        record[1] = freq
                        insert_record( word_list, record )
                else :
                    insert_record( word_list, [ word, freq ] )
            else :
                d[pinyin] = [ [ word, freq ] ]
                new_keys.add( pinyin )
            #print pinyin, word, freq
        line = file.readline()
    return new_keys, highestFreq

class Dictionary() :
    def __init__( self ) :
        self.dict = dict()

        self.pinyinSet = set()
        self.beginCharSet = set()
        #self.pinyinTree = PinyinTree()

        #self.dictTree = DictTree( self.pinyinTree )
        #self.fit = self.dictTree.fit
        self.__getitem__ = self.dict.__getitem__
        self.keys = self.dict.keys
        self.highestFreq = -1
        #记录最高词频，给新词一个合理的初始词频，目前取最高词频的一半
        #self.newRecordQueue = [ [], [], [] ]
        self.logFlag = False
        self.logFile = None
    def logOn( self ) :
        self.logFlag = True
        self.logFile = open( "/home/user/.config/mcip/userdict.log", "a" )
        #print "log on"
    def logOff( self ) :
        self.logFlag = False
        if self.logFile :
            self.logFile.close()
            self.logFile = None
    def load( self, filePath ) :
        print "start load"
        newKeys, highestFreq = load_dict( self.dict, filePath )
        print "loaded"
        if highestFreq > self.highestFreq :
            self.highestFreq = highestFreq
        return newKeys
    def update( self, key, word, freq ) :
        newKey = None
        record = None
        if key in self.dict :
            wordList = self[key]
            i = find_word( wordList, word )
            if i == 0 :
                record = wordList[0]
                if freq <= record[1] :
                    freq = record[1] + 1
                else :
                    freq += 1
                record[1] = freq
            elif i > 0 :
                if freq < 0 :
                    freq = wordList[i/2][1]
                elif freq <= wordList[i][1] :
                    freq = wordList[i][1] + 1
                else :
                    freq = freq + 1
                record = wordList.pop(i)
                record[1] = freq
                insert_record( wordList, record )
            else :
                if freq < 0 :
                    index = 3
                    if index < len( wordList ) - 1 :
                        freq = ( wordList[index][1] + wordList[index+1][1] ) / 2
                    elif len( wordList ) < 4 :
                        index = len( wordList ) - 1
                        freq = wordList[index][1] - 1
                    else :
                        freq = wordList[index][1] - 1
                    #print index, freq
                insert_record( wordList, [ word, freq ] )
            if freq > self.highestFreq :
                self.highestFreq = freq
        else :
            if freq < 0 :
                freq = self.highestFreq / 2
            self.dict[key] = [ [ word, freq ] ]
            newKey = key
        r = [ key, word.encode( "utf-8" ), str( freq ) ]
        l = " ".join( r )
        if self.logFile :
            self.logFile.write( l )
            self.logFile.write( "\n" )
            self.logFile.flush()
            #print "log", l
        return newKey

if __name__ == "__main__" :
    tree = DictTree()
    tree.addKey( "wo" )
    tree.addKey( "zhi'dao" )
    print tree.getKeys( "w" )
    print tree.getKeys( "zd" )
    print tree.getKeys( "j" )
