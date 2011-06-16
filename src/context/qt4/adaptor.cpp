#include "adaptor.h"
#include "context.h"

#include <QApplication>

//#include <QDebug>

namespace adaptor {

Adaptor::Adaptor( context::Context* context ) : QDBusAbstractAdaptor( context ), context( context ) {}

void Adaptor::receiveMessage( const QString& message ) {
    //qDebug() << "received" << message ;
    Q_UNUSED( message ) ;
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
    //qDebug() << "received keyevent" << type << keycode << modifiers ;
    QWidget* widget = this->context->focusWidget() ;
    if ( widget ) {
        QKeyEvent event( static_cast<QEvent::Type>(type), keycode, static_cast<Qt::KeyboardModifiers>(modifiers), "", false, 1 ) ;
        QApplication::sendEvent( widget, &event ) ;
    }
}

void Adaptor::replaceSurrounding( const QString& text ) {
    QWidget* widget = this->context->focusWidget() ;
    if ( widget ) {
        QVariant result( widget->inputMethodQuery( Qt::ImSurroundingText ) ) ;
        if ( result.isValid() ) {
            QString surrounding( result.toString() ) ;
            result = ( widget->inputMethodQuery( Qt::ImCursorPosition ) ) ;
            int position = result.toInt() ;
            QInputMethodEvent event ;
            event.setCommitString( text, -position, surrounding.length() ) ;
            QApplication::sendEvent( widget, &event ) ;
            //qDebug() << surrounding ;
        }
    }
}

void Adaptor::querySurrounding() {
    QWidget* widget = this->context->focusWidget() ;
    if ( widget ) {
        QVariant result( widget->inputMethodQuery( Qt::ImSurroundingText ) ) ;
        if ( result.isValid() ) {
            QString surrounding( result.toString() ) ;
            emit this->sendSurrounding( surrounding ) ;
            //qDebug() << surrounding ;
        }
    }
}

void Adaptor::queryCursorRect() {
    //qDebug() << "queryCursorRect" << this->context->cursorRect ;
    this->context->update() ;
    emit this->cursorRectUpdate( this->context->cursorRect.x(), this->context->cursorRect.y(), this->context->cursorRect.width(), this->context->cursorRect.height() ) ;
}

}
