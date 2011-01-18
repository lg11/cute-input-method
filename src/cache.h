#ifndef __CACHE_H
#define __CACHE_H

#include "node.h"
#include "record.h"

#include <QVector>

class QueryCache {
public :
    QVector<Node*> result ;
    QVector<RecordList*> list ;
    QVector<Record*> cand ;
    QVector<QLinkedList<Record*>::iterator> itor ;
    
    QueryCache() {}
    void set( QVector<Node*> result ) ;
    int gen( int length ) ;
} ;

#endif

