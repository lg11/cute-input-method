#-!- coding=utf-8 -!-

if __name__ == "__main__" :
    import string
    chars = "abcdefghijklmnopqrstuvwxyz"
    nums  = "22233344455566677778889999"
    trans = string.maketrans( chars, nums )

    file = open( "utf8" )
    line = file.readline()
    while line :
        line = line.split()
        code = "".join( line[3:] ).translate( trans )
        pinyin = "'".join( line[3:] )
        hanzi = line[0]
        freq = line[1]
        print code, pinyin, hanzi, freq
        line = file.readline()
