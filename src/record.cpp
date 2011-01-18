#include "record.h"

#include <string.h>
//#include <QDebug>

Record* RecordList::findRecord( QString hanzi ) {
    QLinkedList<Record*>::iterator itor = this->list.begin() ;
    while( itor != this->list.end() ){
        Record* record = *itor ;
        if ( record->hanzi == hanzi )
            return record ;
        else
            itor++ ;
    }
    return NULL ;
}

Record* RecordList::insertRecord( QString hanzi, qreal freq ) {
    Record* record = this->findRecord( hanzi ) ;
    if ( !record ) {
        QLinkedList<Record*>::iterator itor = this->list.begin() ;
        while( itor != this->list.end() ){
            record = *itor ;
            if ( freq > record->freq )
                break ;
            else
                itor++ ;
        }
        record = new Record( hanzi, freq ) ;
        this->list.insert( itor, record ) ;
    }
    return record ;
}
