#ifndef __BACKEND_H
#define __BACKEND_H

#include "codemap.h"
#include "seeker.h"
#include "cache.h"

class Backend {
public :
    CodeMap map ;
    Seeker seeker ;
    QVector<QueryCache> cache ;
    QString code ;
    
    Backend() { this->seeker.setStart( this->map.root ) ; }
    void load( QString file_path ) ;
    void append( QChar code ) ;
    void pop() ;
} ;

#endif
