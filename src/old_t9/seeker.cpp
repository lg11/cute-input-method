#include "seeker.h"

#include <QStack>
#include <QDebug>

Node* Seeker::seek( QString path ) {
    this->current = this->start ;
    for ( int i = 0; i < path.length(); i++ ) {
        QChar code = path[i] ;
        Node* next = this->current->findChild( code ) ;
        if ( next )
            this->current = next ;
        else 
            return NULL ;
    }
    return this->current ;
}

void Seeker::powerSeek( QString path ) {
    this->flag = false ;
    this->result.clear() ;
    Node* node = this->seek( path ) ;
    if ( node ) {
        if ( node->record.count() ) {
            //qDebug() << "get" << path ;
            this->result.append( node ) ;
            this->flag = true ;
        }
        else {
            //qDebug() << "power seek" ;
            QStack<Node*> current;
            QStack<Node*> deeper;
            current.push( this->current ) ;
            while( current.count() > 0 && this->result.count() < 1 ) {
                while( current.count() > 0 ) {
                    node = current.pop() ;
                    //qDebug() << QString( node->code ) ;
                    if ( node->record.count() )
                        this->result.append( node ) ;
                    else {
                        if ( this->result.count() < 1 ) {
                            for ( int i = 0; i < node->child.count(); i++ ) {
                                deeper.append( node->child[i] ) ;
                            }
                        }
                    }
                }
                current = deeper ;
                deeper.clear() ;
            }
        }
    }
    //return this->result ;
}
