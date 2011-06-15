#ifndef T9_H
#define T9_H

#include <QHash>
#include <QList>
#include <QString>
#include <QPair>
#include <QSet>

//#include "split.h"
//#include "fit.h"
#include "pick.h"
#include "dict.h"
#include "trie.h"

//#include <QDebug>

namespace t9 {

typedef QPair<const QString*, const QString*> KeyPair ;
typedef QPair<const QString*, qreal > WordPair ;
typedef QPair<KeyPair, WordPair> CandPair ;
typedef QPair<CandPair, int> Candidate ;

inline const QString* get_key( const Candidate* cand ) { return cand->first.first.first ; }
inline const QString* get_preedit( const Candidate* cand ) { return cand->first.first.second ; }
inline const QString* get_word( const Candidate* cand ) { return cand->first.second.first ; }
inline qreal get_freq( const Candidate* cand ) { return cand->first.second.second ; }

inline void check_cand( QList<Candidate>* cand_list, int length ) {
    if ( length >= cand_list->length() ) 
        cand_list->append( Candidate( CandPair( KeyPair( NULL, NULL ), WordPair( NULL, 0 ) ), 0 ) ) ;
}
inline void set_cand( Candidate* cand, const QString* key, const QString* preedit, const QString* word, qreal freq, int start_index ) {
    cand->first.first.first = key ;
    cand->first.first.second = preedit ;
    cand->first.second.first = word ;
    cand->first.second.second = freq ;
    cand->second = start_index ;
}

//typedef QPair< int, QPair< QList<const QString*>, QList<const QString*> > > LookupPair ;
typedef QPair< QList<const QString*>, QList<const QString*> > LookupPair ;

inline void convert_preedit( const QString& key, const QString& src, QString* dest ) {
    int count = key.count( QChar('\'') ) ;
    if ( count > 0 ) {
        int i = 0 ;
        int length = 0 ;
        while ( i < src.length() ) {
            if ( key.at( i + length ) == QChar('\'') )
                length++ ;
            else 
                i++ ;
        }
        length += i ;
        *dest = key.left( length ) ;
        //qDebug() << length << key << src << *dest ;
        count = count - dest->count( QChar('\'') ) ;
        if ( count > 0 ) {
            for ( int i = 0 ; i < count ; i++ )
                dest->append( QChar('\'') ) ;
        }
    }
    else
        *dest = key.left( src.length() ) ;
}

class T9Lookup {
public :
    dict::Dictionary* dict ;
    //split::Spliter spliter ;
    //fit::KeyMap keyMap ;
    QList<pick::PickPair> pickCache ;
    QList<LookupPair> lookupCache ;
    QList< QList<QString> > preeditCache ;
    QSet<QString> usedKeySet ;
    int candCacheIndex ;
    int candStartIndex ;
    QList<Candidate> candList ;
    int candLength ;
    QString code ;
    trie::Tree tree ;

    //inline Lookup() : dict(), spliter(), keyMap(), pickCache(), lookupCache(), preeditCache(), usedKeySet(), candCacheIndex(0), candStartIndex(0), candList(), candLength(0) {}
    inline T9Lookup( dict::Dictionary* dict ) : dict(dict), pickCache(), lookupCache(), preeditCache(), usedKeySet(), candCacheIndex(0), candStartIndex(0), candList(), candLength(0), code(), tree() {}

