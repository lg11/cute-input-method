#include "dict.h"
#include "trie.h"
#include "lookup.h"

#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QTextStream>

QDebug operator<<( QDebug dbg, const WordRecordList& l ) {
    dbg.nospace() << "{ " ;
    for ( int i = 0 ; i < l.length() ; i++ ) { 
        const WordRecord& r = l.list.at(i) ;
        dbg.nospace() << "( " << r.word << ", " << r.freq << " ) ";
    }
    dbg.nospace() << "}" ;
    return dbg.space();
}

QDebug operator<<( QDebug dbg, const CandidateItem& item ) {
    dbg.nospace() << "( " ;
    //dbg.nospace() <<  item.key << ", " << item.word.toUtf8() << ", " << item.freq ;
    dbg.nospace() <<  item.key << ", " << item.word << ", " << item.freq ;
    dbg.nospace() << " )" ;
    return dbg.space();
}


void load( Dict* d, QString file_path ) {
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
            QString pinyin = list.at(1) ;
            QString hanzi = list.at(2) ;
            qreal freq = list.at(3).toFloat() ;
            d->insert( pinyin, hanzi, freq ) ;
        }
    }
}


int main( int argc, char** argv ) {
    Dict d ;
    load( &d, argv[1] ) ;
    qDebug() << "loaded" ;
    NumberLookup lookup( &d ) ;
    qDebug() << "built" ;

    while( 1 ) {
        QTextStream cin( stdin, QIODevice::ReadOnly ) ;
        QString s ;
        cin >> s ;
        //QVector<QString> keys ;
        //t.goTo(s) ;
        //t.getKeys( keys ) ;
        //qDebug() << keys ;
        for ( int i = 0 ; i < s.length() ; i++ ) 
            lookup.pushCode( s[i] ) ;
        for ( int i = 0 ; i < 600 ; i++ ) {
            const CandidateItem* item ;
            item = lookup.getCandidate( i ) ;
            if ( item )
                qDebug() << i << *item ;
        }
        lookup.clear() ;
    }
}
