#ifndef LOOKUP_H
#define LOOKUP_H

#include "dict.h"
#include "trie.h"

struct CandidateItem {
    QString key ;
    QString word ;
    qreal freq ;
    inline CandidateItem( const QString& key = "" , const QString& word = "" , qreal freq = 0 ) : key(key), word(word) { this->freq = freq ; }
} ;

struct QueryResult {
    bool vaild ;
    QVector<QString> keys ;
    QVector<WordRecordList*> wordRecordLists ;
    inline QueryResult( bool vaild = false ) : vaild(vaild), keys(), wordRecordLists() {}
    inline QueryResult( bool vaild, const QVector<QString>& keys, const QVector<WordRecordList*>& wordRecordLists ) : vaild(vaild), keys(keys), wordRecordLists(wordRecordLists) {}
} ;

class QueryCache {
public :
    QVector<QueryResult> cache ;
    int cacheLength ;
    inline QueryCache() : cache(){ this->cacheLength = 0 ; }
    inline void checkSize() {
        if ( this->cacheLength >= this->cache.size() )
            this->cache.resize( this->cacheLength - this->cache.size() + 16 ) ;
    }
    inline void push( const QueryResult& result ) {
        this->checkSize() ;
        this->cache[this->cacheLength] = result ;
        this->cacheLength++ ;
    }
    inline void pop() {
        if ( this->cacheLength > 0 )
            this->cacheLength-- ;
    }
    inline void clear() { this->cacheLength = 0 ; }
} ;

//class Picker ;

class CandidateList {
public :
    QueryCache* cache ;
    QVector<CandidateItem> list ;
    int listLength ;
    inline CandidateList( QueryCache* cache ) : cache(cache), list(), listLength(0) {} ;
    inline void checkSize() {
        if ( this->listLength >= this->list.size() )
            this->list.resize( this->listLength - this->list.size() + 16 ) ;
    }
    inline void clear() {
    }
    inline int gen( int length ) {
    }
    //inline 
} ;

//class Lookup {
//public :
    //QStack<QChar> code ;
    //QVector<CandidateItem> candidate ;
    //Lookup() : code(), candidate() {}
    //virtual pushCode( QChar code ) = 0 ;
    //virtual popCode() = 0 ;
    //virtual getCandidate( int start, int length ) = 0 ;
//} ;


class NumberLookup {
public :
    QString code ;
    QVector<CandidateItem> candidate ;
    NumberLookup() : code(), candidate() {}
    inline void pushCode( QChar code ) { this->code.append( code ) ; } ;
    inline void popCode() ;
    int genCandidate( int length ) ;
} ;
#endif
