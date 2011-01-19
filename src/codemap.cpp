#include "codemap.h"

Node* CodeMap::addPath( QString path ) {
    Node* current = this->root ;
    for ( int i = 0; i < path.length(); i++ ) {
        QChar code = path[i] ;
        Node* next = current->addChild( code ) ;
        current = next ;
    }
    return current ;
}

void CodeMap::insertRecord( QString path, QString pinyin, QString hanzi, qreal freq ) {
    Node* node = this->addPath( path ) ;
    RecordList* list = node->addRecord( pinyin ) ;
    Record* record = list->insertRecord( hanzi, freq ) ;
    record->setPinyin( list->pinyin ) ;
}

