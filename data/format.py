#-!- coding=utf-8 -!-

def convert( value, src_low, src_up, dest_low, dest_up ) :
    new_value = ( value * ( dest_up - dest_low ) ) / ( src_up - src_low )
    #print value, src_low, src_up
    #print new_value, dest_low, dest_up
    return new_value
    #pass

if __name__ == "__main__" :
    import string
    import os
    chars = "abcdefghijklmnopqrstuvwxyz"
    nums  = "22233344455566677778889999"
    trans = string.maketrans( chars, nums )
    
    os.system( "cat utf8 | awk '{ print $2 }' | sort -n > cache" )
    p = os.popen( "tail -1 cache" )
    highest_freq = float( p.read()[:-1] )
    p.close()
    p2 = os.popen( "head -1 cache" )
    lowerest_freq = float( p2.read()[:-1] )
    p2.close()
    #print "start", highest_freq, lowerest_freq, "end"

    #convert( 86, 0, 100, 0.1, 0.9 )
    #convert( 26, 0, 100, 0.1, 0.9 )
    #convert( 50, 0, 100, 0.1, 0.9 )
    
    file = open( "utf8" )
    line = file.readline()
    while line :
        line = line.split()
        code = "".join( line[3:] ).translate( trans )
        pinyin = "'".join( line[3:] )
        hanzi = line[0]
        freq = float( line[1] )
        freq = convert( freq, lowerest_freq, highest_freq, 0.1, 0.9 )
        #print code, pinyin, hanzi, freq
        print pinyin, hanzi, freq
        line = file.readline()
