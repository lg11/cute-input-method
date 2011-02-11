#-!- coding=utf-8 -!-

import backend

import string

class Selected() :
    CHAR = "abcdefghijklmnopqrstuvwxyz"
    CODE  = "22233344455566677778889999"

    TRANS = string.maketrans( CHAR, CODE )
    def __init__( self, code, pinyin, hanzi ) :
        self.code = code
        self.pinyin = pinyin.split( "'" )
        self.fullCode = "".join( self.pinyin )
        self.fullCode = self.fullCode.translate( t )
        self.hanzi = []
        for zi in hanzi :
            self.hanzi.append( zi )
    def pop( self ) :
        code = ""
        if len( self.pinyin ) > 0 :
            self.hanzi.pop()
            pinyin = self.pinyin.pop()
            length = len( pinyin )
            self.fullCode = self.fullCode[:-length]
            length = len( self.fullCode )
            if len( self.code ) > length :
                code = self.code[length:]
        return code
    def get( self ) :
        return self.fullCode, self.pinyin, self.hanzi

class SelectedStack() :
    def __init__( self ) :
        self.stack = []
    def push( self, code, pinyin, hanzi ) :
        self.stack.append( Selected( code, pinyin, hanzi ) )
    def pop( self ) :
        code = ""
        if len( self.code_stack ) > 0 :
            top = self.stack.top()
            if len( top.code ) > 0 :
                code = top.pop()
            else :
                self.stack.pop()
                code = self.pop()
        return code
    def get( self ) :
        code = ""
        pinyin = []
        hanzi = ""
        for selected in self.stack :
            code = code + selected.fullCode
            pinyin.extend( selected.pinyin )
            hanzi = hanzi + selected.hanzi
        pinyin = "'".join( pinyin )
        return code, pinyin, hanzi
    def clear( self ) :
        self.stack = []

class Backend() :
    CAND_LENGTH = 6
    CODEMAP_PATH = "../data/formated"
    def __init__( self ) :
        backend.load( self.CODEMAP_PATH )
        self.code = ""
        self.invailed_code = ""
        self.page_index = 0
        self.cand_list = []
        self.selected = SelectedStack()
        self.get_pinyin_list = None
    def set_filter( self, pinyin ) :
        self.page_index = 0
        #self.cache.set_filter( pinyin )
    def set_code( self, code ) :
        #vaild_code = self.cache.set( code )
        self.invailed_code = code[ len( vaild_code ) : ]
        self.page_index = 0
    def append( self, code ) :
        if len( self.invailed_code ) > 0 :
            self.invailed_code = self.invailed_code + code
        else :
            backend.append( code )
            flag = backend.get( 0 )
            if flag == None :
                backend.pop()
                self.invailed_code = self.invailed_code + code
            else :
                self.code = self.code + code
            self.page_index = 0
    def pop( self ) :
        code = ""
        if len( self.invailed_code ) > 0 :
            code = self.invailed_code[-1]
            self.invailed_code = self.invailed_code[:-1]
        elif len( self.code ) > 0 :
            code = self.code[-1]
            self.code = self.code[:-1]
            backend.pop()
            self.page_index = 0
        return code
    def gen_cand_list( self ) :
        start_index = self.page_index * self.CAND_LENGTH
        self.cand_list = []
        for i in range( 6 ) :
            r = backend.get( start_index + i )
            if r :
                code = ""
                pinyin = r[0]
                hanzi = r[1].decode( "utf-8" )
                self.cand_list.append( [ code, pinyin, hanzi ] )
    def commit( self ) :
        self.invailed_code = ""
        self.code = ""
        backend.clear()
        self.selected.clear()
    def code( self ) :
        return self.code + self.invailed_code
    def get_selected( self ) :
        code, pinyin, hanzi = self.selected.get()
        return hanzi
    def deselect( self ) :
        code = self.selected.pop()
        if len( code ) > 0 :
            #print code, self.code()
            code = code + self.code()
            self.set_code( code )
        return code
    def select( self, index ) :
        index = self.CAND_LENGTH * self.page_index + index
        remained_code, code, cache, cand_index = self.cache.select( index )
        self.selected.push( code, cache, cand_index )
        remained_code = remained_code + self.invailed_code
        self.set_code( remained_code )
    def page_next( self ) :
        page_index = self.page_index + 1
        start_index = page_index * self.CAND_LENGTH
        cand_length = self.cache.gen_cand( start_index + self.CAND_LENGTH )
        if cand_length > start_index :
            self.page_index = page_index
    def page_prev( self ) :
        if self.page_index > 0 :
            self.page_index = self.page_index - 1

