#include "dict.h"
#include "split.h"
//#include "lookup.h"

#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QTextStream>

QDebug operator<<( QDebug dbg, const WordRecordList& l ) {
    dbg.nospace() << "{ " ;
    for ( int i = 0 ; i < l.length() ; i++ ) { 
        const WordRecord& r = l.at(i) ;
#ifdef Q_WS_MAEMO_5
        dbg.nospace() << "( " << r.first << ", " << r.second << " ) ";
#else
        dbg.nospace() << "( " << r.first.toUtf8() << ", " << r.second << " ) ";
#endif
    }
    dbg.nospace() << "}" ;
    return dbg.space();
}

QDebug operator<<( QDebug dbg, const KeyString& string ) {
    QString s = string.first.join( "'" ) ;
#ifdef Q_WS_MAEMO_5
    dbg.nospace() << s << ", " ;
#else
    dbg.nospace() << s.toUtf8() << ", " ;
#endif
    dbg.nospace() << string.second.first << ", " << string.second.second ;
    return dbg.space();
}

//QDebug operator<<( QDebug dbg, const CandidateItem& item ) {
    //dbg.nospace() << "( " ;
    //dbg.nospace() <<  item.key << ", " << item.word.toUtf8() << ", " << item.freq ;
//#ifdef Q_WS_MAEMO_5
    //dbg.nospace() <<  item.key << ", " << item.word << ", " << item.freq ;
//#else
    //dbg.nospace() <<  item.key << ", " << item.word.toUtf8() << ", " << item.freq ;
//#endif
    //dbg.nospace() << " )" ;
    //return dbg.space();
//}


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
            QString key = list.at(0) ;
            QString word = list.at(1) ;
            qreal freq = list.at(2).toFloat() ;
            d->insert( key, word, freq ) ;
        }
    }
}


int main( int argc, char** argv ) {
    Dict d ;
    Spliter spliter ;
    load( &d, argv[1] ) ;
    qDebug() << "loaded" ;
    foreach( QString key, d.hash.keys() ) {
        if ( key.count( "'" ) <= 0 )
            add_key( &(spliter.keySet), key ) ;
    }
    qDebug() << "built" ;
    //NumberLookup lookup( &d ) ;

    while( 1 ) {
        QTextStream cin( stdin, QIODevice::ReadOnly ) ;
        QString s ;
        cin >> s ;
        //WordRecordList* l = d.get(s) ;
        //if ( l )
            //qDebug() << *l ;
        for ( int i = 0 ; i < s.length() ; i++ ) 
            spliter.appendCode( s[i] ) ;
        for ( int i = 0 ; i < spliter.stringList.length() ; i++ )
            qDebug() << spliter.stringList[i] ;
        spliter.clear() ;

        //QVector<QString> keys ;
        //t.goTo(s) ;
        //t.getKeys( keys ) ;
        //qDebug() << keys ;
        //for ( int i = 0 ; i < s.length() ; i++ ) 
            //lookup.pushCode( s[i] ) ;
        //for ( int i = 0 ; i < 600 ; i++ ) {
            //const CandidateItem* item ;
            //item = lookup.getCandidate( i ) ;
            //if ( item )
                //qDebug() << i << *item ;
        //}
        //lookup.clear() ;
    }
}
