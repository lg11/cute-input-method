#ifndef TRIE_H
#define TRIE_H

#include <QString>
#include <QStack>
#include <QDebug>

class TrieNode {
public :
    QChar tag ;
    QVector<QString> keys ;
    QVector<TrieNode> children ;
    inline TrieNode( QChar tag = 0 ) : tag(tag), keys(), children() {}
    inline TrieNode* findChild( QChar tag ) { 
        for ( int i = 0 ; i < this->children.count() ; i++ ) {
            if ( tag == this->children.at(i).tag )
                return &this->children[i] ;
        }
        return 0 ;
    }
    inline TrieNode* appendChild( QChar tag ) {
        TrieNode* node = this->findChild( tag ) ;
        if ( !node ) {
            this->children.append( TrieNode(tag) ) ;
            node = &this->children.last() ;
        }
        return node ;
    }
    inline void removeChild( QChar tag ) {
        for ( int i = 0 ; i < this->children.count() ; i++ ) {
            if ( tag == this->children.at(i).tag ) {
                this->children.remove(i) ;
                break ;
            }
        }
    }
    inline int findKey( const QString& key ) {
        for ( int i = 0 ; i < this->keys.count() ; i++ ) {
            if ( key == this->keys.at(i) )
                return i ;
        }
        return -1 ;
    }
    inline void appendKey( const QString& key ) {
        int i = this->findKey( key ) ;
        if ( i < 0 ) {
            this->keys.append( key ) ;
        }
    } ;
    inline void removeKey( const QString& key ) {
        int i = this->findKey( key ) ;
        if ( i >= 0 ) {
            this->keys.remove(i) ;
        }
    }
    inline bool hasKeys() const { return !this->keys.isEmpty() ; }
    inline bool hasChildren() const { return !this->children.isEmpty() ; }
    inline bool useful() const { return this->hasKeys() && this->hasChildren() ; }
    inline int getKeys( QVector<QString>& keys ) const {
        keys += this->keys ;
        return this->keys.count() ;
    }
    inline int getChildren( QVector<const TrieNode*>& children ) const {
        for ( int i = 0 ; i < this->children.count() ; i++ )
            children.append( &this->children[i] ) ;
        return this->children.count() ;
    }
    inline int seekKeys( QVector<QString>& keys ) const {
        int count = 0 ;
        count = this->getKeys( keys ) ;
        //qDebug() << count ;
        if ( count <= 0 && this->hasChildren() ) {
            //qDebug() << 1 ;
            QStack<const TrieNode*> current ;
            QStack<const TrieNode*> deeper ;
            this->getChildren( current ) ;
            while( current.count() > 0 && count <= 0 ) {
                //qDebug() << 2 ;
                while( current.count() > 0 ) {
                    //qDebug() << count ;
                    const TrieNode* node = current.pop() ;
                    count += node->getKeys( keys ) ;
                    if ( count <= 0 )
                        this->getChildren( deeper ) ;
                }
                current = deeper ;
                deeper.clear() ;
            }
        }
        return count ;
    }
} ;

class TrieTree {
public :
    TrieNode root ;
    QStack<TrieNode*> stack ;
    QHash<QChar, QChar> hash ;
    inline TrieTree() : root(), stack(), hash() {
        this->stack.push( &this->root ) ;
        this->hash['a'] = '2' ;
        this->hash['b'] = '2' ;
        this->hash['c'] = '2' ;
        this->hash['d'] = '3' ;
        this->hash['e'] = '3' ;
        this->hash['f'] = '3' ;
        this->hash['g'] = '4' ;
        this->hash['h'] = '4' ;
        this->hash['i'] = '4' ;
        this->hash['j'] = '5' ;
        this->hash['k'] = '5' ;
        this->hash['l'] = '5' ;
        this->hash['m'] = '6' ;
        this->hash['n'] = '6' ;
        this->hash['o'] = '6' ;
        this->hash['p'] = '7' ;
        this->hash['q'] = '7' ;
        this->hash['r'] = '7' ;
        this->hash['s'] = '7' ;
        this->hash['t'] = '8' ;
        this->hash['u'] = '8' ;
        this->hash['v'] = '8' ;
        this->hash['w'] = '9' ;
        this->hash['x'] = '9' ;
        this->hash['y'] = '9' ;
        this->hash['z'] = '9' ;
    }
    inline bool goStep( QChar tag ) {
        TrieNode* node = this->stack.top()->findChild( tag ) ;
        if ( node ) {
            this->stack.push( node ) ;
            return true ;
        }
        else 
            return false ;
    }
    inline bool backStep() {
        if ( this->stack.count() > 0 ) {
            this->stack.pop() ;
            return true ;
        }
        else
            return false ;
    }
    inline void backRoot() {
        this->stack.clear() ;
        this->stack.push( &this->root ) ;
    }
    inline void goTo( const QString& path ) {
        this->backRoot() ;
        for ( int i = 0 ; i < path.length() ; i++ ) {
            if ( !this->goStep( path[i] ) )
                break ;
        }
    }
    inline void buildTag( QChar tag ) {
        if ( this->hash.contains( tag ) )
            this->stack.push( this->stack.top()->appendChild( this->hash.value(tag) ) ) ;
    }
    inline void buildPath( const QString& path ) {
        this->backRoot() ;
        for ( int i = 0 ; i < path.length() ; i++ )
            this->buildTag( path[i] ) ;
    }
    inline void attachKey( const QString& key ) { this->stack.top()->appendKey( key ) ; }
    inline void insert( const QString& key ) {
        this->buildPath( key ) ;
        this->attachKey( key ) ;
    }
    inline bool removeEnd() { 
        if ( !this->stack.top()->useful() ) {
            QChar tag = this->stack.top()->tag ;
            if ( this->backStep() ) {
                this->stack.top()->removeChild( tag ) ;
                return true ;
            }
            else
                return false ;
        }
        else
            return false ;
    }
    inline void removeNode() {
        while( this->removeEnd() ) ;
    }
    inline int getKeys( QVector<QString>& keys ) {
        return this->stack.top()->seekKeys( keys ) ;
    }
} ;

#endif

