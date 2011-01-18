#include "codemap.h"

#include <QDebug>
#include <QFile>
#include <QStringList>

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
    Node* node = map->seek( "zhe" ) ;
    
    for ( int i = 0; i < node->child.count(); i++ ) {
        const Node* child = node->child.at(i) ;
        qDebug() << QString( child->code )  ;
    }
    for ( int i = 0; i < node->record.count(); i++ ) {
        const RecordList* record = node->record.at(i) ;
        qDebug() << record->pinyin ;
    }

    return 0 ;
}
