#include "adaptor.h"
#include "host.h"

#include <QDBusReply>
#include <QDebug>

namespace adaptor {

Adaptor::Adaptor( host::Host* host ) : QDBusAbstractAdaptor( host ), host( host ) {
    //this->extraCallCount = 0 ;
#ifdef Q_WS_MAEMO_5
    this->interface = new QDBusInterface( "org.freedesktop.Hal", "/org/freedesktop/Hal/devices/platform_slide", "org.freedesktop.Hal.Device", QDBusConnection::systemBus(), this ) ;
#endif
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
#ifdef Q_WS_MAEMO_5
    if ( this->host->inputDevice == host::OnscreenInputDevice ) {
        emit this->host->receiveSurrounding( surrounding ) ;
        this->host->show() ;
    }
#endif
}

void Adaptor::cursorRectUpdate( int x, int y, int width, int height ) {
    //qDebug() << "cursorRectUpdate"  ;
    emit this->host->cursorRectUpdate( x, y, width, height ) ;
}

void Adaptor::focusIn() {
    qDebug() << "focusIn"  ;
}

void Adaptor::focusOut() {
    qDebug() << "focusOut"  ;
#ifdef Q_WS_MAEMO_5
    if ( this->host->inputDevice == host::HardwareInputDevice )
        this->host->hide() ;
#else
    this->host->hide() ;
#endif
}

void Adaptor::requestSoftwareInputPanel() {
    qDebug() << "requestSoftwareInputPanel"  ;
    if ( this->host->inputDevice == host::OnscreenInputDevice ) {
#ifdef Q_WS_MAEMO_5
        emit this->querySurrounding() ;
#else
        this->host->show() ;
#endif
    }
}

void Adaptor::closeSoftwareInputPanel() {
    qDebug() << "closeSoftwareInputPanel"  ;
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

#ifdef Q_WS_MAEMO_5
    void Adaptor::checkKeyboardStatus() {
        if ( this->interface->isValid() ) {
            QDBusReply<bool> result = this->interface->call( "GetProperty", "button.state.value" ) ;
            bool status ;
            if ( result.isValid() ) {
                status = result.value() ;
                qDebug() << "keyboard isClosed" << status ;
                if ( status ) {
                    this->host->inputDevice = host::OnscreenInputDevice ;
                }
                else {
                    this->host->inputDevice = host::HardwareInputDevice ;
                    emit this->host->setKeyboardLayout( 1 ) ;
                    //this->host->setInputDevice( host::HardwareInputDevice ) ;
                }
            }
        }
    }
#endif

}
