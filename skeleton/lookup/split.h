#ifndef SPLIT_H
#define SPLIT_H

#include <QString>
#include <QList>
#include <QStringList>
#include <QPair>
#include <QSet>

namespace split {

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

inline bool check_complete( const KeySet* set, const QString& key ) { return set->first.first.contains( key ) ; } 
inline bool check_head( const KeySet* set, QChar head ) { return set->first.second.contains( head ) ; } 
inline bool check_valid( const KeySet* set, const QString& key ) { return set->first.first.contains( key ) ? true : set->second.contains( key ) ; } 

typedef QPair< QStringList, QPair<int,int> > KeyString ;

inline void append_code( KeyString* string, QChar code, const KeySet* keySet, QList<KeyString>* stringList ) {
    QString* tail = &(string->first.last()) ;
    bool flag = check_complete( keySet, *tail ) && check_head( keySet, code ) ;
    tail->append( code ) ;
    if ( check_valid( keySet, *tail ) ) {
        if ( flag ) {
            stringList->append( *string ) ;
            KeyString* new_string = &(stringList->last()) ;
            new_string->first.last().chop( 1 ) ;
            new_string->first.append( code ) ;
            new_string->second.first++ ;
            new_string->second.second = string->second.first ;
        }
        string->second.first++ ;
    }
    else {
        tail->chop( 1 ) ;
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
        for ( int i = 0 ; i < this->stringList.length() ; i++ )
            list.append( &(this->stringList[i]) ) ;
        for ( int i = 0 ; i < list.length() ; i++ ) {
            KeyString* string = list[i] ;
            if ( string->second.first >= this->code.length() ) 
                append_code( string, code, &(this->keySet), &(this->stringList) ) ;
        }
        this->code.append( code ) ;
    }
    inline void popCode() {
        this->code.chop( 1 ) ;
        QList<int> removeList ;
        for ( int i = 0 ; i < this->stringList.length() ; i++ ) {
            KeyString* string = &(this->stringList[i]) ;
            if ( string->second.first > this->code.length() ) {
                pop_code( string ) ;
                if ( string->second.first <= string->second.second )
                    removeList.append( i ) ;
            }
        }
        int removedCount = 0 ;
        foreach ( int i, removeList ) {
            this->stringList.removeAt( i - removedCount ) ;
            removedCount++ ;
        }
        if ( this->stringList.isEmpty() ) 
            this->stringList.append( this->emptyString ) ;
    }
    inline void clear() { this->code.clear() ; this->stringList.clear() ; this->stringList.append( this->emptyString ) ; }
} ;

}

#endif
