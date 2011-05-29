#ifndef IMENGINE_H
#define IMENGINE_H

#include <QObject>
#include <QSet>
#include <QFile>
#include <QTextStream>

#include "../lookup/lookup.h"

class IMEngine : public QObject {
    Q_OBJECT
public:
    lookup::Lookup lookup ;
    inline IMEngine( QObject* parent = NULL ) : QObject( parent ), lookup() {}
    Q_INVOKABLE inline void load( const QString& path ) {
        QFile file( path ) ;
        if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
            QSet<QString> newKeySet ;
            QTextStream in( &file ) ;
            in.setCodec( "utf-8" ) ;
            while( !in.atEnd() ) {
                QString line = in.readLine() ;
                QStringList list = line.split( " " ) ;
                QString key = list.at(0) ;
                QString word = list.at(1) ;
                qreal freq = list.at(2).toFloat() ;
                if ( !this->lookup.dict.hash.contains( key ) )
                    newKeySet.insert( key ) ;
                this->lookup.dict.insert( key, word, freq ) ;
            }
            foreach( const QString& key, newKeySet ) {
                if ( key.count( "'" ) <= 0 )
                    split::add_key( &(this->lookup.spliter.keySet), key ) ;
                fit::add_key( &(this->lookup.keyMap), key ) ;

            }
        }
    }
} ;

#endif

