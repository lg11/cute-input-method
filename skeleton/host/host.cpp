#include "host.h"
#include "adaptor.h"

#include <QEvent>

#include <QDebug>

namespace host {

Host::Host( QObject* parent ) :
    QObject( parent ),
    view( NULL ),
    extraInputPanel( NULL ),
    engine( NULL ),
    inputDevice( UnknownInputDevice ), 
    adaptor( new adaptor::Adaptor( this ) ) {
}

void Host::setView( QWidget* view ) {
    if ( view ) {
        this->view = view ;
    }
}

void Host::setExtraInputPanel( QWidget* extraInputPanel ) {
    if ( extraInputPanel ) {
        this->extraInputPanel = extraInputPanel ;
    }
}

void Host::setEngine( QObject* engine ) {
    if ( engine ) {
        const QMetaObject* object = engine->metaObject() ;

        int index = object->indexOfMethod( "processKeyPress(int)" ) ;
        if ( index >= 0 ) {
            this->processKeyPress = object->method( index ) ;
            index = object->indexOfMethod( "processKeyRelease(int)" ) ;
            this->processKeyRelease = object->method( index ) ;
            this->engine = engine ;
            //qDebug() << "set engine" ;
        }
    }
}

void Host::show() {
    //qDebug() << "show" ;
    if ( this->inputDevice == HardwareInputDevice ) {
        if ( this->view )
            this->view->show() ;
    }
    else if ( this->inputDevice == OnscreenInputDevice ) {
        if ( this->extraInputPanel )
            this->extraInputPanel->show() ;
    }
}

void Host::hide() {
    //qDebug() << "hide" ;
    if ( this->view )
        this->view->hide() ;
    if ( this->extraInputPanel )
        this->extraInputPanel->hide() ;
}

bool Host::keyPress( int keycode, int modifiers ) {
    qDebug() << "keyPress" << keycode << modifiers ;
    Q_UNUSED( modifiers ) ;
    bool flag = false ;
    //if ( modifiers == Qt::NoModifier && inputDevice != UnknownInputDevice ) {
    if ( inputDevice == HardwareInputDevice ) {
        this->processKeyPress.invoke( this->engine, Q_RETURN_ARG( bool, flag ), Q_ARG( int, keycode ) ) ;
    }
    //qDebug() << "keyPress" << flag ;
    return flag ;
}

bool Host::keyRelease( int keycode, int modifiers ) {
    qDebug() << "keyRelease" << keycode << modifiers ;
    Q_UNUSED( modifiers ) ;
    bool flag = false ;
    if ( inputDevice == HardwareInputDevice ) {
        this->processKeyRelease.invoke( this->engine, Q_RETURN_ARG( bool, flag ), Q_ARG( int, keycode ) ) ;
    }
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

}
