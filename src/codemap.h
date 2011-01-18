#ifndef __CODEMAP_H
#define __CODEMAP_H

#include "node.h"

class CodeMap {
public :
    Node* root ;

    CodeMap() { this->root = new Node( 0x00 ) ; } 
    Node* addPath( QString path ) ;
    void insertRecord( QString path, QString pinyin, QString hanzi, qreal freq ) ;
} ;

//class Worker {
//public :
    //Worker() {}
    //addRecord( Node* node,  )
//} ;

#endif
