#ifndef SPLIT_H
#define SPLIT_H

#include <QString>
#include <QList>
#include <QStringList>
#include <QPair>
#include <QSet>

#include <QDebug>

typedef QPair< QPair< QSet<QString>, QSet<QChar> >, QSet<QString> > KeySet ;

inline void add_key( KeySet* set, const QString& key ) {
    if ( !set->first.first.contains( key ) ) {
        QString k = key ;
        set->first.first.insert( k ) ;
        set->first.second.insert( k.at(0) ) ;
        set->second.remove( k ) ;
        k.chop( 1 ) ;
        while( k.length() > 0 ) {
            if ( !set->first.first.contains( k ) )
                set->second.insert( k ) ;
            k.chop( 1 ) ;
        }
    }
}

inline bool check_complete( KeySet* set, const QString& key ) { return set->first.first.contains( key ) ; } 
inline bool check_head( KeySet* set, QChar head ) { return set->first.second.contains( head ) ; } 
inline bool check_vaild( KeySet* set, const QString& key ) { return set->second.contains( key ) ; } 

typedef QPair< QStringList, QPair<int,int> > KeyString ;

inline void append_code( KeyString* string, QChar code, KeySet* keySet, QList<KeyString>* stringList ) {
    KeyString* new_string ;
    QString orig_tail( string->first.last() ) ;
    QString new_tail( orig_tail ) ;
    new_tail.append( code ) ;
    if ( check_vaild( keySet, new_tail ) ) {
        if ( check_complete( keySet, orig_tail ) && check_head( keySet, code ) ) {
            stringList->append( *string ) ;
            new_string = &(stringList->last()) ;
            new_string->first.append( code ) ;
            new_string->second.first++ ;
            new_string->second.second = string->second.first ;
        }
        string->first.last() = new_tail ;
        string->second.first++ ;
    }
    else {
        if ( check_head( keySet, code ) ) {
            string->first.append( code ) ;
            string->second.first++ ;
        }
    }
}

inline void pop_code( KeyString* string ) {
    if ( string->second.first > 0 ) {
        if ( string->first.last().length() > 1 )
            string->first.last().chop( 1 ) ;
        else 
            string->first.removeLast() ;
        string->second.first-- ;
    }
}

class Spliter {
public :
    QString code ;
    KeyString emptyString ;
    KeySet keySet ;
    QList<KeyString> stringList ;
    inline Spliter() : code(), emptyString( QStringList(), QPair<int,int>() ), keySet(), stringList() { this->emptyString.first.append( "" ) ; this->stringList.append( this->emptyString ) ; }
    inline void appendCode( QChar code ) {
        QList<KeyString*> list ;
        for( int i = 0 ; i < this->stringList.length() ; i++ )
            list.append( &(this->stringList[i]) ) ;
        for( int i = 0 ; i < list.length() ; i++ ) {
            KeyString* string = list[i] ;
            if ( string->second.first >= this->code.length() ) 
                append_code( string, code, &(this->keySet), &(this->stringList) ) ;
        }
        this->code.append( code ) ;
    }
    inline void clear() { this->code.clear() ; this->stringList.clear() ; this->stringList.append( this->emptyString ) ; }
} ;

#endif
