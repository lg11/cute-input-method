#include "context.h"
#include "adaptor.h"

#include <QDebug>

namespace context {

Context::Context( QObject* parent ) : QInputContext( parent ), adaptor( new adaptor::Adaptor( this ) ), eventStack() {
}

bool Context::filterEvent( const QEvent* event ) {
    bool flag = true ;
    if ( event->type() == QEvent::KeyPress )
        emit this->adaptor->sendMessage( "KeyPress" ) ;
    else if ( event->type() == QEvent::KeyRelease )
        emit this->adaptor->sendMessage( "KeyRelease" ) ;
    else if ( event->type() == QEvent::RequestSoftwareInputPanel )
        emit this->adaptor->sendMessage( "RequestSoftwareInputPanel" ) ;
    else if ( event->type() == QEvent::CloseSoftwareInputPanel )
        emit this->adaptor->sendMessage( "CloseSoftwareInputPanel" ) ;
    else
        flag = false ;
    return flag ;
}

QString Context::identifierName() {
    return "inputmethod" ;
}

bool Context::isComposing() const {
    return true ;
}

void Context::reset() {
    emit this->adaptor->sendMessage( "reset" ) ;
}

void Context::setFocusWidget( QWidget* widget ) {
    emit this->adaptor->sendMessage( "setFocusWidget" ) ;
    Q_UNUSED( widget ) ;
}

void Context::update() {
    emit this->adaptor->sendMessage( "update" ) ;
}

QString Context::language() {
    return "zh_CN" ;
}

}
