#include "codemap.h"
#include "seeker.h"
#include "cache.h"

#include <QDebug>
#include <QFile>
#include <QStringList>

#include <QtGui>

CodeMap* load_codemap( QString file_path ) {
    QFile file( file_path ) ;
    CodeMap* map = new CodeMap() ;
    bool flag ;

    flag = file.open( QIODevice::ReadOnly | QIODevice::Text ) ;
    if ( !flag ) return map ;

    QTextStream in( &file ) ;
    in.setCodec( "utf-8" ) ;
    while( !in.atEnd() ) {
        QString line = in.readLine() ;
        QStringList list = line.split( " " ) ;
        QString code = list.at(0) ;
        QString pinyin = list.at(0) ;
        QString hanzi = list.at(1) ;
        qreal freq = list.at(2).toDouble() ;

        map->insertRecord( code, pinyin, hanzi, freq ) ;

        //qDebug() << hanzi.toUtf8() << freq << code ;
    }

    return map ;
}

int main( int argc, char** argv ) {
    CodeMap* map = load_codemap( "../data/formated" ) ;
    qDebug() << "done" ;
    Seeker seeker ;
    seeker.setStart( map->root ) ;
    QueryCache cache;

    while (1) {
        QString path ;
        QVector<Node*> result ;
        QTextStream cin( stdin, QIODevice::ReadOnly ) ;
        cin >> path ;
        cache.set( seeker.powerSeek( path ) ) ;
        cache.gen( 6 ) ;
        for( int i = 0; i < cache.cand.count(); i++ ) {
            Record* record = cache.cand[i] ;
            qDebug() << QString( record->hanzi ) << record->freq ;
        }
    }
    

    return 0 ;
}
