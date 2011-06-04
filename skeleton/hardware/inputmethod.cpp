#include <mabstractinputmethodhost.h>
#include <mimgraphicsview.h>
#include <QGraphicsView>

#include "inputmethod.h"

#include <QDebug>

namespace inputmethod {

class InputMethodPrivate {
public :
    Q_DECLARE_PUBLIC( InputMethod ) ;
    InputMethod* const q_ptr ;
    InputMethodPrivate( InputMethod* inputmethod ) : q_ptr( inputmethod ) {}
    ~InputMethodPrivate() {
    }
} ;

InputMethod::InputMethod( MAbstractInputMethodHost *host, QWidget *mainWindow ) : MAbstractInputMethod( host, mainWindow ), d_ptr( new InputMethodPrivate( this ) ) {
    qDebug() << "construct" ;
}

InputMethod::~InputMethod() { delete this->d_ptr ; }

void InputMethod::show() {
    this->inputMethodHost()->setRedirectKeys( true ) ;
    qDebug() << "show" ;
}

void InputMethod::hide() {
    qDebug() << "hide" ;
}

void InputMethod::update() {
    qDebug() << "update" ;
}

void InputMethod::handleFocusChange( bool focusIn ) {
    qDebug() << "focus" << focusIn ;
}

void InputMethod::processKeyEvent( QEvent::Type keyType, Qt::Key keyCode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count, quint32 nativeScanCode, quint32 nativeModifiers, unsigned long time) {
    QObject::connect( this, SIGNAL(processKeyEvent()), this, SLOT(message()));
    qDebug() << "processKeyEvent" ;
}

bool InputMethod::imExtensionEvent( MImExtensionEvent* event ) {
    QObject::connect( this, SIGNAL(imExtensionEvent()), this, SLOT(message()));
    qDebug() << "imExtensionEvent" ;
    return false ;
}

}
