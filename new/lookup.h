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

struct LookupResult {
    bool vaild ;
    QVector<QString> keys ;
    QVector<WordRecordList*> wordRecordLists ;
    inline LookupResult( bool vaild = false ) : vaild(vaild), keys(), wordRecordLists() {}
    inline LookupResult( bool vaild, const QVector<QString>& keys, const QVector<WordRecordList*>& wordRecordLists ) : vaild(vaild), keys(keys), wordRecordLists(wordRecordLists) {}
} ;

class LookupCache {
public :
    QVector<LookupResult> cache ;
    //int cacheLength ;
    inline LookupCache() : cache(){}
    inline void checkSize( int size ) {
        if ( size > this->cache.size() )
            this->cache.resize( size ) ;
    }
    inline LookupResult* request( int i ) {
        this->checkSize( i + 1 ) ;
        return &this->cache[i] ;
    }
} ;

class Picker {
public :
    int length ;
    bool flag ;
    const QVector<QString>* keys ;
    QVector<QList<WordRecord>::iterator> itors ;
    QVector<QList<WordRecord>::iterator> ends ;
    inline Picker () : length(0), flag(false), keys(), itors(), ends() {} ;
    inline void set( const LookupResult& result ) {
        this->length = result.wordRecordLists.count() ;
        this->flag = true ;
        this->keys = &result.keys ;
        if ( this->itors.size() < this->length ) {
            this->itors.resize( this->length ) ;
            this->ends.resize( this->length ) ;
        }
        for ( int i = 0 ; i < this->length ; i++ ) {
            this->itors[i] = result.wordRecordLists[i]->list.begin() ;
            this->ends[i] = result.wordRecordLists[i]->list.end() ;
        }
    }
    inline void set( const LookupResult* result ) {
        this->set( *result ) ;
    }
    inline void pick( CandidateItem& item ) {
        int highestIndex = -1 ;
        qreal highestFreq = -1 ;
        for ( int i = 0 ; i < this->length ; i++ ) {
            if ( this->itors[i] != this->ends[i] ) {
                if ( this->itors[i]->freq > highestFreq ) {
                    highestIndex = i ;
                    highestFreq = this->itors[i]->freq ;
                }
            }
        }
        if ( highestIndex >= 0 ) {
            item.key = (*this->keys)[highestIndex] ;
            item.word = this->itors[highestIndex]->word ;
            item.freq = highestFreq ;
            this->itors[highestIndex]++ ;
        }
        else
            this->flag = false ;
    }
} ;

class CandidateList {
public :
    LookupCache* cache ;
    Picker picker ;
    QVector<CandidateItem> list ;
    int listLength ;
    inline CandidateList( LookupCache* cache ) : cache(cache), picker(), list(), listLength(0) {} ;
    inline void checkSize() {
        if ( this->listLength >= this->list.size() )
            this->list.resize( this->listLength - this->list.size() + 16 ) ;
    }
    inline void clear() {
        this->listLength = 0 ;
    }
    inline void set( int index ) {
        this->listLength = 0 ;
        picker.set( this->cache->cache[index] ) ;
    }
    inline int gen( int requestLength ) {
        if ( this->listLength < requestLength ) {
            for ( int i = this->listLength ; i < requestLength ; i++ ) {
                this->checkSize() ;
                picker.pick( this->list[i] ) ;
                if ( picker.flag )
                    this->listLength++ ;
                else
                    break ;
            }
        }
        return requestLength - this->listLength ;
    }
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
    LookupCache cache ;
    CandidateList candidateList ;
    Dict dict ;
    TrieTree trie ;
    NumberLookup() : code(), cache(), candidateList(&cache), dict(), trie() {}
    inline void pushCode( QChar code ) {
        this->code.append( code ) ;
        this->lookup() ;
    }
    inline void lookup() {
        this->trie.goTo( this->code ) ;
        LookupResult* result = this->cache.request( this->code.length() ) ;
        result->vaild = this->trie.hasKeys() ;
        result->keys.clear() ;
        result->wordRecordLists.clear() ;
        this->trie.getKeys( result->keys ) ;
        for( int i = 0 ; i < result->keys.count() ; i++ )
            result->wordRecordLists.append( &this->dict.find( result->keys[i] ) ) ;
        this->candidateList.set( this->code.length() ) ;
        //qDebug() << result->keys ;
    }
    inline void popCode() { ;
        this->code.chop( 1 ) ;
        this->lookup() ;
    }
    inline void clear() {
        this->code.clear() ;
        this->lookup() ;
    }
    inline int genCandidate( int requestLength ) {
        return this->candidateList.gen( requestLength ) ;
    }
    inline const CandidateItem* getCandidate( int index ) {
        this->genCandidate( index + 1 ) ;
        if ( this->candidateList.listLength > index )
            return &this->candidateList.list[index] ;
        else
            return 0 ;
    }
} ;

#endif
