#ifndef DICT_H
#define DICT_H

#include <QHash>
#include <QList>
#include <QString>

struct WordRecord {
    QString word ;
    qreal freq ;
    inline WordRecord( const QString& word, qreal freq ) : word(word), freq(freq) {}
} ;

//inline bool operator==( const WordRecord& l, const WordRecord& r ) { return l.word == r.word ; }
//inline bool operator==( const WordRecord& r, const QString& s ) { return r.word == s ; }
//inline bool operator==( const QString& s, const WordRecord& r ) { return r.word == s ; }


class WordRecordList {
public :
    QList<WordRecord> list ;
    inline WordRecordList() : list() {}
    inline int length() const { return this->list.length() ; }
    inline int find( const QString& word ) const {
        for( int i = 0 ; i < this->length() ; i++ ) {
            if ( word == this->list.at(i).word )
                return i ;
        }
        return -1 ;
    }
    inline void insert( const WordRecord& r ) {
        int i = 0 ;
        for( ; i < this->length() ; i++ ) {
            if ( r.freq > this->list.at(i).freq )
                break ;
        } 
        this->list.insert( i, r ) ;
    }
    inline void insert( const QString& word, qreal freq ) { 
        WordRecord r( word, freq ) ;
        int i = this->find( word ) ;
        if ( i >= 0 )
            this->list.removeAt(i) ;
        this->insert( r ) ;
    }
    inline void remove( const QString& word ) { 
        int i = this->find( word ) ;
        if ( i >= 0 ) 
            this->list.removeAt(i) ;
    }
} ;


class Dict {
public :
    QHash< QString, WordRecordList > hash ;
    inline Dict() : hash() {} ;
    inline WordRecordList& find( const QString& key ) { return this->hash[key] ; }
    inline bool contains( const QString& key ) { return this->hash.contains(key) ; }
    inline void insert( const QString& key, const QString& word, qreal freq ) {
        WordRecordList& l = this->hash[key] ;
        l.insert( word, freq ) ;
    }
    inline void remove( const QString& key, const QString& word ) {
        WordRecordList& l = this->hash[key] ;
        l.remove( word ) ;
        if ( l.length() <= 0 )
            this->hash.remove( key ) ;
    }
} ;

#endif
