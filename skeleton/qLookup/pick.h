#ifndef PICK_H
#define PICK_H

#include <QPair>
#include <QString>
#include <QList>
#include <QHash>

//#include <QDebug>

namespace pick {

typedef QPair< const QString*, const QString* > KeyPair ;
typedef QPair< QList< QPair<QString, qreal> >*, int > RecordPair ;
typedef QPair< KeyPair, RecordPair > PickPair ;

inline const QString* get_key( PickPair* pair ) { return pair->first.first ; }
inline const QString* get_preedit( PickPair* pair ) { return pair->first.second ; }
inline QList< QPair<QString, qreal> >* get_list( PickPair* pair ) { return pair->second.first ; }
inline int get_index( PickPair* pair ) { return pair->second.second ; }
inline void set_index( PickPair* pair, int index ) { pair->second.second = index ; }
inline const QString* get_word( PickPair* pair ) { return &(get_list( pair )->at(get_index( pair )).first) ; }
inline qreal get_freq( PickPair* pair ) { return get_list( pair )->at(get_index( pair )).second ; }

inline void set( QList<PickPair>* list, QList<const QString*>* key, QList<const QString*>* preedit, QHash< QString, QList< QPair<QString, qreal> > >* hash ) {
    for ( int i = 0 ; i < key->length() ; i ++ )
        list->append( PickPair( KeyPair( key->at(i), preedit->at(i) ), RecordPair( &((*hash)[*(key->at(i))]), 0 ) ) ) ;
}

inline void pick( QList<PickPair>* list, const QString** key, const QString** preedit, const QString** word, qreal* freq ) {
    qreal highest_freq = -0x1000 ;
    int highest_index = -0x1000 ;
    for ( int i = 0 ; i < list->length() ; i++ ) {
        PickPair* pair = &((*list)[i]) ;
        QList< QPair<QString, qreal> >* record_list = get_list( pair ) ;
        int index = get_index( pair ) ;
        //qDebug() << index << record_list->length() ;
        if ( index < record_list->length() ) {
            qreal freq = record_list->at(index).second ;
            if ( freq > highest_freq ) {
                highest_freq = freq ;
                highest_index = i ;
            }
        }
    }
    if ( highest_index >= 0 ) {
        PickPair* pair = &((*list)[highest_index]) ;
        *key = get_key( pair ) ;
        *preedit = get_preedit( pair ) ;
        *word = get_word( pair ) ;
        *freq = get_freq( pair ) ;
        set_index( pair, get_index( pair ) + 1 ) ;
    }
    else {
        *key = NULL ;
        *preedit = NULL ;
        *word = NULL ;
        *freq = 0 ;
    }
}

}

#endif
