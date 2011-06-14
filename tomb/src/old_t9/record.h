#ifndef __RECORD_H
#define __RECORD_H

#include <QStringList>
#include <QString>
#include <QLinkedList>

class Record {
public :
    QStringList pinyin ;
    QString hanzi ;
    qreal freq ;
    Record( QString hanzi ) : hanzi( hanzi ) { this->freq = 0 ; }
    Record( QString hanzi, qreal freq ) : hanzi( hanzi ) { this->freq = freq ; }
    void setPinyin( QStringList pinyin ) { this->pinyin = pinyin ; }
} ;

class RecordList {
public :
    QStringList pinyin ;
    QLinkedList<Record*> list ;
    RecordList( QStringList pinyin ) : pinyin( pinyin ) {}
    Record* findRecord( QString hanzi ) ;
    Record* insertRecord( QString hanzi, qreal freq ) ;
} ;

#endif
