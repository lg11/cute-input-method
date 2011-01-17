#include "record.h"

#include <string.h>

struct RecordList* recordlist_new( const char* pinyin ) {
    struct RecordList* list = malloc( sizeof( struct RecordList ) ) ;
    list->pinyin = strdup( pinyin ) ;
    list->head = NULL ;

    return list ;
}

struct RecordList* recordlist_add( const char* hanzi, double freq ) {
}
