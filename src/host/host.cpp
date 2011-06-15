#include "host.h"
#include "adaptor.h"

#include <QEvent>

#include <QDebug>

namespace host {

Host::Host( QObject* parent ) :
    QObject( parent ),
    view( NULL ),
    handle( NULL ),
    inputDevice( UnknownInputDevice ), 
    inputLanguage( UnknownLanguage ), 
    adaptor( new adaptor::Adaptor( this ) ) {
}

void Host::setView( QWidget* view ) {
    this->view = view ;
}

void Host::setHandle( QObject* handle ) {
    int index ;
    const QMetaObject* object = handle->metaObject() ;

    index = object->indexOfMethod( "processKeyPress(int)" ) ;
    this->processKeyPress = object->method( index ) ;
    index = object->indexOfMethod( "processKeyRelease(int)" ) ;
    this->processKeyRelease = object->method( index ) ;
    index = object->indexOfMethod( "requestReset()" ) ;
    this->requestReset = object->method( index ) ;
    index = object->indexOfMethod( "setKeyboardLayout(int)" ) ;
    this->setKeyboardLayout = object->method( index ) ;

    this->handle = handle ;
}

void Host::show() {
    //qDebug() << "show" ;
    this->view->show() ;
}

void Host::hide() {
    //qDebug() << "hide" ;
    this->view->hide() ;
}

bool Host::keyPress( int keycode, int modifiers ) {
    qDebug() << "keyPress" << keycode << modifiers ;
    Q_UNUSED( modifiers ) ;
    bool flag = false ;
    if ( inputDevice == HardwareInputDevice ) 
        this->processKeyPress.invoke( this->handle, Q_RETURN_ARG( bool, flag ), Q_ARG( int, keycode ) ) ;
    return flag ;
}

bool Host::keyRelease( int keycode, int modifiers ) {
    qDebug() << "keyRelease" << keycode << modifiers ;
    Q_UNUSED( modifiers ) ;
    bool flag = false ;
    if ( inputDevice == HardwareInputDevice ) 
        this->processKeyRelease.invoke( this->handle, Q_RETURN_ARG( bool, flag ), Q_ARG( int, keycode ) ) ;
    return flag ;
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

void Host::setInputDevice( InputDevice inputDevice ) {
    if ( this->inputDevice != inputDevice ) {
        this->inputDevice = inputDevice ;
        emit this->adaptor->sendStatus( this->inputDevice, this->inputLanguage ) ;
    }
}

void Host::setInputLanguage( InputLanguage inputLanguage ) {
    if ( this->inputLanguage != inputLanguage ) {
        this->inputLanguage = inputLanguage ;
        emit this->adaptor->sendStatus( this->inputDevice, this->inputLanguage ) ;
    }
}

}
