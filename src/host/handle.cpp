#include "handle.h"
#include "host.h"
#include "../engine/engine.h"

#include <QDebug>

namespace handle {

Handle::Handle( host::Host* host, engine::Engine* engine, QObject* parent ) : 
    QObject( parent ),
    host( host ),
    engine( engine ),
    pressCount( 0 ) {
    //this->modifiers = NoModifier ;
}

bool Handle::processKeyPress( int keycode ) {
    //qDebug() << "handle" << keycode ;
    this->pressCount++ ;
    bool flag = false ;

    if ( this->host->inputLanguage == host::SimplifiedChinese ) {
        if ( keycode >= Qt::Key_A && keycode <= Qt::Key_Z ) {
            keycode = keycode + 'a' - Qt::Key_A  ;
            QChar code( keycode )  ;
            flag = this->engine->appendCode( code ) ;
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
        else if ( keycode == 16777234 ) {
            flag = this->engine->select( 1 ) ;
            if ( flag )
                this->engine->checkCommit() ;
        }
        else if ( keycode == 16777237 ) {
            flag = this->engine->select( 2 ) ;
            if ( flag )
                this->engine->checkCommit() ;
        }
        else if ( keycode == 16777236 ) {
            flag = this->engine->select( 3 ) ;
            if ( flag )
                this->engine->checkCommit() ;
        }
        else if ( keycode == 16777248 ) {
            if ( this->engine->getCodeLength() > 0 ) {
                this->engine->nextPage() ;
                flag = true ;
            }
        }
        else if ( keycode == 16781571 ) {
            if ( this->engine->getCodeLength() > 0 ) {
                this->engine->prevPage() ;
                flag = true ;
            }
        }
#endif
#ifdef Q_WS_MAEMO_5
        else if ( keycode == 16777249 ) {
            this->pressCount = 0 ;
        }
#endif
    }
    else if ( this->host->inputLanguage == host::UnknownLanguage ) {
#ifdef Q_WS_MAEMO_5
        if ( keycode == 16777249 ) {
            this->pressCount = 0 ;
        }
#endif
    }

    if ( flag )
        emit this->engine->candidateUpdate() ;
    return flag ;
}

bool Handle::processKeyRelease( int keycode ) {
#ifdef Q_WS_MAEMO_5
    if ( keycode == 16777249 ) {
        //this->modifiers = NoModifier ;
        if ( this->pressCount < 1 ) {
            if ( this->host->inputLanguage == host::SimplifiedChinese ) {
                this->host->setInputLanguage( host::UnknownLanguage ) ;
                this->engine->reset() ;
                emit this->engine->candidateUpdate() ;
            }
            else if ( this->host->inputLanguage == host::UnknownLanguage ) {
                this->host->setInputLanguage( host::SimplifiedChinese ) ;
                this->engine->reset() ;
                emit this->engine->candidateUpdate() ;
            }
        }
    }
#endif
    return false ;
}

void Handle::requestReset() {
    this->engine->reset() ;
}

void Handle::setKeyboardLayout( int layout ) {
    this->engine->setKeyboardLayout( layout ) ;
}

}

