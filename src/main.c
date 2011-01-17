#include "node.h"
#include "record.h"

#include <stdio.h>

int main( int argc, char** argv ) {
    struct Node* node = node_new( 'c' ) ;
    struct Node* result ;
    struct RecordList* list = recordlist_new( "zhi" ) ;
    
    printf( "pinyin = %s\n", list->pinyin ) ;
    printf( "code = %c\n", node->code ) ;
    node_add( node, 'a' ) ;
    node_add( node, 'b' ) ;
    node_add( node, 'b' ) ;

    result = node_find( node, 'b' ) ;
    printf( "code = %c\n", result->code ) ;
    result = node_find( node, 'a' ) ;
    printf( "code = %c\n", result->code ) ;

    return 0 ;
}
