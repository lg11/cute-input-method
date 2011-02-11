#include "backend.h"

#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QDebug>

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
    //qDebug() << "append" << this->code ;
    int i = this->code.length() ;
    this->code += code ;
    if ( this->cache.count() < this->code.length() )
        this->cache.append( QueryCache() ) ;
    this->cache[i].set( this->seeker.powerSeek( this->code ) ) ;
}

void Backend::pop() {
    this->code.chop( 1 ) ;
    //this->code.truncate( this->code.length() - 1 ) ;
}

void Backend::clear() {
    this->code.clear() ;
    //qDebug() << "clear" << this->code ;
}
