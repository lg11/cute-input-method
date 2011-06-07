#include "context.h"
#include "adaptor.h"

#include <QDBusConnection>
#include <QDBusReply>

#include <QDebug>

namespace context {

Context::Context( QObject* parent ) :
    QInputContext( parent ), 
    adaptor( new adaptor::Adaptor( this ) ),
    interface( new QDBusInterface( "me.inputmethod.host", "/host", "inputmethod.host", QDBusConnection::sessionBus(), this ) ) {

    QDBusConnection::sessionBus().registerService( "me.inputmethod.context" ) ;
    QDBusConnection::sessionBus().registerObject( "/context", this ) ;

    QDBusConnection::sessionBus().connect( "", "", "inputmethod.host", "sendCommit", this->adaptor, SLOT(receiveCommit( const QString& )) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.host", "sendKeyEvent", this->adaptor, SLOT(receiveKeyEvent( int, int, int )) ) ;

}

bool Context::filterEvent( const QEvent* event ) {
    if ( event->type() == QEvent::KeyPress ) {
        emit this->adaptor->sendMessage( "KeyPress" ) ;
        if ( this->interface->isValid() ) {
            const QKeyEvent* keyevent = static_cast<const QKeyEvent*>(event) ;
            QDBusReply<bool> result = this->interface->call( "keyPress", (int)( keyevent->key() ), (int)( keyevent->modifiers() ) ) ;
            return result.isValid() ? result.value() : false ;
        }
    }
    else if ( event->type() == QEvent::KeyRelease ) {
        emit this->adaptor->sendMessage( "KeyRelease" ) ;
        if ( this->interface->isValid() ) {
            const QKeyEvent* keyevent = static_cast<const QKeyEvent*>(event) ;
            QDBusReply<bool> result = this->interface->call( "keyRelease", (int)(keyevent->key()), (int)(keyevent->modifiers()) ) ;
            return result.isValid() ? result.value() : false ;
        }
    }
    else if ( event->type() == QEvent::RequestSoftwareInputPanel ) {
        emit this->adaptor->sendMessage( "RequestSoftwareInputPanel" ) ;
        emit this->adaptor->requestSoftwareInputPanel() ;
    }
    else if ( event->type() == QEvent::CloseSoftwareInputPanel ) {
        emit this->adaptor->sendMessage( "CloseSoftwareInputPanel" ) ;
        emit this->adaptor->closeSoftwareInputPanel() ;
    }
    return QInputContext::filterEvent( event ) ;
}

QString Context::identifierName() {
    return "inputmethod" ;
}

bool Context::isComposing() const {
    return false ;
}

QString Context::language() {
    return "" ;
}

void Context::mouseHandler( int x, QMouseEvent* event ) {
    emit this->adaptor->sendMessage( "mouseHandler" ) ;
    Q_UNUSED( x ) ;
    Q_UNUSED( event ) ;
}

void Context::reset() {
    emit this->adaptor->sendMessage( "reset" ) ;
}

void Context::setFocusWidget( QWidget* widget ) {
    emit this->adaptor->sendMessage( "setFocusWidget" ) ;
    if ( widget ) {
        //QDBusConnection::sessionBus().registerService( "me.inputmethod.context" ) ;
        emit this->adaptor->sendMessage( "focusIn" ) ;
        emit this->adaptor->focusIn() ;
        this->update() ;
    }
    else {
        emit this->adaptor->sendMessage( "focusOut" ) ;
        emit this->adaptor->focusOut() ;
        //QDBusConnection::sessionBus().unregisterService( "me.inputmethod.context" ) ;
    }
    QInputContext::setFocusWidget( widget ) ;
}

void Context::update() {
    emit this->adaptor->sendMessage( "update" ) ;
    QWidget* widget = this->focusWidget() ;
    if ( widget ) {
        QVariant result( widget->inputMethodQuery( Qt::ImMicroFocus ) ) ;
        if ( result.isValid() ) {
            QRect cursorRect( result.toRect() ) ;
            cursorRect.moveTopLeft( widget->mapToGlobal( cursorRect.topLeft() ) ) ;
            if ( this->cursorRect != cursorRect ) {
                this->cursorRect = cursorRect ;
                emit this->adaptor->cursorRectUpdate( cursorRect.x(), cursorRect.y(), cursorRect.width(), cursorRect.height() ) ;
            }
        }
    }
}

}
