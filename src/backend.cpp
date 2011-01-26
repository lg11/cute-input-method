#include "backend.h"

#include <QFile>
#include <QStringList>
#include <QTextStream>

void Backend::load( QString file_path ) {
    QFile file( file_path ) ;
    bool flag ;

    flag = file.open( QIODevice::ReadOnly | QIODevice::Text ) ;
    if ( flag ) {
        QTextStream in( &file ) ;
        in.setCodec( "utf-8" ) ;
        while( !in.atEnd() ) {
            QString line = in.readLine() ;
            QStringList list = line.split( " " ) ;
            QString code = list.at(0) ;
            QStringList pinyin = list.at(1).split( "\'" ) ;
            QString hanzi = list.at(2) ;
            qreal freq = list.at(3).toDouble() ;
            this->map.insertRecord( code, pinyin, hanzi, freq ) ;
        }
    }
}

void Backend::append( QChar code ) {
    int i = this->code.length() ;
    this->code += code ;
    if ( this->cache.count() < this->code.length() )
        this->cache.append( QueryCache() ) ;
    this->cache[i].set( this->seeker.powerSeek( this->code ) ) ;
}
