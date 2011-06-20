#include "handle.h"
#include "host.h"
#include "../engine/engine.h"

#include <QDebug>

namespace handle {

#ifdef Q_WS_MAEMO_5
inline QChar punc( host::InputLanguage language, int keycode ) {
    if ( language == host::UnknownLanguage ) {
        switch ( keycode ) {
        case Qt::Key_1 :
            return QChar('1') ;
        case Qt::Key_2 :
            return QChar('2') ;
        case Qt::Key_3 :
            return QChar('3') ;
        case Qt::Key_4 :
            return QChar('4') ;
        case Qt::Key_5 :
            return QChar('5') ;
        case Qt::Key_6 :
            return QChar('6') ;
        case Qt::Key_7 :
            return QChar('7') ;
        case Qt::Key_8 :
            return QChar('8') ;
        case Qt::Key_9 :
            return QChar('9') ;
        case Qt::Key_0 :
            return QChar('0') ;
        //case Qt::Key_Comma :
            //return QChar(',') ;
        //case Qt::Key_Semicolon :
            //return QChar(';') ;
        case Qt::Key_Equal :
            return QChar('=') ;
        case Qt::Key_Asterisk :
            return QChar('*') ;
        case Qt::Key_Plus :
            return QChar('+') ;
        case Qt::Key_NumberSign :
            return QChar('#') ;
        case Qt::Key_Minus :
            return QChar('-') ;
        case Qt::Key_Underscore :
            return QChar('_') ;
        case Qt::Key_ParenLeft :
            return QChar('(') ;
        case Qt::Key_ParenRight :
            return QChar(')') ;
        case Qt::Key_Ampersand :
            return QChar('&') ;
        case Qt::Key_Exclam :
            return QChar('!') ;
        //case Qt::Key_Period :
            //return QChar('.') ;
        //case Qt::Key_Colon :
            //return QChar(':') ;
        case Qt::Key_Question :
            return QChar('?') ;
        case 163 :
            return QChar('|') ;
        case Qt::Key_Dollar :
            return QChar('$') ;
        case 8364 :
            return QChar('%') ;
        case Qt::Key_Slash :
            return QChar('/') ;
        case Qt::Key_Backslash :
            return QChar('\\') ;
        case Qt::Key_QuoteDbl :
            return QChar('"') ;
        case Qt::Key_Apostrophe :
            return QChar('\'') ;
        case Qt::Key_At :
            return QChar('@') ;
        case Qt::Key_Q :
            return QChar('1') ;
        case Qt::Key_W :
            return QChar('2') ;
        case Qt::Key_E :
            return QChar('3') ;
        case Qt::Key_R :
            return QChar('4') ;
        case Qt::Key_T :
            return QChar('5') ;
        case Qt::Key_Y :
            return QChar('6') ;
        case Qt::Key_U :
            return QChar('7') ;
        case Qt::Key_I :
            return QChar('8') ;
        case Qt::Key_O :
            return QChar('9') ;
        case Qt::Key_P :
            return QChar('0') ;
        case Qt::Key_Comma :
            return QChar('=') ;
        case Qt::Key_A :
            return QChar('*') ;
        case Qt::Key_S :
            return QChar('+') ;
        case Qt::Key_D :
            return QChar('#') ;
        case Qt::Key_F :
            return QChar('-') ;
        case Qt::Key_G :
            return QChar('_') ;
        case Qt::Key_H :
            return QChar('(') ;
        case Qt::Key_J :
            return QChar(')') ;
        case Qt::Key_K :
            return QChar('&') ;
        case Qt::Key_L :
            return QChar('!') ;
        case Qt::Key_Period :
            return QChar('?') ;
        case Qt::Key_Z :
            return QChar('|') ;
        case Qt::Key_X :
            return QChar('$') ;
        case Qt::Key_C :
            return QChar('%') ;
        case Qt::Key_V :
            return QChar('/') ;
        case Qt::Key_B :
            return QChar('\\') ;
        case Qt::Key_N :
            return QChar('"') ;
        case Qt::Key_M :
            return QChar('\'') ;
        case Qt::Key_Space :
            return QChar('@') ;
        default :
            return QChar('\0') ;
        }
    }
    else if ( language == host::SimplifiedChinese ) {
        switch ( keycode ) {
        case Qt::Key_1 :
            return QChar('1') ;
        case Qt::Key_2 :
            return QChar('2') ;
        case Qt::Key_3 :
            return QChar('3') ;
        case Qt::Key_4 :
            return QChar('4') ;
        case Qt::Key_5 :
            return QChar('5') ;
        case Qt::Key_6 :
            return QChar('6') ;
        case Qt::Key_7 :
            return QChar('7') ;
        case Qt::Key_8 :
            return QChar('8') ;
        case Qt::Key_9 :
            return QChar('9') ;
        case Qt::Key_0 :
            return QChar('0') ;
        //case Qt::Key_Comma :
            //return QChar(',') ;
        //case Qt::Key_Semicolon :
            //return QChar(';') ;
        case Qt::Key_Equal :
            return QChar('=') ;
        case Qt::Key_Asterisk :
            return QChar('*') ;
        case Qt::Key_Plus :
            return QChar('+') ;
        case Qt::Key_NumberSign :
            return QChar('#') ;
        case Qt::Key_Minus :
            return QChar('-') ;
        case Qt::Key_Underscore :
            return QChar('_') ;
        case Qt::Key_ParenLeft :
            return QChar('(') ;
        case Qt::Key_ParenRight :
            return QChar(')') ;
        case Qt::Key_Ampersand :
            return QChar('&') ;
        case Qt::Key_Exclam :
            return QChar('!') ;
        //case Qt::Key_Period :
            //return QChar('.') ;
        //case Qt::Key_Colon :
            //return QChar(':') ;
        case Qt::Key_Question :
            return QChar('?') ;
        case 163 :
            return QChar('|') ;
        case Qt::Key_Dollar :
            return QChar('$') ;
        case 8364 :
            return QChar('%') ;
        case Qt::Key_Slash :
            return QChar('/') ;
        case Qt::Key_Backslash :
            return QChar('\\') ;
        case Qt::Key_QuoteDbl :
            return QChar('"') ;
        case Qt::Key_Apostrophe :
            return QChar('\'') ;
        case Qt::Key_At :
            return QChar('@') ;
        case Qt::Key_Q :
            return QChar('1') ;
        case Qt::Key_W :
            return QChar('2') ;
        case Qt::Key_E :
            return QChar('3') ;
        case Qt::Key_R :
            return QChar('4') ;
        case Qt::Key_T :
            return QChar('5') ;
        case Qt::Key_Y :
            return QChar('6') ;
        case Qt::Key_U :
            return QChar('7') ;
        case Qt::Key_I :
            return QChar('8') ;
        case Qt::Key_O :
            return QChar('9') ;
        case Qt::Key_P :
            return QChar('0') ;
        case Qt::Key_Comma :
            return QChar('=') ;
        case Qt::Key_A :
            return QChar('*') ;
        case Qt::Key_S :
            return QChar('+') ;
        case Qt::Key_D :
            return QChar('#') ;
        case Qt::Key_F :
            return QChar('-') ;
        case Qt::Key_G :
            return QChar('_') ;
        case Qt::Key_H :
            return QChar('(') ;
        case Qt::Key_J :
            return QChar(')') ;
        case Qt::Key_K :
            return QChar('&') ;
        case Qt::Key_L :
            return QChar('!') ;
        case Qt::Key_Period :
            return QChar('?') ;
        case Qt::Key_Z :
            return QChar('|') ;
        case Qt::Key_X :
            return QChar('$') ;
        case Qt::Key_C :
            return QChar('%') ;
        case Qt::Key_V :
            return QChar('/') ;
        case Qt::Key_B :
            return QChar('\\') ;
        case Qt::Key_N :
            return QChar('"') ;
        case Qt::Key_M :
            return QChar('\'') ;
        case Qt::Key_Space :
            return QChar('@') ;
        default :
            return QChar('\0') ;
        }
    }
    return QChar( '\0' ) ;
}
#endif

Handle::Handle( host::Host* host, engine::Engine* engine, QObject* parent ) : 
    QObject( parent ),
    host( host ),
    engine( engine ),
    modifiers( NoModifier ), 
    pressCount( 0 ) {
#ifdef Q_WS_MAEMO_5
    this->fnPressed = false ;
    this->shiftPressed = false ;
#endif
}

bool Handle::processKeyPress( int keycode ) {
    //qDebug() << "handle" << keycode ;
    this->pressCount++ ;

#ifdef Q_WS_MAEMO_5
    //if ( this->engine->getCodeLength() <= 0 ) {
        if ( keycode == 16777249 ) {
            this->pressCount = 0 ;
            this->modifiers |= CtrlModifier ;
            return false ;
        }
        else if ( this->modifiers & CtrlModifier ) {
            return false ;
        }
    //}
        
    if ( keycode == 16781571 ) {
        this->pressCount = 0 ;
        this->fnPressed = true ;
        this->modifiers |= FnModifier ;
        return true ;
    }

    if ( this->modifiers & FnModifier ) {
        QChar ch( punc( this->host->inputLanguage, keycode ) ) ;
        if ( ch != QChar( '\0' ) )
            emit this->engine->sendCommit( ch ) ;
        return true ;
    }

#endif
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
                this->engine->prevPage( 4 ) ;
                flag = true ;
            }
        }
        else if ( keycode == Qt::Key_Equal ) {
            if ( this->engine->getCodeLength() > 0 ) {
                this->engine->nextPage( 4 ) ;
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
                this->engine->nextPage( 4 ) ;
                flag = true ;
            }
        }
        else if ( keycode == 16781571 ) {
            if ( this->engine->getCodeLength() > 0 ) {
                this->engine->prevPage( 4 ) ;
                flag = true ;
            }
        }
#endif
    }
    else if ( this->host->inputLanguage == host::UnknownLanguage ) {
    }

    if ( flag )
        emit this->engine->candidateUpdate() ;
    return flag ;
}

bool Handle::processKeyRelease( int keycode ) {
#ifdef Q_WS_MAEMO_5
    if ( keycode == 16777249 ) {
        this->modifiers &= (~CtrlModifier) ;
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
        return false ;
    }
    else if ( keycode == 16781571 ) {
        this->fnPressed = false ;
        if ( this->pressCount > 0 ) {
            this->modifiers &= (~FnModifier) ;
        }
        //return true ;
    }
    else if ( ( this->modifiers & FnModifier ) && ( !this->fnPressed ) ) {
            this->modifiers &= (~FnModifier) ;
        //return true ;
    }
#endif
    return false ;
}

void Handle::requestReset() {
    this->pressCount = 0 ;
    this->modifiers = NoModifier ;
#ifdef Q_WS_MAEMO_5
    this->fnPressed = false ;
    this->shiftPressed = false ;
#endif
    this->engine->reset() ;
}

void Handle::setKeyboardLayout( int layout ) {
    this->engine->setKeyboardLayout( layout ) ;
}

}

