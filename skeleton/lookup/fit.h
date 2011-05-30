#ifndef FIT_H
#define FIT_H

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

inline const QList<QString>* get_keys( KeyMap* map, const QString& path ) {
    return map->contains( path ) ? &((*map)[path]) : NULL ;
}

inline void check_string( const QStringList* string, const QString& key, bool* flag, int* fit_point ) {
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

inline void fit( const QStringList* string, QList<const QString*>* buffer, int* fit_point, KeyMap* key_map ) {
    QString path ;
    foreach ( const QString& s, *string )
        path.append( s.at(0) ) ;
    
    const QList<QString>* keys = get_keys( key_map, path ) ;
    int highest_point = -0x1000 ;

    if ( keys ) {
        //qDebug() << *string << *keys ;
        foreach( const QString& key, *keys ) {
            *fit_point = 0 ;
            bool flag = true ;
            check_string( string, key, &flag, fit_point ) ;
            //qDebug() << *string << key << flag << fit_point ;
            if ( flag ) {
                if ( *fit_point >= 0 ) {
                    buffer->clear() ;
                    buffer->append( &key ) ;
                    highest_point = 0 ;
                    break ;
                }
                else if ( *fit_point > highest_point ) {
                    buffer->clear() ;
                    buffer->append( &key ) ;
                    highest_point = *fit_point ;
                }
                else if ( *fit_point == highest_point ) 
                    buffer->append( &key ) ;
            }
        }
    }
    *fit_point = highest_point ;
}

}

#endif
