#include "backend.h"
#include <QDebug>

#include <Python.h>

static Backend* backend ;
static int pinyinCacheIndex ;
static int pinyinIndex ;


static PyObject* load( PyObject* self, PyObject* args ) {
    char* path ;

    if ( ! PyArg_Parse( args, "(s)", &path ) )
        return NULL ;

    backend->load( path ) ;
    //qDebug() << path ;

    return Py_None ;
}

static PyObject* append( PyObject* self, PyObject* args ) {
    char* code ;

    if ( ! PyArg_Parse( args, "(s)", &code ) )
        return NULL ;

    backend->append( code[0] ) ;
    //qDebug() << path ;

    return Py_None ;
}

static PyObject* pop( PyObject* self, PyObject* args ) {
    backend->pop() ;
    return Py_None ;
}

static PyObject* clear( PyObject* self, PyObject* args ) {
    backend->clear() ;
    return Py_None ;
}

static PyObject* getPinyin( PyObject* self, PyObject* args ) {
    int index ;
    int cacheIndex ;
    QueryCache* cache ;
    QString pinyin ;

    if ( ! PyArg_Parse( args, "(i)", &index ) )
        return NULL ;

    cacheIndex = backend->code.length() - 1 ;
    cache = &( backend->cache[cacheIndex] ) ;
    if ( cache->list.count() > 0 ) {
        if ( index < cache->list.count() ) 
            ;
        else {
            index = index - cache->list.count() ;
            cacheIndex-- ;
            while ( cacheIndex >= 0 ) {
                cache = &( backend->cache[cacheIndex] ) ;
                if ( cache->flag ) {
                    if ( index < cache->list.count() )
                        break ;
                    else
                        index = index - cache->list.count() ;
                }
                cacheIndex-- ;
                //qDebug() << index << cacheIndex << cache->flag ;
            }
        }
        //qDebug() << index << cacheIndex << cache->flag ;
        if ( cacheIndex >= 0 ) {
            cache = &( backend->cache[cacheIndex] ) ;
            if ( index < cache->list.count() ) {
                RecordList* list = cache->list[index] ;
                pinyin = list->pinyin.join( QChar( '\'' ) ) ;
                //qDebug() << pinyin ;
                return Py_BuildValue( "s", pinyin.toUtf8().data() ) ;
            }
        }
    }
    return Py_None ;
}

static PyObject* setPinyin( PyObject* self, PyObject* args ) {
    char* buffer ;
    int cacheIndex ;
    int index ;
    bool flag = false ;
    QueryCache* cache ;

    if ( ! PyArg_Parse( args, "(s)", &buffer ) )
        return NULL ;

    QString s( buffer ) ;
    if ( s.count() <= 0 ) {
        pinyinCacheIndex = -1 ;
        pinyinIndex = -1 ;
        return Py_None ;
    }
    QStringList pinyin = s.split( '\'' ) ;
    
    //qDebug() << "select" << pinyin ;
    cacheIndex = backend->code.length() - 1 ;
    cache = &( backend->cache[cacheIndex] ) ;
    if ( cache->list.count() > 0 ) {
        for ( index = 0 ; index < cache->list.count() ; index++ ) {
            RecordList* list = cache->list[index] ;
            if ( pinyin == list->pinyin ) {
                flag = true ;
                break ;
            }
        }
        if ( flag ) 
            ;
        else {
            cacheIndex-- ;
            while ( cacheIndex >= 0 ) {
                cache = &( backend->cache[cacheIndex] ) ;
                if ( cache->flag ) {
                    for ( index = 0 ; index < cache->list.count() ; index++ ) {
                        RecordList* list = cache->list[index] ;
                        if ( pinyin == list->pinyin ) {
                            flag = true ;
                            break ;
                        }
                    }
                }
                if ( flag )
                    break ;
                else
                    cacheIndex-- ;
            }
        }
    }

    if ( flag ) {
        pinyinCacheIndex = cacheIndex ;
        pinyinIndex = index ;
        //cache = &( backend->cache[cacheIndex] ) ;
        //RecordList* list = cache->list[index] ;
        //qDebug() << list->pinyin ;
    }

    return Py_None ;
}

static PyObject* get( PyObject* self, PyObject* args ) {
    int index ;
    int cacheIndex ;
    QueryCache* cache ;
    QString pinyin ;

    if ( ! PyArg_Parse( args, "(i)", &index ) )
        return NULL ;

    if ( pinyinCacheIndex >= 0 ) {
        cacheIndex = pinyinCacheIndex ;
        cache = &( backend->cache[cacheIndex] ) ;
        Record* record = cache->get( pinyinIndex, index ) ;
        if ( record ) {
            pinyin = record->pinyin.join( QChar( '\'' ) ) ;
            return Py_BuildValue( "(ss)", pinyin.toUtf8().data(), record->hanzi.toUtf8().data() ) ;
        }
        else
            return Py_None ;
        
    }
    cacheIndex = backend->code.length() - 1 ;
    cache = &( backend->cache[cacheIndex] ) ;
    if ( cache->max > 0 ) {
        if ( index < cache->max ) 
            ;
        else {
            index = index - cache->max ;
            cacheIndex-- ;
            while ( cacheIndex >= 0 ) {
                cache = &( backend->cache[cacheIndex] ) ;
                if ( cache->flag ) {
                    if ( index < cache->max )
                        break ;
                    else
                        index = index - cache->max ;
                }
                cacheIndex-- ;
                //qDebug() << index << cacheIndex << cache->flag ;
            }
        }
        //qDebug() << index << cacheIndex << cache->flag ;
        if ( cacheIndex >= 0 ) {
            cache = &( backend->cache[cacheIndex] ) ;
            cache->gen( index + 1 ) ;
            if ( index < cache->cand.count() ) {
                Record* record = cache->cand[index] ;
                pinyin = record->pinyin.join( QChar( '\'' ) ) ;
                //qDebug() << pinyin << record->hanzi ;
                return Py_BuildValue( "(ss)", pinyin.toUtf8().data(), record->hanzi.toUtf8().data() ) ;
                //return Py_BuildValue( "(u#u#)", pinyin.data(), pinyin.count(), record->hanzi.data(), record->hanzi.count() ) ;
            }
        }
    }
    return Py_None ;
}

static struct PyMethodDef methods[] = {
    { "load", load, METH_VARARGS, "load dict" } ,
    { "append", append, METH_VARARGS, "append code" } ,
    { "pop", pop, METH_VARARGS, "pop code" } ,
    { "clear", clear, METH_VARARGS, "clear code" } ,
    { "get", get, METH_VARARGS, "get cand" } ,
    { "setPinyin", setPinyin, METH_VARARGS, "set pinyin" } ,
    { "getPinyin", getPinyin, METH_VARARGS, "get pinyin" } ,
    { NULL, NULL, 0, NULL }
} ;

PyMODINIT_FUNC initbackend() {
    backend = new Backend() ;
    pinyinCacheIndex = -1 ;
    pinyinIndex = -1 ;

    (void) Py_InitModule( "backend", methods ) ;
}
