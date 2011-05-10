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
    QVector<const WordRecordList*> wordRecordLists ;
    inline LookupResult( bool vaild = false ) : vaild(vaild), keys(), wordRecordLists() {}
    inline LookupResult( bool vaild, const QVector<QString>& keys, const QVector<const WordRecordList*>& wordRecordLists ) : vaild(vaild), keys(keys), wordRecordLists(wordRecordLists) {}
} ;

class LookupCache {
public :
    QVector<LookupResult> vector ;
    //int cacheLength ;
    inline LookupCache() : vector(){}
    inline void checkSize( int size ) {
        if ( size > this->vector.size() )
            this->vector.resize( size ) ;
    }
    inline LookupResult* request( int i ) {
        this->checkSize( i + 1 ) ;
        return &this->vector[i] ;
    }
} ;

class Picker {
public :
    int length ;
    bool flag ;
    const QVector<QString>* keys ;
    QVector<QList<WordRecord>::const_iterator> itors ;
    QVector<QList<WordRecord>::const_iterator> ends ;
    inline Picker () : length(0), flag(false), keys(0), itors(), ends() {} ;
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
    inline void pick( CandidateItem* item ) {
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
            item->key = (*this->keys)[highestIndex] ;
            item->word = this->itors[highestIndex]->word ;
            item->freq = highestFreq ;
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
    QVector<CandidateItem> vector ;
    int vectorLength ;
    int resultIndex ;
    inline CandidateList( LookupCache* cache ) : cache(cache), picker(), vector(), vectorLength(0), resultIndex(0) {} ;
    inline void checkSize() {
        if ( this->vectorLength >= this->vector.size() )
            this->vector.resize( this->vectorLength + 16 ) ;
    }
    inline void clear() {
        this->vectorLength = 0 ;
        this->resultIndex = 0 ;
    }
    inline void setResultIndex( int resultIndex ) {
        this->vectorLength = 0 ;
        this->resultIndex = resultIndex ;
        picker.set( this->cache->vector[resultIndex] ) ;
    }
    inline bool tryPrevResult() {
        bool flag = false ;
        while ( this->resultIndex > 0 && !flag ) {
            //qDebug() << this->resultIndex ;
            this->resultIndex-- ;
            if ( this->cache->vector[this->resultIndex].vaild )
                flag = true ;
        }
        return flag ;
    }
    inline int gen( int requestLength ) {
        int prevLength = this->vectorLength ;
        if ( this->vectorLength < requestLength ) {
            for ( int i = this->vectorLength ; i < requestLength ; i++ ) {
                this->checkSize() ;
                picker.pick( &this->vector[this->vectorLength] ) ;
                if ( picker.flag )
                    this->vectorLength++ ;
                else {
                    if ( this->tryPrevResult() )
                        picker.set( this->cache->vector[this->resultIndex] ) ;
                    else
                        break ;
                }
            }
        }
        return this->vectorLength - prevLength ;
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
    Dict* dict ;
    TrieTree trie ;
    NumberLookup( Dict* dict ) : code(), cache(), candidateList(&cache), dict(dict), trie() { this->buildTrieTree() ; }
    void buildTrieTree() {
        for( QHash<QString, WordRecordList>::const_iterator itor = this->dict->hash.constBegin() ; itor != this->dict->hash.constEnd() ; itor++ ) {
            //qDebug() << itor.key() ;
            this->trie.addKey( itor.key() ) ;
        }
    }
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
        this->trie.getKeys( &result->keys ) ;
        for( int i = 0 ; i < result->keys.count() ; i++ )
            result->wordRecordLists.append( &this->dict->find( result->keys[i] ) ) ;
        this->candidateList.setResultIndex( this->code.length() ) ;
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
        if ( this->candidateList.vectorLength > index )
            return &this->candidateList.vector[index] ;
        else
            return 0 ;
    }
} ;

#endif
