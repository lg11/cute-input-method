#include "handle.h"
#include "../engine/engine.h"

#include <QDebug>

namespace handle {

Handle::Handle( engine::Engine* engine, QObject* parent ) : QObject( parent ), engine(engine) {
    this->pressCount = 0 ;
    //this->modifiers = NoModifier ;
    this->flag = true ;
}

bool Handle::processKeyPress( int keycode ) {
    this->pressCount++ ;
    if ( !this->flag ) {
        return false ;
    }
    bool flag = false ;
    //qDebug() << "handle" << keycode ;
    if ( keycode >= Qt::Key_A && keycode <= Qt::Key_Z ) {
        keycode = keycode + 'a' - Qt::Key_A  ;
        QChar code( keycode )  ;
        flag = this->engine->appendCode( code ) ;
        //qDebug() << "handle" << flag ;
    }
    else if ( keycode == Qt::Key_Backspace ) {
        flag = this->engine->deselect() ? true : this->engine->popCode() ;
    }
    else if ( keycode == Qt::Key_Space ) {
        flag = this->engine->select( 0 ) ;
        if ( flag )
            this->engine->checkCommit() ;
    }
    else if ( keycode >= Qt::Key_1 && keycode <= Qt::Key_5 ) {
        keycode = keycode - Qt::Key_1 ;
        flag = this->engine->select( keycode ) ;
        if ( flag )
            this->engine->checkCommit() ;
    }
    else if ( keycode == Qt::Key_Return || keycode == Qt::Key_Enter ) {
        if ( this->engine->getCodeLength() > 0 ) {
            emit this->engine->sendCommit( this->engine->getCode() ) ;
            this->engine->reset() ;
            flag = true ;
        }
    }
    else if ( keycode == Qt::Key_Minus ) {
        if ( this->engine->getCodeLength() > 0 ) {
            this->engine->prevPage() ;
            flag = true ;
        }
    }
    else if ( keycode == Qt::Key_Equal ) {
        if ( this->engine->getCodeLength() > 0 ) {
            this->engine->nextPage() ;
            flag = true ;
        }
    }
#ifdef Q_WS_MAEMO_5
    //else if ( keycode == 16777249 ) {
        //this->modifiers |= CtrlModifier ;
    //}
#endif
    if ( flag )
        emit this->engine->candidateUpdate() ;
    return flag ;
}

bool Handle::processKeyRelease( int keycode ) {
#ifdef Q_WS_MAEMO_5
    if ( keycode == 16777249 ) {
        //this->modifiers = NoModifier ;
        if ( this->pressCount <= 2 ) {
            this->flag = !this->flag ;
            this->queryStatus() ;
            this->engine->reset() ;
            emit this->engine->candidateUpdate() ;
        }
    }
#endif
    this->pressCount = 0 ;
    return false ;
}

bool Handle::setKeyboardLayout( int layout ) {
    return this->engine->setKeyboardLayout( layout ) ;
}

void Handle::queryStatus() {
    qDebug( "queryStatus" ) ;
    if ( this->flag )
        emit this->sendStatus( 1 ) ;
    else
        emit this->sendStatus( 0 ) ;
}

}

