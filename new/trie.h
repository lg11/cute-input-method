#ifndef TRIE_H
#define TRIE_H

#include <QString>
#include <QStack>

class TrieNode {
public :
    QChar tag ;
    QList<QString> key ;
    QList<TrieNode> child ;
    inline TrieNode( QChar tag = 0 ) : tag(tag), key(), child() {}
    inline int findChild( QChar tag ) {
        for ( int i = 0 ; i < this->child.length() ; i++ ) {
            if ( tag == this->child.at(i).tag )
                return i ;
        }
        return -1 ;
    }
    inline TrieNode* getChild( int i ) { return &this->child[i] ; }
    inline int appendChild( QChar tag ) {
        int i = this->findChild( tag ) ;
        if ( i < 0 ) {
            this->child.append( TrieNode(tag) ) ;
            return this->child.length() - 1 ;
        }
        else 
            return i ;
    }
    inline void removeChild( QChar tag ) {
        int i = this->findChild( tag ) ;
        if ( i >= 0 ) {
            this->child.removeAt(i) ;
        }
    }
    inline int findKey( const QString& key ) {
        for ( int i = 0 ; i < this->key.length() ; i++ ) {
            if ( key == this->key.at(i) )
                return i ;
        }
        return -1 ;
    }
    inline void appendKey( const QString& key ) {
        int i = this->findKey( key ) ;
        if ( i < 0 ) {
            this->key.append( key ) ;
        }
    } ;
    inline void removeKey( const QString& key ) {
        int i = this->findKey( key ) ;
        if ( i >= 0 ) {
            this->key.removeAt(i) ;
        }
    }
} ;

class Seeker {
public :
    QStack<TrieNode*> track ;
    TrieNode* startPoint ;
    inline Seeker() : track() {}
    
} ;

class TrieTree {
public :
    TrieNode root ;
    inline TrieTree() : root() {}
    inline TrieNode* find( const QString& path ) {
        TrieNode* node = &this->root ;
        for ( int i = 0 ; i < path.length() ; i++ ) {
            int index = node->findChild( path[i] ) ;
            if ( index < 0 ) 
                return &this->root ;
            else
                node = node->getChild(index) ;
        }
        return node ;
    }
    inline void insert( const QString& path, const QString& key ) {
        TrieNode* node = &this->root ;
        for ( int i = 0 ; i < path.length() ; i++ ) {
            node = node->getChild( node->appendChild( path[i] ) ) ;
        }
        node->appendKey( key ) ;
    }
    inline void remove( const QString& path, const QString& key ) {
        TrieNode* node = this->find( path ) ;
        if ( node != &this->root ) {
            node->removeKey( key ) ;
        }
    }
} ;

#endif

