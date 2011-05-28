#ifndef LOOKUP_H
#define LOOKUP_H

#include <QHash>
#include <QList>
#include <QString>
#include <QPair>

#include "split.h"
#include "fit.h"
#include "pick.h"
#include "dict.h"

namespace lookup {

typedef QPair<const QString*, const QString*> KeyPair ;
typedef QPair<const QString*, qreal > WordPair ;
typedef QPair<KeyPair, WordPair> Candidate ;

inline const QString* get_key( Candidate* cand ) { return cand->first.first ; }

typedef QPair< int, QPair< QList<const QString*>, QList<const QString*> > > LookupPair ;

class Lookup {
public :
    dict::Dictionary dictionary ;
    split::Spliter spliter ;
    fit::KeyMap keyMap ;
    QList<pick::PickPair> pickCache ;
    QList<LookupPair> lookupCache ;
    QList< QList<QString> > preeditCache ;
    int candCacheIndex ;
    int candStartIndex ;
    QList<Candidate> candList ;

    inline Lookup() : dictionary(), spliter(), keyMap(), pickCache(), lookupCache(), preeditCache(), candCacheIndex(0), candStartIndex(0), candList() {}

    inline void appendCode( QChar code ) {
        this->spliter.appendCode( code ) ;
        this->lookupCache.append( LookupPair() ) ;
        this->preeditCache.append( QList<QString>() ) ;

        QList<const QString*>* key = &(this->lookupCache.last().second.first)  ;
        QList<const QString*>* preedit = &(this->lookupCache.last().second.second)  ;
        QList<QString>* preeditCache = &(this->preeditCache.last())  ;
        
        int highestPoint = -0x1000 ;
        for ( int i = 0 ; i < spliter.stringList.length() ; i++ ) {
            int fitPoint ;
            QList<const QString*> buffer ;
            fit::fit( &(this->spliter.stringList[i].first), &buffer, &fitPoint, &(this->keyMap) ) ;
            if ( fitPoint > highestPoint ) {
                highestPoint = fitPoint ;
                preeditCache->clear() ;
                key->clear() ;
                preedit->clear() ;
                preeditCache->append( this->spliter.stringList[i].first.join( "'" ) ) ;
                foreach( const QString* s, buffer ) {
                    key->append( s ) ;
                    preedit->append( &(preeditCache->last()) ) ;
                }
            }
            else if ( fitPoint == highestPoint ) {
                preeditCache->append( this->spliter.stringList[i].first.join( "'" ) ) ;
                foreach( const QString* s, buffer ) {
                    key->append( s ) ;
                    preedit->append( &(preeditCache->last()) ) ;
                }
            }
        }
        this->pickCache.clear() ;
        pick::set( &(this->pickCache), key, preedit, &(this->dictionary.hash) ) ;
        this->candList.clear() ;
        this->candCacheIndex = this->lookupCache.length() - 1 ;
        this->candStartIndex = 0 ;
    }
};

}

#endif
