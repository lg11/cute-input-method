#include "adaptor.h"
#include "host.h"

#include <QDebug>

namespace adaptor {

Adaptor::Adaptor( host::Host* host ) : QDBusAbstractAdaptor( host ), host( host ) {}

//void Adaptor::show() {
    //this->host->show() ;
    //emit this->requestSurrounding() ;
//}

//void Adaptor::hide() {
    //this->host->hide() ;
//}

bool Adaptor::keyPress( int keycode, int modifiers ) {
    //qDebug() << "keyPree" << keycode << modifiers ;
    return this->host->keyPress( keycode, modifiers ) ;
}

bool Adaptor::keyRelease( int keycode, int modifiers ) {
    return this->host->keyRelease( keycode, modifiers ) ;
}

void Adaptor::receiveMessage( const QString& message ) {
    qDebug() << "received" << message ;
}

void Adaptor::receiveSurrounding( const QString& surrounding ) {
    qDebug() << "receiveSurrounding" << surrounding ;
}

void Adaptor::cursorRectUpdate( int x, int y, int width, int height ) {
    //qDebug() << "cursorRectUpdate"  ;
    emit this->host->cursorRectUpdate( x, y, width, height ) ;
}

void Adaptor::requestSoftwareInputPanel() {
    if ( this->host->inputDevice == host::OnscreenInputDevice ) {
        this->host->show() ;
        emit this->querySurrounding() ;
    }
}

void Adaptor::closeSoftwareInputPanel() {
    this->host->hide() ;
}

void Adaptor::preeditStart() {
    emit this->queryCursorRect() ;
    this->host->show() ;
}
void Adaptor::preeditEnd() {
    //if ( this->host->inputDevice == host::HardwareInputDevice ) {
        //this->host->hide() ;
    //}
}

}
