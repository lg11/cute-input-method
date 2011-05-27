#ifndef FIT_H
#define FIT_H

//#include "split.h"
//#include "dich.h"
#include <QHash>
#include <QString>
#include <QList>

//#include <QDebug>

namespace fit {

typedef QHash< QString, QList<QString>  > KeyMap ;

inline void add_key( KeyMap* map, const QString& key ) {
    QString path( key.at(0) ) ;
    int i = key.indexOf( "'" ) ;
    while ( i > 0 ) {
        i++ ;
        path.append( key.at(i) ) ;
        i = key.indexOf( "'", i ) ;
    }
    (*map)[path].append( key ) ;
    //qDebug() << key << path ;
}

inline QList<QString>* get_keys( KeyMap* map, const QString& path ) {
    return map->contains( path ) ? &((*map)[path]) : NULL ;
}

inline void check_string( QStringList* string, const QString& key, bool* flag, int* fit_point ) {
    QStringList list( key.split( "'" ) ) ;
    for ( int i = 0 ; i < list.length() && flag ; i++ ) {
        const QString& s = string->at(i) ;
        const QString& k = list.at(i) ;
        if ( s == k )
            ;
        else {
            (*fit_point)-- ;
            if ( s.length() > k.length() )
                *flag = false ;
            else {
                QString head( k ) ;
                head.truncate( s.length() ) ;
                if ( s != head ) 
                    *flag = false ;
            }
        }
    }
}

inline int fit( QStringList* string, QList<const QString*>* result, KeyMap* key_map ) {
    QString path ;
    foreach ( const QString& s, *string )
        path.append( s.at(0) ) ;
    
    QList<QString>* keys = get_keys( key_map, path ) ;
    int highest_point = -0x1000 ;

    if ( keys ) {
        //qDebug() << *string << *keys ;
        foreach( const QString& key, *keys ) {
            int fit_point = 0 ;
            bool flag = true ;
            check_string( string, key, &flag, &fit_point ) ;
            //qDebug() << *string << key << flag << fit_point ;
            if ( flag ) {
                if ( fit_point >= 0 ) {
                    result->clear() ;
                    result->append( &key ) ;
                    highest_point = 0 ;
                    break ;
                }
                else if ( fit_point > highest_point ) {
                    result->clear() ;
                    result->append( &key ) ;
                    highest_point = fit_point ;
                }
                else if ( fit_point == highest_point ) 
                    result->append( &key ) ;
            }
        }
    }
    return highest_point ;
}

}

#endif
