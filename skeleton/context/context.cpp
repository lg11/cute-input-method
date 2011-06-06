#include "context.h"
#include "adaptor.h"

#include <QDBusConnection>
#include <QDBusReply>

#include <QDebug>

namespace context {

Context::Context( QObject* parent ) :
    QInputContext( parent ), 
    adaptor( new adaptor::Adaptor( this ) ),
    interface( new QDBusInterface( "me.inputmethod.host", "/host", "inputmethod.host", QDBusConnection::sessionBus(), this ) ),
    eventStack() {
    QDBusConnection::sessionBus().registerService( "me.inputmethod.context" ) ;
    QDBusConnection::sessionBus().registerObject( "/context", this ) ;
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
    return QInputContext::isComposing() ;
}

void Context::reset() {
    emit this->adaptor->sendMessage( "reset" ) ;
}

void Context::setFocusWidget( QWidget* widget ) {
    emit this->adaptor->sendMessage( "setFocusWidget" ) ;
    if ( widget ) {
        //QDBusConnection::sessionBus().registerService( "me.inputmethod.context" ) ;
        emit this->adaptor->focusIn() ;
    }
    else {
        emit this->adaptor->focusOut() ;
        //QDBusConnection::sessionBus().unregisterService( "me.inputmethod.context" ) ;
    }
    QInputContext::setFocusWidget( widget ) ;
}

void Context::update() {
    emit this->adaptor->sendMessage( "update" ) ;
}

QString Context::language() {
    return "zh_CN" ;
}

}
