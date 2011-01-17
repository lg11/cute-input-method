#ifndef RECORD_H
#define RECORD_H

struct Record {
    char* hanzi ;
    double freq ;
    struct Record* next ;
} ;

struct RecordList {
    char* pinyin ;
    struct Record* head ;
} ;

#endif
