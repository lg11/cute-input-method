
def prePhrase( file_path ) :
    f = open( file_path, "r" )
    line = f.readline()
    prevKey = ""
    prevWord = ""
    while line :
        line = line.split()
        if len( line ) == 3 :
            key, word, freq = line
            if prevKey == key and prevWord == word :
                pass
            else :
                prevKey = key
                prevWord = word
                print key, word, freq
        line = f.readline()

if __name__ == "__main__" :
    import sys
    prePhrase( sys.argv[1] )
