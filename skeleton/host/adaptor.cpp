#include "adaptor.h"
#include "host.h"

#include <QDebug>

namespace adaptor {

Adaptor::Adaptor( host::Host* host ) : QDBusAbstractAdaptor( host ), host( host ) {
    this->extraCallCount = 0 ;
}

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
    if ( this->host->inputDevice == host::OnscreenInputDevice ) {
        emit this->host->receiveSurrounding( surrounding ) ;
        this->host->show() ;
    }
}

void Adaptor::cursorRectUpdate( int x, int y, int width, int height ) {
    //qDebug() << "cursorRectUpdate"  ;
    emit this->host->cursorRectUpdate( x, y, width, height ) ;
}

void Adaptor::requestSoftwareInputPanel() {
    qDebug() << "requestSoftwareInputPanel"  ;
    if ( this->host->inputDevice == host::OnscreenInputDevice ) {
        if ( this->extraCallCount == 0 ) 
            this->extraCallCount++ ;
        else if ( this->extraCallCount == 1 ) {
            //this->host->show() ;
            emit this->querySurrounding() ;
            this->extraCallCount = 0 ;
        }
    }
}

void Adaptor::closeSoftwareInputPanel() {
    qDebug() << "closeSoftwareInputPanel"  ;
    //this->host->hide() ;
    this->extraCallCount = 0 ;
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

void Adaptor::setInputDevice( int index ) {
    if ( index == 0 ) {
        if ( this->host->inputDevice != host::UnknownInputDevice ) {
            this->host->inputDevice = host::UnknownInputDevice ;
            emit this->host->inputDeviceChanged() ;
        }
    }
    else if ( index == 1 ) {
        if ( this->host->inputDevice != host::HardwareInputDevice ) {
            this->host->inputDevice = host::HardwareInputDevice ;
            emit this->host->inputDeviceChanged() ;
        }
    }
    else if ( index == 2 ) {
        if ( this->host->inputDevice != host::OnscreenInputDevice ) {
            this->host->inputDevice = host::OnscreenInputDevice ;
            emit this->host->inputDeviceChanged() ;
        }
    }
}

}
