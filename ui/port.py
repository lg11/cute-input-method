#-!- coding=utf-8 -!-

import backend

import string
import os

class Selected() :
    def __init__( self, code, fullCode, pinyin, hanzi ) :
        self.code = code
        self.fullCode = fullCode
        self.pinyin = pinyin.split( "'" )
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
    def push( self, code, fullCode, pinyin, hanzi ) :
        self.stack.append( Selected( code, fullCode, pinyin, hanzi ) )
    def pop( self ) :
        code = ""
        if len( self.stack ) > 0 :
            selected = self.stack[-1]
            if len( selected.code ) > 0 :
                code = selected.pop()
            else :
                self.stack.pop()
                code = self.pop()
        return code
    def get( self ) :
        code = ""
        pinyin = []
        hanzi = []
        for selected in self.stack :
            code = code + selected.fullCode
            pinyin.extend( selected.pinyin )
            hanzi.extend( selected.hanzi )
        pinyin = "'".join( pinyin )
        hanzi = "".join( hanzi )
        return code, pinyin, hanzi
    def clear( self ) :
        self.stack = []

class Backend() :
    CAND_LENGTH = 6
    CODEMAP_PATH = "../data/formated"
    if not os.path.exists( CODEMAP_PATH ) :
        CODEMAP_PATH = "/opt/cim/data/formated"
    CHAR = "abcdefghijklmnopqrstuvwxyz"
    CODE  = "22233344455566677778889999"
    TRANS = string.maketrans( CHAR, CODE )
    def __init__( self ) :
        backend.load( self.CODEMAP_PATH )
        self.vailed_code = ""
        self.invailed_code = ""
        self.page_index = 0
        self.cand_list = []
        self.selected = SelectedStack()
        #self.get_pinyin_list = None
    def get_pinyin_list( self ) :
        pinyin_list = []
        i = 0
        r = backend.getPinyin( i )
        while r :
            pinyin_list.append( r.decode( "utf-8" ) )
            i = i + 1
            r = backend.getPinyin( i )
        return pinyin_list
    def set_filter( self, pinyin ) :
        self.page_index = 0
        #backend.setPinyin( pinyin.encode( "utf-8" ) )
        backend.setPinyin( pinyin )
        #self.cache.set_filter( pinyin )
    def set_code( self, code ) :
        self.clearCode()
        for c in code :
            self.append( c )
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
                self.vailed_code = self.vailed_code + code
            self.page_index = 0
    def pop( self ) :
        code = ""
        if len( self.invailed_code ) > 0 :
            code = self.invailed_code[-1]
            self.invailed_code = self.invailed_code[:-1]
        elif len( self.vailed_code ) > 0 :
            code = self.vailed_code[-1]
            self.vailed_code = self.vailed_code[:-1]
            backend.pop()
            self.page_index = 0
        return code
    def gen_cand_list( self ) :
        start_index = self.page_index * self.CAND_LENGTH
        self.cand_list = []
        for i in range( 6 ) :
            r = backend.get( start_index + i )
            if r :
                pinyin = r[0]
                code = pinyin.replace( "'", "" )
                code = code.translate( self.TRANS )
                hanzi = r[1].decode( "utf-8" )
                self.cand_list.append( [ code, pinyin, hanzi ] )
    def clearCode( self ) :
        self.page_index = 0
        self.set_filter( "" )
        self.invailed_code = ""
        self.vailed_code = ""
        backend.clear()
    def commit( self ) :
        self.clearCode()
        self.selected.clear()
    def code( self ) :
        return self.vailed_code + self.invailed_code
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
        if index < len( self.cand_list ) :
            r = self.cand_list[index]
            code = r[0]
            pinyin = r[1]
            hanzi = r[2]
            remained_code = ""
            codeLength = len( code )
            if len( self.vailed_code ) > codeLength :
                remained_code = self.vailed_code[codeLength:]
                self.vailed_code = self.vailed_code[:codeLength]
            #print "select", code, pinyin, hanzi
            self.selected.push( self.vailed_code, code, pinyin, hanzi )
            remained_code = remained_code + self.invailed_code
            self.set_code( remained_code )
    def page_next( self ) :
        page_index = self.page_index + 1
        r = backend.get( page_index * self.CAND_LENGTH )
        if r != None :
            self.page_index = page_index
    def page_prev( self ) :
        if self.page_index > 0 :
            self.page_index = self.page_index - 1
            self.gen_cand_list()

