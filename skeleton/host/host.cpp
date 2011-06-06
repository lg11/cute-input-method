#include "host.h"
#include "adaptor.h"
#include "../engine/engine.h"

#include <QEvent>

#include <QDebug>

namespace host {

Host::Host( QObject* parent ) : QObject( parent ), view( NULL ), adaptor( new adaptor::Adaptor( this ) ), engine( new engine::Engine( this ) ) {
}

void Host::setView( QWidget* view ) {
    this->view = view ;
}

void Host::show() {
    if ( this->view )
        view->show() ;
}

void Host::hide() {
    if ( this->view )
        view->hide() ;
}

bool Host::keyPress( int keycode, int modifiers ) {
    qDebug() << "keyPress" << keycode << modifiers ;
    return false ;
}

bool Host::keyRelease( int keycode, int modifiers ) {
    qDebug() << "keyRelease" << keycode << modifiers ;
    return false ;
}

void Host::sendCommit( const QString& text ) {
    emit this->adaptor->sendCommit( text ) ;
}

void Host::sendKeyPress( int keycode, int modifiers ) {
    emit this->adaptor->sendKeyEvent( QEvent::KeyPress, keycode, modifiers ) ;
}

void Host::sendKeyRelease( int keycode, int modifiers ) {
    emit this->adaptor->sendKeyEvent( QEvent::KeyRelease, keycode, modifiers ) ;
}

}
