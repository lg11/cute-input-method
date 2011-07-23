#include "lookup.h"
#include "t9.h"

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
    QString s = string.first.join( QChar( '\'' ) ) ;
#ifdef Q_WS_MAEMO_5
    dbg.nospace() << s << ", " ;
#else
    dbg.nospace() << s.toUtf8() << ", " ;
#endif
    dbg.nospace() << string.second.first << ", " << string.second.second ;
    return dbg.space();
}

QDebug operator<<( QDebug dbg, const lookup::Candidate& cand ) {
#ifdef Q_WS_MAEMO_5
    dbg.nospace() << *(cand.first.first.first) << " " << *(cand.first.first.second) << " " << *(cand.first.second.first) << " " << cand.first.second.second << " " << cand.second ;
#else
    dbg.nospace() << *(cand.first.first.first) << " " << *(cand.first.first.second) << " " << cand.first.second.first->toUtf8() << " " << cand.first.second.second << " " << cand.second ;
#endif
    return dbg.space();
}

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
    t9::T9Lookup t9lup( &(lup.dict) ) ;
    load( &(lup.dict), argv[argc-1] ) ;
    qDebug() << "loaded" ;
    foreach ( const QString& key, lup.dict.hash.keys() ) {
        if ( key.count( '\'' ) <= 0 )
            split::add_key( &(lup.spliter.keySet), key ) ;
        fit::add_key( &(lup.keyMap), key ) ;
        t9lup.tree.addKey( key ) ;
    }
    qDebug() << "built" ;

    while( 1 ) {
        QTextStream cin( stdin, QIODevice::ReadOnly ) ;
        QString s ;
        cin >> s ;
        
        //QList<const QString*> keys ;
        //t9lup.tree.getKeys( s, &keys ) ;
        //foreach( const QString* k, keys )
            //qDebug() << *k ;

        //for ( int i = 0 ; i < s.length() ; i++ ) 
            //t9lup.appendCode( s[i] ) ;
        //t9lup.setCode( s ) ;
        //for ( int i = 0 ; i < 10 ; i ++ ) {
            //const lookup::Candidate* cand = t9lup.getCand( i ) ;
            //if ( cand )
                //qDebug() << *cand ;
        //}
        //while ( !t9lup.code.isEmpty() )
            //t9lup.popCode() ;
        //lup.reset() ;

        //for ( int i = 0 ; i < s.length() ; i++ ) 
            //lup.appendCode( s[i] ) ;
        lup.setCode( s ) ;
        for ( int i = 0 ; i < 10 ; i ++ ) {
            const lookup::Candidate* cand = lup.getCand( i ) ;
            if ( cand )
                qDebug() << *cand ;
        }
        //while ( !lup.spliter.code.isEmpty() )
            //lup.popCode() ;
        //lup.reset() ;

    }
}
