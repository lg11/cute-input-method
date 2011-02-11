#include "backend.h"
#include <QDebug>

#include <Python.h>

static Backend* backend ;

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

static PyObject* get( PyObject* self, PyObject* args ) {
    int index ;
    int cacheIndex ;
    QueryCache* cache ;
    QString pinyin ;

    if ( ! PyArg_Parse( args, "(i)", &index ) )
        return NULL ;

    cacheIndex = backend->code.length() - 1 ;
    cache = &( backend->cache[cacheIndex] ) ;
    if ( cache->max > 0 ) {
        for ( ; cacheIndex >= 0 ; cacheIndex-- ) {
            cache = &( backend->cache[cacheIndex] ) ;
            if ( index < cache->max )
                break ;
            else 
                index = index - cache->max ;
            //qDebug() << index << cacheIndex ;
        }
        if ( cacheIndex >= 0 ) {
            cache = &( backend->cache[cacheIndex] ) ;
            cache->gen( index + 1 ) ;
            if ( index < cache->cand.count() ) {
                Record* record = cache->cand[index] ;
                pinyin = record->pinyin.join( "\'" ) ;
                //qDebug() << pinyin << record->hanzi ;
                return Py_BuildValue( "(ss)", pinyin.toUtf8().data(), record->hanzi.toUtf8().data() ) ;
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
    { NULL, NULL, 0, NULL }
} ;

PyMODINIT_FUNC initbackend() {
    backend = new Backend() ;

    (void) Py_InitModule( "backend", methods ) ;
}
