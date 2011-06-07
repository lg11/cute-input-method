#include "host.h"
#include "adaptor.h"

#include <QEvent>

//#include <QDebug>

namespace host {

Host::Host( QObject* parent ) :
    QObject( parent ),
    view( NULL ),
    engine( NULL ),
    inputDevice( UnknownInputDevice ), 
    adaptor( new adaptor::Adaptor( this ) ) {
}

void Host::setView( QWidget* view ) {
    if ( view ) {
        this->view = view ;
    }
}

void Host::setEngine( QObject* engine ) {
    if ( engine ) {
        const QMetaObject* object = engine->metaObject() ;

        int index = object->indexOfMethod( "processKey(int)" ) ;
        if ( index >= 0 ) {
            this->processKey = object->method( index ) ;
            this->engine = engine ;
        }
    }
}

void Host::show() {
    if ( this->view )
        this->view->show() ;
}

void Host::hide() {
    if ( this->view )
        this->view->hide() ;
}

bool Host::keyPress( int keycode, int modifiers ) {
    //qDebug() << "keyPress" << keycode << modifiers ;
    bool flag = false ;
    if ( modifiers == Qt::NoModifier && inputDevice != UnknownInputDevice ) {
        this->processKey.invoke( this->engine, Q_RETURN_ARG( bool, flag ), Q_ARG( int, keycode ) ) ;
        if ( flag ) 
            emit this->update() ;
    }
    return flag ;
}

bool Host::keyRelease( int keycode, int modifiers ) {
    //qDebug() << "keyRelease" << keycode << modifiers ;
    Q_UNUSED( keycode ) ;
    Q_UNUSED( modifiers ) ;
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
