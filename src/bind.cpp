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

static PyObject* get( PyObject* self, PyObject* args ) {
    int index ;
    QString pinyin ;
    QueryCache* cache ;

    if ( ! PyArg_Parse( args, "(i)", &index ) )
        return NULL ;

    cache = &( backend->cache[ backend->code.length() - 1 ] ) ;
    cache->gen( index + 1 ) ;
    if ( index < cache->cand.count() ) {
        Record* record = cache->cand[index] ;
        pinyin = record->pinyin.join( "\'" ) ;
        //qDebug() << pinyin ;
        return Py_BuildValue( "(ss)", pinyin.toUtf8().data(), record->hanzi.toUtf8().data() ) ;
    }
    else {
        return Py_None ;
    }
}

static struct PyMethodDef methods[] = {
    { "load", load, METH_VARARGS, "load dict" } ,
    { "append", append, METH_VARARGS, "append code" } ,
    { "get", get, METH_VARARGS, "get cand" } ,
    { NULL, NULL, 0, NULL }
} ;

PyMODINIT_FUNC initbackend() {
    backend = new Backend() ;

    (void) Py_InitModule( "backend", methods ) ;
}
