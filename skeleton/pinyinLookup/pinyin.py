import tree

pinyinSet = set( \
    [ \
    "a" , \
    "ai" , \
    "an" , \
    "ang" , \
    "ao" , \
    "ba" , \
    "bai" , \
    "ban" , \
    "bang" , \
    "bao" , \
    "bei" , \
    "ben" , \
    "beng" , \
    "bi" , \
    "bian" , \
    "biao" , \
    "bie" , \
    "bin" , \
    "bing" , \
    "bo" , \
    "bu" , \
    "ca" , \
    "cai" , \
    "can" , \
    "cang" , \
    "cao" , \
    "ce" , \
    "cen" , \
    "ceng" , \
    "cha" , \
    "chai" , \
    "chan" , \
    "chang" , \
    "chao" , \
    "che" , \
    "chen" , \
    "cheng" , \
    "chi" , \
    "chong" , \
    "chou" , \
    "chu" , \
    "chua" , \
    "chuai" , \
    "chuan" , \
    "chuang" , \
    "chui" , \
    "chun" , \
    "chuo" , \
    "ci" , \
    "cong" , \
    "cou" , \
    "cu" , \
    "cuan" , \
    "cui" , \
    "cun" , \
    "cuo" , \
    "da" , \
    "dai" , \
    "dan" , \
    "dang" , \
    "dao" , \
    "de" , \
    "dei" , \
    "den" , \
    "deng" , \
    "di" , \
    "dia" , \
    "dian" , \
    "diao" , \
    "die" , \
    "ding" , \
    "diu" , \
    "dong" , \
    "dou" , \
    "du" , \
    "duan" , \
    "dui" , \
    "dun" , \
    "duo" , \
    "e" , \
    "ei" , \
    "en" , \
    "eng" , \
    "er" , \
    "fa" , \
    "fan" , \
    "fang" , \
    "fei" , \
    "fen" , \
    "feng" , \
    "fiao" , \
    "fo" , \
    "fou" , \
    "fu" , \
    "ga" , \
    "gai" , \
    "gan" , \
    "gang" , \
    "gao" , \
    "ge" , \
    "gei" , \
    "gen" , \
    "geng" , \
    "gong" , \
    "gou" , \
    "gu" , \
    "gua" , \
    "guai" , \
    "guan" , \
    "guang" , \
    "gui" , \
    "gun" , \
    "guo" , \
    "ha" , \
    "hai" , \
    "han" , \
    "hang" , \
    "hao" , \
    "he" , \
    "hei" , \
    "hen" , \
    "heng" , \
    "hm" , \
    "hng" , \
    "hong" , \
    "hou" , \
    "hu" , \
    "hua" , \
    "huai" , \
    "huan" , \
    "huang" , \
    "hui" , \
    "hun" , \
    "huo" , \
    "ji" , \
    "jia" , \
    "jian" , \
    "jiang" , \
    "jiao" , \
    "jie" , \
    "jin" , \
    "jing" , \
    "jiong" , \
    "jiu" , \
    "ju" , \
    "juan" , \
    "jue" , \
    "jun" , \
    "ka" , \
    "kai" , \
    "kan" , \
    "kang" , \
    "kao" , \
    "ke" , \
    "kei" , \
    "ken" , \
    "keng" , \
    "kong" , \
    "kou" , \
    "ku" , \
    "kua" , \
    "kuai" , \
    "kuan" , \
    "kuang" , \
    "kui" , \
    "kun" , \
    "kuo" , \
    "la" , \
    "lai" , \
    "lan" , \
    "lang" , \
    "lao" , \
    "le" , \
    "lei" , \
    "leng" , \
    "li" , \
    "lia" , \
    "lian" , \
    "liang" , \
    "liao" , \
    "lie" , \
    "lin" , \
    "ling" , \
    "liu" , \
    "lo" , \
    "long" , \
    "lou" , \
    "lu" , \
    "luan" , \
    "lue" , \
    "lun" , \
    "luo" , \
    "lv" , \
    "m" , \
    "ma" , \
    "mai" , \
    "man" , \
    "mang" , \
    "mao" , \
    "me" , \
    "mei" , \
    "men" , \
    "meng" , \
    "mi" , \
    "mian" , \
    "miao" , \
    "mie" , \
    "min" , \
    "ming" , \
    "miu" , \
    "mo" , \
    "mou" , \
    "mu" , \
    "n" , \
    "na" , \
    "nai" , \
    "nan" , \
    "nang" , \
    "nao" , \
    "ne" , \
    "nei" , \
    "nen" , \
    "neng" , \
    "ng" , \
    "ni" , \
    "nian" , \
    "niang" , \
    "niao" , \
    "nie" , \
    "nin" , \
    "ning" , \
    "niu" , \
    "nong" , \
    "nou" , \
    "nu" , \
    "nuan" , \
    "nue" , \
    "nuo" , \
    "nv" , \
    "o" , \
    "ou" , \
    "pa" , \
    "pai" , \
    "pan" , \
    "pang" , \
    "pao" , \
    "pei" , \
    "pen" , \
    "peng" , \
    "pi" , \
    "pian" , \
    "piao" , \
    "pie" , \
    "pin" , \
    "ping" , \
    "po" , \
    "pou" , \
    "pu" , \
    "qi" , \
    "qia" , \
    "qian" , \
    "qiang" , \
    "qiao" , \
    "qie" , \
    "qin" , \
    "qing" , \
    "qiong" , \
    "qiu" , \
    "qu" , \
    "quan" , \
    "que" , \
    "qun" , \
    "ran" , \
    "rang" , \
    "rao" , \
    "re" , \
    "ren" , \
    "reng" , \
    "ri" , \
    "rong" , \
    "rou" , \
    "ru" , \
    "ruan" , \
    "rui" , \
    "run" , \
    "ruo" , \
    "sa" , \
    "sai" , \
    "san" , \
    "sang" , \
    "sao" , \
    "se" , \
    "sen" , \
    "seng" , \
    "sha" , \
    "shai" , \
    "shan" , \
    "shang" , \
    "shao" , \
    "she" , \
    "shei" , \
    "shen" , \
    "sheng" , \
    "shi" , \
    "shou" , \
    "shu" , \
    "shua" , \
    "shuai" , \
    "shuan" , \
    "shuang" , \
    "shui" , \
    "shun" , \
    "shuo" , \
    "si" , \
    "song" , \
    "sou" , \
    "su" , \
    "suan" , \
    "sui" , \
    "sun" , \
    "suo" , \
    "ta" , \
    "tai" , \
    "tan" , \
    "tang" , \
    "tao" , \
    "te" , \
    "tei" , \
    "teng" , \
    "ti" , \
    "tian" , \
    "tiao" , \
    "tie" , \
    "ting" , \
    "tong" , \
    "tou" , \
    "tu" , \
    "tuan" , \
    "tui" , \
    "tun" , \
    "tuo" , \
    "wa" , \
    "wai" , \
    "wan" , \
    "wang" , \
    "wei" , \
    "wen" , \
    "weng" , \
    "wo" , \
    "wu" , \
    "xi" , \
    "xia" , \
    "xian" , \
    "xiang" , \
    "xiao" , \
    "xie" , \
    "xin" , \
    "xing" , \
    "xiong" , \
    "xiu" , \
    "xu" , \
    "xuan" , \
    "xue" , \
    "xun" , \
    "ya" , \
    "yan" , \
    "yang" , \
    "yao" , \
    "ye" , \
    "yi" , \
    "yin" , \
    "ying" , \
    "yo" , \
    "yong" , \
    "you" , \
    "yu" , \
    "yuan" , \
    "yue" , \
    "yun" , \
    "za" , \
    "zai" , \
    "zan" , \
    "zang" , \
    "zao" , \
    "ze" , \
    "zei" , \
    "zen" , \
    "zeng" , \
    "zha" , \
    "zhai" , \
    "zhan" , \
    "zhang" , \
    "zhao" , \
    "zhe" , \
    "zhei" , \
    "zhen" , \
    "zheng" , \
    "zhi" , \
    "zhong" , \
    "zhou" , \
    "zhu" , \
    "zhua" , \
    "zhuai" , \
    "zhuan" , \
    "zhuang" , \
    "zhui" , \
    "zhun" , \
    "zhuo" , \
    "zi" , \
    "zong" , \
    "zou" , \
    "zu" , \
    "zuan" , \
    "zui" , \
    "zun" , \
    "zuo" , \
    ] \
    )

