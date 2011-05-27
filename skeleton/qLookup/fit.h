#ifndef FIT_H
#define FIT_H

//#include "split.h"
//#include "dich.h"
#include <QHash>
#include <QString>
#include <QList>

#include <QDebug>

namespace fit {

typedef QHash< QString, QList<QString>  > KeyMap ;

inline void add_key( KeyMap* map, const QString& key ) {
    QString path( key.at(0) ) ;
    int i = key.indexOf( "'" ) ;
    while ( i > 0 ) {
        i++ ;
        path.append( key.at(i) ) ;
        i = key.indexOf( "'", i ) ;
    }
    (*map)[path].append( key ) ;
    //qDebug() << key << path ;
}

inline QList<QString>* get_keys( KeyMap* map, const QString& path ) {
    return map->contains( path ) ? &((*map)[path]) : NULL ;
}

inline void check_string( QStringList* string, const QString& key, bool* flag, int* fit_point ) {
    *flag = true ;
    *fit_point = 0 ;
    QStringList l( key.split( "'" ) ) ;
    for i in range( len(s) ) :
        #print s[i], pinyinString[i]
        if s[i] == pinyinString[i] :
            pass
        else :
            currentFitPoint -= 1
            l = len( pinyinString[i] )
            if l > len( s[i] ) :
                flag = False
                break
            elif pinyinString[i] in self.pinyinSet and i < len(s) - 1 :
                if pinyinString[i] in self.extraSet :
                    if s[i][:l] != pinyinString[i][:l] :
                        flag = False
                        break
                else :
                    flag = False
                    break
            else :
                #print s[i][:l], pinyinString[i][:l]
                if s[i][:l] != pinyinString[i][:l] :
                    flag = False
                    break
    #print currentFitPoint, key, flag
    if flag :
        if currentFitPoint >= 0 :
            results = [ key ]
            fitPoint = 0
            #hasFullFit = True
            break
        elif currentFitPoint > fitPoint :
            results = [ key ]
            fitPoint = currentFitPoint
        elif currentFitPoint == fitPoint :
            results.append( key )
}

inline void fit( QStringList* string, QList<QString*>* result, QSet<QString>* key_set, KeyMap* key_map ) {
    QString path ;
    foreach ( const QString& s, *string )
        path.append( s.at(0) ) ;

    QList<QString>* keys = get_keys( key_map, path ) ;
    int highest_point = -0x1000 ;
    bool flag = true ;
    foreach( const QString& key, keys ) {
        int fit_point = 0 ;
        QStringList l( key.split( "'" ) ) ;
        for ( int i = 0 ; i < l.length() ; i++ ) {
            if ( l.at(i) == string_list.at(i) )
                ;
            else {
                fit_point-- ;
                if ( string_list.at(i).length() > l.at(i).length() ) {
                    flag = false ;
                    break ;
                }
                else if ( key_set->contains( string_list.at(i) ) && i < l.length() - 1 ) {
                    if ( string_list

                        //if pinyinString[i] in self.extraSet :
                            //if s[i][:l] != pinyinString[i][:l] :
                                //flag = False
                                //break
                        //else :
                            //flag = False
                            //break
                    //else :
                        //#print s[i][:l], pinyinString[i][:l]
                        //if s[i][:l] != pinyinString[i][:l] :
                            //flag = False
                            //break
            //#print currentFitPoint, key, flag
            //if flag :
                //if currentFitPoint >= 0 :
                    //results = [ key ]
                    //fitPoint = 0
                    //#hasFullFit = True
                    //break
                //elif currentFitPoint > fitPoint :
                    //results = [ key ]
                    //fitPoint = currentFitPoint
                //elif currentFitPoint == fitPoint :
                    //results.append( key )
        //#print "-----end-----"
        //return fitPoint, results
//#endif
}

}

#endif
