#ifndef DICT_H
#define DICT_H

#include <QString>
#include <QPair>
#include <QList>
#include <QHash>

//#include <QDebug>

namespace dict {

typedef QPair<QString, qreal> WordRecord ;
typedef QList<WordRecord> WordRecordList ;

inline WordRecord* find_record( WordRecordList* list, const QString& word ) { 
    for( int i = 0 ; i < list->length() ; i++ ) {
        if ( word == list->at(i).first )
            return &((*list)[i]) ;
    }
    return NULL ;
}

inline void remove_record( WordRecordList* list, const QString& word ) { 
    for( int i = 0 ; i < list->length() ; i++ ) {
        if ( word == list->at(i).first ) {
            list->removeAt(i) ;
            break ;
        }
    }
}

inline void insert_record( WordRecordList* list, const QString& word, qreal freq ) { 
    remove_record( list, word ) ;
    int i = 0 ;
    for( ; i < list->length() ; i++ ) {
        if ( freq > list->at(i).second )
            break ;
    } 
    list->insert( i, WordRecord( word, freq ) ) ;
}


class Dictionary {
public :
    QHash<QString, WordRecordList> hash ;
    qreal highestFreq ;
    inline Dictionary() : hash() { this->highestFreq = -0x1000 ; }
    inline WordRecordList* get( const QString& key ) { return this->hash.contains(key) ? &(this->hash[key]) : NULL ; }
    inline void insert( const QString& key, const QString& word, qreal freq ) { 
        this->highestFreq = freq > this->highestFreq ? freq : highestFreq ;
        insert_record( &(this->hash[key]), word, freq ) ;
    }
    inline qreal update( const QString& key, const QString& word, qreal freq ) {
        if ( freq >= 0 ) 
            this->insert( key, word, freq ) ;
        else {
            WordRecordList* list = &(this->hash[key]) ; 
            if ( list->isEmpty() ) {
                freq = highestFreq / 2 ;
                if ( freq < 1.1 ) 
                    freq = 1.1 ;
                insert_record( list, word, freq ) ;
            }
            else {
                if ( list->length() < 4 ) 
                    freq = list->last().second / 2 ;
                else
                    freq = list->at(3).second + ( list->at(2).second - list->at(3).second ) / 2 ;
                if ( freq < 1.1 ) 
                    freq = 1.1 ;
                //else
                    //freq += 1 ;
                this->highestFreq = freq > this->highestFreq ? freq : highestFreq ;
                insert_record( list, word, freq ) ;
            }
        }
        //qDebug() << key << word << freq << highestFreq ;
        return freq ;
    }
} ;

}

#endif
