#include "node.h"


Node* Node::findChild( QChar code ) {
    int i = 0 ;
    while ( i < this->child.count() ) {
        Node* child = this->child[i] ;
        if ( child->code == code )
            return child ;
        else 
            i++ ;
    }
    return NULL ;
}

Node* Node::addChild( QChar code ) {
    Node* child = this->findChild( code ) ;
    if ( !child ) {
        child = new Node( code ) ;
        this->child.append( child ) ;
    }
    return child ;
}

RecordList* Node::findRecord( QStringList pinyin ) {
    int i = 0 ;
    while ( i < this->record.count() ) {
        RecordList* record = this->record[i] ;
        if ( record->pinyin == pinyin )
            return record ;
        else
            i++ ;
    }
    return NULL ;
}

RecordList* Node::addRecord( QStringList pinyin ) {
    RecordList* record = this->findRecord( pinyin ) ;
    if ( !record ) {
        record = new RecordList( pinyin ) ;
        this->record.append( record ) ;
    }
    return record ;
}