beginCharSet = set()
pinyinTree = tree.Tree()

for pinyin in pinyinSet :
    beginCharSet.add( pinyin[0] ) 
    pinyinTree.add( pinyin )

#print len( beginCharSet )
#for beginChar in beginCharSet :
    #print beginChar

class PinyinString () :
    def __init__( self, string = [ "" ] ) :
        self.string = string
        self.vaild = True
    def append( self, code ) :
        lastString = self.string[-1] + code
        #print "start"
        #print self.string
        if pinyinTree.check( lastString ) :
            self.string[-1] = lastString
            #print lastString
        else :
            if code in beginCharSet :
                self.string.append( code )
            else :
                self.vaild = False
    def space( self ) :
        self.string.append( "" )
    def length( self ) :
        return len( self.string )
    def clear( self ) :
        self.string = [ "" ]
        self.vaild = True
    def __str__( self ) :
        s = "'".join( self.string )
        return s



class AdvSeeker () :
    def __init__( self ) :
        self.code = ""
        self.stack = []
    def append( self, code ) :
        self.code = self.code + code 
        if len( self.stack ) > 0 :
            newString = []
            for s in self.stack :
                if s.vaild :
                    if code in beginCharSet :
                        prevList = list( s.string )
                        prevLength = s.length()
                        s.append( code )
                        if s.length() == prevLength :
                            pinyinString = PinyinString( prevList )
                            pinyinString.space()
                            pinyinString.append( code )
                            newString.append( pinyinString )
                    else :
                        s.append( code )
            self.stack.extend( newString )
        else :
            pinyinString = PinyinString( [""] )
            #print pinyinString
            pinyinString.append( code )
            if pinyinString.vaild :
                self.stack.append( pinyinString )
    def clear( self ) :
        self.code = ""
        self.stack = []
    def __str__( self ) :
        s = "["
        for string in self.stack :
            s = s + " \"" + str(string) + "\""
        s = s + " ]"
        return s
        
if __name__ == "__main__" :
    import sys
    seeker = AdvSeeker()
    
    while (1) :
        code = sys.stdin.readline()[:-1]
        for c in code :
            seeker.append( c )
        print seeker
        print len( seeker.stack )
        seeker.clear()

