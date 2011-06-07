#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iconv.h>

#include "dict.c"

inline int read_record( FILE* fp, iconv_t handle, char* key, char* word, float* freq ) {
    char line[256] ;
    char buffer[256] ;
    char* src = buffer ;
    char* dest = word ;
    size_t len = 256 ;
    int result ;
    fgets( line, 256, fp ) ;
    result = sscanf( line, "%s %s %f\n", key, buffer, freq ) ;
    iconv( handle, &src, &len, &dest, &len ) ;
    return result ;
}

int dict_insert_record( record_h* dict, char* key, char* word, float freq ) {
    /*Record* record =*/
}

int main( int argc, char** argv ) {
    FILE* fp = fopen( "../../data/formated", "r" ) ;
    char key[256] ;
    char word[256] ;
    float freq ;
    int r ;
    /*iconv_t handle = iconv_open( "UCS-2", "UTF-8" ) ;*/
    iconv_t handle = iconv_open( "GBK", "UTF-8" ) ;
    record_h* dict = NULL ;

    while ( !feof( fp ) ) {
        r = read_record( fp, handle, key, word, &freq ) ;
    }

    iconv_close( handle ) ;
    fclose( fp ) ;

    return 0 ;
}
