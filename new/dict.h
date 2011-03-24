#ifndef DICT_H
#define DICT_H

#include <QHash>
#include <QList>
#include <QPair>
#include <QString>
#include <QDebug>

struct WordRecord {
    QString word ;
    qreal freq ;
    inline WordRecord( const QString& word, qreal freq ) : word(word), freq(freq) {}
} ;

inline bool operator==( const WordRecord& l, const WordRecord& r ) { return l.word == r.word ; }
inline bool operator==( const WordRecord& r, const QString& s ) { return r.word == s ; }
inline bool operator==( const QString& s, const WordRecord& r ) { return r.word == s ; }


class WordRecordList {
public :
    QList<WordRecord*> data ;
    WordRecordList() : data() {}
    inline int length() const { return this->data.length() ; }
    inline int find( const QString& word ) const {
        for( int i = 0 ; i < this->length() ; i++ ) {
            if ( word == *this->data.at(i) )
                return i ;
        }
        return -1 ;
    }
    inline void insert( WordRecord* r ) {
        int i = 0 ;
        for( ; i < this->length() ; i++ ) {
            if ( r->freq > this->data.at(i)->freq )
                break ;
        } 
        this->data.insert( i, r ) ;
    }
    inline void insert( const QString& word, qreal freq ) { 
        int i = this->find( word ) ;
        WordRecord* r ;
        if ( i < 0 )
            r = new WordRecord( word, freq ) ;
        else {
            r = this->data[i] ;
            this->data.removeAt(i) ;
        }
        r->freq = freq ;
        this->insert( r ) ;
    }
    inline void remove( const QString& word ) { 
        int i = this->find( word ) ;
        if ( i >= 0 ) 
            this->data.removeAt(i) ;
    }
} ;

QDebug operator<<( QDebug dbg, const WordRecordList& l ) ; 
QDebug operator<<( QDebug dbg, const WordRecordList& l ) {
    dbg.nospace() << "{ " ;
    for ( int i = 0 ; i < l.length() ; i++ ) { 
        const WordRecord* r = l.data.at(i) ;
        dbg.nospace() << "( " << r->word << ", " << r->freq << " ) ";
    }
    dbg.nospace() << "}" ;
    return dbg.space();
}


class Dict {
public :
    QHash< QString, WordRecordList* > data ;
    Dict() : data() {} ;
    inline WordRecordList* find( const QString& key ) { return this->data[key] ; }
    inline void insert( const QString& key, const QString& word, qreal freq ) {
        WordRecordList* l = this->data[key] ;
        if ( !l ) {
            l = new WordRecordList() ;
            this->data.insert( key, l ) ;
        }
        l->insert( word, freq ) ;
    }
    inline void remove( const QString& key, const QString& word ) {
        WordRecordList* l = this->data[key] ;
        if ( l ) {
            l->remove( word ) ;
            if ( l->length() <= 0 ) {
                this->data.remove( key ) ;
                delete l ;
            }
        }
    }
} ;

#endif
