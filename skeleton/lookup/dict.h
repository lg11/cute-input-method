#ifndef DICT_H
#define DICT_H

#include <QString>
#include <QPair>
#include <QList>
#include <QHash>

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
    inline Dictionary() : hash() {} ;
    inline WordRecordList* get( const QString& key ) { return this->hash.contains(key) ? &(this->hash[key]) : NULL ; }
    inline void insert( const QString& key, const QString& word, qreal freq ) { insert_record( &(this->hash[key]), word, freq ) ; }
} ;

}

#endif