    inline void appendCode( QChar code ) {
        this->pickCache.clear() ;
        this->usedKeySet.clear() ;
        this->code.append( code ) ;
        this->lookupCache.append( LookupPair() ) ;
        this->preeditCache.append( QList<QString>() ) ;

        QList<const QString*>* key = &(this->lookupCache.last().first)  ;
        QList<const QString*>* preedit = &(this->lookupCache.last().second)  ;
        QList<QString>* preeditCache = &(this->preeditCache.last())  ;
        
        this->tree.getKeys( this->code, key ) ;
        foreach( const QString* k, *key ) {
            preeditCache->append( QString() ) ;
            convert_preedit( *k, this->code, &(preeditCache->last()) ) ;
        }
        for ( int i = 0 ; i < key->length(); i++ )
            preedit->append( &(preeditCache->at(i)) ) ;

        //foreach( const QString* k, *key )
            //qDebug() << *k ;
        pick::set( &(this->pickCache), key, preedit, &(this->dict->hash) ) ;
        foreach( const QString* k, *key )
            this->usedKeySet.insert( *k ) ;
        this->candLength = 0 ;
        this->candCacheIndex = this->lookupCache.length() - 1 ;
        this->candStartIndex = 0 ;
    }
    inline void popCode() {
        this->code.chop(1) ;
        this->pickCache.clear() ;
        this->usedKeySet.clear() ;
        this->lookupCache.removeLast() ;
        this->preeditCache.removeLast() ;

        if ( !this->lookupCache.isEmpty() ) {
            QList<const QString*>* key = &(this->lookupCache.last().first)  ;
            QList<const QString*>* preedit = &(this->lookupCache.last().second)  ;
            pick::set( &(this->pickCache), key, preedit, &(this->dict->hash) ) ;
            foreach( const QString* k, *key )
                this->usedKeySet.insert( *k ) ;
            //this->candList.clear() ;
            this->candLength = 0 ;
            this->candCacheIndex = this->lookupCache.length() - 1 ;
            this->candStartIndex = 0 ;
        }
    }
    inline void reset() {
        this->code.clear() ;
        this->pickCache.clear() ;
        this->usedKeySet.clear() ;
        this->lookupCache.clear() ;
        this->preeditCache.clear() ;
        this->candCacheIndex = 0 ;
        this->candStartIndex = 0 ;
        this->candLength = 0 ;
    }
    inline void setCode( const QString& code ) {
        this->reset() ;
        for( int i = 0 ; i < code.length() ; i++ )
            this->appendCode( code.at(i) ) ;
    }
    //inline void appendCode( const QString& code ) {
        //for( int i = 0 ; i < code.length() ; i++ )
            //this->appendCode( code.at(i) ) ;
    //}
    inline bool checkCache() {
        bool flag = false ;
        if ( this->candCacheIndex >= 0 ) {
            this->pickCache.clear() ;
            QList<const QString*>* key ;
            QList<const QString*>* preedit ;

            this->candCacheIndex-- ;
            while ( !flag && this->candCacheIndex >= 0 ) {
                key = &(this->lookupCache[this->candCacheIndex].first)  ;
                preedit = &(this->lookupCache[this->candCacheIndex].second)  ;
                if ( !key->isEmpty() ) {
                    //qDebug() << fitPoint << prevPoint << *(preedit->at(0)) ;
                    flag = true ;
                }
                if ( !flag )
                    this->candCacheIndex-- ;
            }
            if ( flag ) {
                pick::set( &(this->pickCache), key, preedit, &(this->dict->hash), &(this->usedKeySet) ) ;
                foreach( const QString* k, *key )
                    this->usedKeySet.insert( *k ) ;
            }
        }
        return flag ;
    }
    inline const Candidate* getCand( int index ) {
        bool flag = true ;
        //bool flag = true && !this->spliter.code.isEmpty() ;
        //while ( flag && this->candList.length() <= index ) {
        while ( flag && this->candLength <= index ) {
            const QString* key ; const QString* preedit ; const QString* word ; qreal freq ;
            pick::pick( &(this->pickCache), &key, &preedit, &word, &freq ) ;
            if ( key ) {
                //this->candList.append( Candidate( CandPair( KeyPair( key, preedit ), WordPair( word, freq ) ), this->candStartIndex ) ) ;
                check_cand( &(this->candList), this->candLength ) ;
                set_cand( &(this->candList[this->candLength]), key, preedit, word, freq, this->candStartIndex ) ;
                this->candLength++ ;
            }
            else {
                flag = this->checkCache() ;
                //this->candStartIndex = this->candList.length() ;
                this->candStartIndex = this->candLength ;
            }
        }
        if ( flag ) 
            return &(this->candList.at(index)) ; 
        else 
            return NULL ;
    }
};

}

#endif
