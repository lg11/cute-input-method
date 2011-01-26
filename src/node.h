#ifndef __NODE_H
#define __NODE_H

#include <QChar>
#include <QVector>

#include "record.h"

class Node {
public :
    QChar code ;
    QVector<Node*> child ;
    QVector<RecordList*> record ;

    Node( QChar code ) : code( code ) {}
    Node* findChild( QChar code ) ;
    Node* addChild( QChar code ) ;
    RecordList* findRecord( QStringList pinyin ) ;
    RecordList* addRecord( QStringList pinyin ) ;
} ;

#endif
