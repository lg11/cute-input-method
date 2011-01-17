#include "node.h"

#include <stdlib.h>

struct Node* node_new( char code ) {
    struct Node* node = malloc( sizeof( struct Node ) ) ;
    node->code = code ;
    node->child = NULL ;
    node->child_count = 0 ;
    return node ;
}

struct Node* node_find( struct Node* node, char code ) {
    char flag = 0 ;
    int i = 0 ;
    while ( i < node->child_count && !flag ) {
        if ( node->child[i]->code == code )
            flag = 1 ;
        else
            i++ ;
    }
    if ( flag )
        return node->child[i] ;
    else 
        return NULL ;
}

struct Node* node_add( struct Node* node, char code ) {
    struct Node* result = node_find( node, code ) ;
    if ( result ) 
        return result ;
    else {
        result = node_new( code ) ;
        if ( node->child_count )
            node->child = realloc( node->child, ( node->child_count + 1 ) * sizeof( struct Node* ) ) ;
        else 
            node->child = malloc( sizeof( struct Node* ) ) ;
        node->child[node->child_count] = result ;
        node->child_count++ ;
    }
}
