#include "cache.h"

#include <QDebug>

void QueryCache::set( bool flag, QVector<Node*> result ) {
    this->flag = flag ;
    this->result = result ;
    //qDebug() << result.count() ;
    this->list.clear() ;
    this->itor.clear() ;
    this->max = 0 ;
    for ( int i = 0; i < this->result.count(); i++ ) {
        Node* node = this->result[i] ;
        for ( int j = 0; j < node->record.count(); j++ ) {
            RecordList* list = node->record[j] ;
            QLinkedList<Record*>::iterator itor = list->list.begin() ; 
            this->list.append( list ) ;
            this->itor.append( itor ) ;
            this->max += list->list.count() ;
        }
    }
    this->cand.clear() ;
}

Record* QueryCache::get( int listIndex, int recordIndex ) {
    if ( listIndex < this->list.count() ) {
        RecordList* list = this->list[listIndex] ;
        if ( recordIndex < list->list.count() ) {
            QLinkedList<Record*>::iterator itor ;
            itor = list->list.begin() ;
            for ( int i = 0 ; i < recordIndex ; i++ ) {
                itor++ ;
            }
            return *itor ;
        }
    }
    return NULL ;
}

int QueryCache::gen( int length ) {
    //qDebug() << "0" ;
    while ( ( this->cand.count() < length ) && ( this->cand.count() < this->max ) ) {
        //qDebug() << "1" ;
        qreal freq = -1 ; 
        int index = -1 ;
        for ( int i = 0; i < this->itor.count(); i++ ) {
            //qDebug() << "2" ;
            RecordList* list = this->list[i] ;
            if ( this->itor[i] != list->list.end() ) {
                //qDebug() << "3" ;
                if ( (*this->itor[i])->freq > freq ) {
                    //qDebug() << "4" ;
                    freq = (*this->itor[i])->freq ;
                    index = i ;
                }
            }
        }
        if ( index >= 0 ) {
            Record* record = *this->itor[index] ;
            this->itor[index]++ ;
            this->cand.append( record ) ;
        }
        //else
            //break ;
    }
    return this->cand.count() ;
}

