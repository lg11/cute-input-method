#ifndef TRIE_H
#define TRIE_H

#include <QString>
#include <QStack>
#include <QList>
#include <QPair>

//#include <QDebug>

namespace trie {


typedef QPair< QSet<QString>, QList<int> > NodePair ;
typedef QPair< QChar, NodePair > Node ;

inline Node* get_child( QList<Node>* stack, Node* node, QChar tag ) { 
    for ( int i = 0 ; i < node->second.second.length() ; i++ ) {
        Node* child = &((*stack)[node->second.second.at(i)]) ;
        if ( tag == child->first )
            return child ;
    }
    return NULL ;
}

inline Node* add_child( QList<Node>* stack, Node* node, QChar tag ) {
    Node* child = get_child( stack, node, tag ) ;
    if ( !child ) {
        node->second.second.append( stack->length() ) ;
        stack->append( Node( tag, NodePair() ) ) ;
        child = &(stack->last()) ;
    }
    return child ;
}

inline void get_children( const QList<Node>* stack, const Node* node, QList<const Node*>* children ) {
    foreach( int i, node->second.second )
        children->append( &(stack->at(i)) ) ;
}

inline void get_keys( const Node* node, QList<const QString*>* keys ) {
    for ( QSet<QString>::const_iterator i = node->second.first.begin() ; i != node->second.first.end() ; i++ )
        keys->append( &(*i) ) ;
}

inline void add_key( Node* node, const QString& key ) {
    node->second.first.insert( key ) ;
}

inline void get_keys( const QList<Node>* stack, const Node* node, QList<const QString*>* keys ) {
    get_keys( node, keys ) ;
    if ( keys->isEmpty() && !node->second.second.isEmpty() ) {
        QList<const Node*> current ;
        QList<const Node*> deeper ;
        get_children( stack, node, &current ) ;
        while( !current.isEmpty() && keys->isEmpty() ) {
            while( !current.isEmpty() ) {
                const Node* node = current.takeLast() ;
                get_keys( node, keys ) ;
                if ( keys->isEmpty() )
                    get_children( stack, node, &deeper ) ;
            }
            current.append( deeper ) ;
            deeper.clear() ;
        }
    }
}

class Tree {
public :
    QList<Node> stack ;
    Node* root ;
    QChar trans[26] ;
    inline Tree() : stack() {
        this->stack.append( Node( 0x00, NodePair() ) ) ;
        this->root = &(this->stack.last()) ;
        this->trans[ 'a' - 'a' ] = QChar('2') ;
        this->trans[ 'b' - 'a' ] = QChar('2') ;
        this->trans[ 'c' - 'a' ] = QChar('2') ;
        this->trans[ 'd' - 'a' ] = QChar('3') ;
        this->trans[ 'e' - 'a' ] = QChar('3') ;
        this->trans[ 'f' - 'a' ] = QChar('3') ;
        this->trans[ 'g' - 'a' ] = QChar('4') ;
        this->trans[ 'h' - 'a' ] = QChar('4') ;
        this->trans[ 'i' - 'a' ] = QChar('4') ;
        this->trans[ 'j' - 'a' ] = QChar('5') ;
        this->trans[ 'k' - 'a' ] = QChar('5') ;
        this->trans[ 'l' - 'a' ] = QChar('5') ;
        this->trans[ 'm' - 'a' ] = QChar('6') ;
        this->trans[ 'n' - 'a' ] = QChar('6') ;
        this->trans[ 'o' - 'a' ] = QChar('6') ;
        this->trans[ 'p' - 'a' ] = QChar('7') ;
        this->trans[ 'q' - 'a' ] = QChar('7') ;
        this->trans[ 'r' - 'a' ] = QChar('7') ;
        this->trans[ 's' - 'a' ] = QChar('7') ;
        this->trans[ 't' - 'a' ] = QChar('8') ;
        this->trans[ 'u' - 'a' ] = QChar('8') ;
        this->trans[ 'v' - 'a' ] = QChar('8') ;
        this->trans[ 'w' - 'a' ] = QChar('9') ;
        this->trans[ 'x' - 'a' ] = QChar('9') ;
        this->trans[ 'y' - 'a' ] = QChar('9') ;
        this->trans[ 'z' - 'a' ] = QChar('9') ;
    }
    inline void addKey( const QString& key ) {
        //qDebug() << "1" << key ;
        Node* node = this->root ;
        for ( int i = 0 ; i < key.length() ; i++ ) {
            char ch = key.at(i).toAscii() ;
            //qDebug() << "3" << ch << node ;
            if ( ch >= 'a' && ch <= 'z' ) 
                node = add_child( &(this->stack), node, this->trans[ ch - 'a' ] ) ;
        }
        add_key( node, key ) ;
    }
    inline void getKeys( const QString& path, QList<const QString*>* keys ) {
        Node* node = this->root ;
        for ( int i = 0 ; i < path.length() && node ; i++ ) {
            node = get_child( &(this->stack), node, path.at(i) ) ;
        }
        if ( node )
            get_keys( &(this->stack), node, keys ) ;
    }
} ;

}

#endif

