#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int read_record( FILE* fp, char* key, char* word, float* freq ) {
    char line[512] ;
    fgets( line, 512, fp ) ;
    return sscanf( line, "%s %s %f\n", key, word, &freq ) ;
}

int main( int argc, char** argv ) {
    FILE* fp = fopen( "../../data/formated", "r" ) ;
    char key[256] ;
    char word[256] ;
    float freq ;
    int r ;

    while ( !feof( fp ) ) {
        r = read_record( fp, key, word, &freq ) ;
        /*printf( "line %d : %s %s %f\n", i, key, word, freq ) ;*/
        /*printf( "%d\n", r ) ;*/
    }

    fclose( fp ) ;

    return 0 ;
}
