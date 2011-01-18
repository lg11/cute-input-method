#ifndef __RECORD_H
#define __RECORD_H

#include <QString>
#include <QLinkedList>

class Record {
public :
    QString hanzi ;
    qreal freq ;
    Record( QString hanzi ) : hanzi( hanzi ) { this->freq = 0 ; }
    Record( QString hanzi, qreal freq ) : hanzi( hanzi ) { this->freq = freq ; }
} ;

class RecordList {
public :
    QString pinyin ;
    QLinkedList<Record*> list ;
    RecordList( QString pinyin ) : pinyin( pinyin ) {}
    Record* findRecord( QString hanzi ) ;
    Record* insertRecord( QString hanzi, qreal freq ) ;
} ;

#endif
