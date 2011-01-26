#ifndef __SEEKER_H
#define __SEEKER_H

#include "node.h"

#include <QVector>

class Seeker {
public :
    Node* start ;
    Node* current ;
    QVector<Node*> result ;
    bool flag ;

    Seeker() { this->flag = false; }
    void setStart( Node* start ) { this->start = start; }
    Node* seek( QString path ) ;
    QVector<Node*> powerSeek( QString path ) ;
    QVector<Node*> get() ;
} ;

#endif
