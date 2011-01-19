#include "backend.h"

#include <QDebug>
#include <QFile>
#include <QStringList>

//#include <QtGui>

int main( int argc, char** argv ) {
    Backend backend ;
    backend.load( "../data/formated" ) ;
    qDebug() << "done" ;
    QueryCache* cache ;

    while (1) {
        QString path ;
        QVector<Node*> result ;
        QTextStream cin( stdin, QIODevice::ReadOnly ) ;
        cin >> path ;
        backend.append( path[0] ) ;
        cache = &( backend.cache[ backend.code.length() - 1 ] ) ;
        cache->gen( 6 ) ;
        //cache->gen( cache->max ) ;
        qDebug() << cache->max ;
        for( int i = 0; i < cache->cand.count(); i++ ) {
            Record* record = cache->cand[i] ;
            qDebug() << record->pinyin << record->hanzi << record->freq ;
        }
    }

    return 0 ;
}
