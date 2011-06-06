#include "adaptor.h"
#include "context.h"

#include <QApplication>

#include <QDebug>

namespace adaptor {

Adaptor::Adaptor( context::Context* context ) : QDBusAbstractAdaptor( context ), context( context ) {}

void Adaptor::receiveMessage( const QString& message ) {
    qDebug() << "received" << message ;
}

void Adaptor::receiveCommit( const QString& text ) {
    QWidget* widget = this->context->focusWidget() ;
    if ( widget ) {
        QInputMethodEvent event ;
        event.setCommitString( text ) ;
        this->context->sendEvent( event ) ;
    }
}

void Adaptor::receiveKeyEvent( int type, int keycode, int modifiers ) {
    qDebug() << "received keyevent" << type << keycode << modifiers ;
    QWidget* widget = this->context->focusWidget() ;
    if ( widget ) {
        QKeyEvent event( static_cast<QEvent::Type>(type), keycode, static_cast<Qt::KeyboardModifiers>(modifiers), "", false, 1 ) ;
        QApplication::sendEvent( widget, &event ) ;
    }
}

}
