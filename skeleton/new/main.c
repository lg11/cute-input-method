#include "pinyin.h"

#include <QDebug>

int main( int argc, char** argv ) {
    Pinyin pinyin ;

    for ( quint16 i = 0 ; i < pinyinListLength ; i++ ) {
        p = pinyin->list[i] ;
        /*quint index = pinyinMap*/
        printf( "%s\n", p ) ;
    }
}
