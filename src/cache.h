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
    int max ;
    bool flag ;
    int focus ;
    //QLinkedList<Record*>::iterator* focus ;
    
    QueryCache() { this->max = 0 ; this->focus = -1 ; }
    //QueryCache() { this->focus = NULL ; }
    void set( bool flag, QVector<Node*> result ) ;
    int gen( int length ) ;
    Record* get( int listIndex, int recordIndex ) ;
} ;

#endif

