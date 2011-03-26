#include "dict.h"


QDebug operator<<( QDebug dbg, const WordRecordList& l ) {
    dbg.nospace() << "{ " ;
    for ( int i = 0 ; i < l.length() ; i++ ) { 
        const WordRecord& r = l.data.at(i) ;
        dbg.nospace() << "( " << r->word << ", " << r->freq << " ) ";
    }
    dbg.nospace() << "}" ;
    return dbg.space();
}
