#include "cache.h"

#include <QDebug>

void QueryCache::set( QVector<Node*> result ) {
    this->result = result ;
    this->list.clear() ;
    this->itor.clear() ;
    for ( int i = 0; i < this->result.count(); i++ ) {
        Node* node = this->result[i] ;
        for ( int j = 0; j < node->record.count(); j++ ) {
            RecordList* list = node->record[j] ;
            QLinkedList<Record*>::iterator itor = list->list.begin() ; 
            this->list.append( list ) ;
            this->itor.append( itor ) ;
        }
    }
    this->cand.clear() ;
}

int QueryCache::gen( int length ) {
    //qDebug() << "0" ;
    while ( this->cand.count() < length ) {
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
        else
            break ;
    }
    return this->cand.count() ;
}
