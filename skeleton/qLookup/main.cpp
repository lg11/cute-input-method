#include "lookup.h"

#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QTextStream>

QDebug operator<<( QDebug dbg, const dict::WordRecordList& l ) {
    dbg.nospace() << "{ " ;
    for ( int i = 0 ; i < l.length() ; i++ ) { 
        const dict::WordRecord& r = l.at(i) ;
#ifdef Q_WS_MAEMO_5
        dbg.nospace() << "( " << r.first << ", " << r.second << " ) ";
#else
        dbg.nospace() << "( " << r.first.toUtf8() << ", " << r.second << " ) ";
#endif
    }
    dbg.nospace() << "}" ;
    return dbg.space();
}

QDebug operator<<( QDebug dbg, const split::KeyString& string ) {
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


void load( dict::Dictionary* d, QString file_path ) {
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
    lookup::Lookup lup ;
    load( &(lup.dictionary), argv[argc-1] ) ;
    qDebug() << "loaded" ;
    foreach ( const QString& key, lup.dictionary.hash.keys() ) {
        if ( key.count( "'" ) <= 0 )
            split::add_key( &(lup.spliter.keySet), key ) ;
        fit::add_key( &(lup.keyMap), key ) ;
    }
    //qDebug() << spliter.keySet.first.first ;
    //qDebug() << spliter.keySet.first.second ;
    //qDebug() << spliter.keySet.second ;
    qDebug() << "built" ;
    //NumberLookup lookup( &d ) ;

    while( 1 ) {
        QTextStream cin( stdin, QIODevice::ReadOnly ) ;
        QString s ;
        cin >> s ;
        //WordRecordList* l = d.get(s) ;
        //if ( l )
            //qDebug() << *l ;
        //qDebug() <<  *(fit::get_keys( &map, s )) ;
        
        for ( int i = 0 ; i < s.length() ; i++ ) 
            lup.appendCode( s[i] ) ;
        //lup.popCode() ;
        for ( int i = 0 ; i < 10 ; i ++ ) {
            const QString* k ;
            const QString* p ;
            const QString* w ;
            qreal freq ;
            pick::pick( &(lup.pickCache), &k, &p, &w, &freq ) ;
            if ( k )
                qDebug() << *k << *p << w->toUtf8() << freq ;
        }
        while ( !lup.spliter.code.isEmpty() )
            lup.popCode() ;

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
