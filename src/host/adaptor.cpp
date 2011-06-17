#include "adaptor.h"
#include "host.h"
#ifdef Q_WS_MAEMO_5
#include "extra.h"
#endif

#include <QDBusReply>

//#include <QDebug>

namespace adaptor {

Adaptor::Adaptor( host::Host* host ) : 
    QDBusAbstractAdaptor( host ),
#ifdef Q_WS_MAEMO_5
    interface( new QDBusInterface( "org.freedesktop.Hal", "/org/freedesktop/Hal/devices/platform_slide", "org.freedesktop.Hal.Device", QDBusConnection::systemBus(), this ) ),
    extraInputPanel( NULL ),
    focusedWindowId( 0 ),
#endif
    host( host ) {
}

#ifdef Q_WS_MAEMO_5
void Adaptor::setExtraInputPanel( extra::ExtraInputPanel* extraInputPanel ) {
    this->extraInputPanel = extraInputPanel ;
}
#endif


bool Adaptor::keyPress( int keycode, int modifiers ) {
    return this->host->keyPress( keycode, modifiers ) ;
}

bool Adaptor::keyRelease( int keycode, int modifiers ) {
    return this->host->keyRelease( keycode, modifiers ) ;
}

void Adaptor::receiveMessage( const QString& message ) {
    //qDebug() << "received" << message ;
    Q_UNUSED( message ) ;
}

void Adaptor::receiveSurrounding( const QString& surrounding ) {
    //qDebug() << "receiveSurrounding" << surrounding ;
#ifdef Q_WS_MAEMO_5
    if ( this->host->inputDevice == host::OnscreenInputDevice ) {
        emit this->extraInputPanel->receiveSurrounding( surrounding ) ;
        this->host->hide() ;
        this->extraInputPanel->show() ;
    }
#else
    Q_UNUSED( message ) ;
#endif
}

void Adaptor::cursorRectUpdate( int x, int y, int width, int height ) {
    //qDebug() << "cursorRectUpdate" << x << y ;
    emit this->host->cursorRectUpdate( x, y, width, height ) ;
}

void Adaptor::focusIn() {
    //qDebug() << "focusIn"  ;
}

void Adaptor::focusOut() {
    //qDebug() << "focusOut"  ;
    this->host->hide() ;
    this->host->requestReset.invoke( this->host->handle ) ;
}

void Adaptor::requestSoftwareInputPanel() {
    //qDebug() << "requestSoftwareInputPanel"  ;
    if ( this->host->inputDevice == host::OnscreenInputDevice ) {
#ifdef Q_WS_MAEMO_5
        emit this->querySurrounding() ;
#else
        this->host->show() ;
#endif
    }
}

void Adaptor::closeSoftwareInputPanel() {
    //qDebug() << "closeSoftwareInputPanel"  ;
if ( this->host->inputDevice == host::OnscreenInputDevice ) {
#ifdef Q_WS_MAEMO_5
#else
        this->host->hide() ;
#endif
    }
}

void Adaptor::preeditStart() {
#ifdef Q_WS_MAEMO_5
    if ( this->host->inputDevice == host::HardwareInputDevice ) {
        emit this->queryCursorRect() ;
        this->host->show() ;
    }
#else
    emit this->queryCursorRect() ;
    this->host->show() ;
#endif
}

void Adaptor::preeditEnd() {
    //if ( this->host->inputDevice == host::HardwareInputDevice ) {
        //this->host->hide() ;
    //}
}

void Adaptor::setInputDevice( int inputDevice ) {
    if ( inputDevice == 0 ) {
        if ( this->host->inputDevice != host::UnknownInputDevice ) {
            this->host->inputDevice = host::UnknownInputDevice ;
            emit this->host->inputDeviceChanged() ;
        }
    }
    else if ( inputDevice == 1 ) {
        if ( this->host->inputDevice != host::HardwareInputDevice ) {
            this->host->inputDevice = host::HardwareInputDevice ;
            emit this->host->inputDeviceChanged() ;
        }
    }
    else if ( inputDevice == 2 ) {
        if ( this->host->inputDevice != host::OnscreenInputDevice ) {
            this->host->inputDevice = host::OnscreenInputDevice ;
            emit this->host->inputDeviceChanged() ;
        }
    }
}

void Adaptor::setInputLanguage( int inputLanguage ) {
    if ( inputLanguage == 0 ) {
        if ( this->host->inputLanguage != host::UnknownLanguage ) {
            this->host->inputLanguage = host::UnknownLanguage ;
            emit this->host->inputLanguageChanged() ;
        }
    }
    else if ( inputLanguage == 1 ) {
        if ( this->host->inputLanguage != host::SimplifiedChinese ) {
            this->host->inputLanguage = host::SimplifiedChinese ;
            emit this->host->inputLanguageChanged() ;
        }
    }
}

void Adaptor::queryStatus() {
    emit this->sendStatus( this->host->inputDevice, this->host->inputLanguage ) ;
}

#ifdef Q_WS_MAEMO_5
void Adaptor::checkKeyboardStatus() {
    if ( this->interface->isValid() ) {
        QDBusReply<bool> result = this->interface->call( "GetProperty", "button.state.value" ) ;
        bool status ;
        if ( result.isValid() ) {
            status = result.value() ;
            //qDebug() << "keyboard isClosed" << status ;
            if ( status ) {
                this->host->inputDevice = host::OnscreenInputDevice ;
                this->host->hide() ;
                this->host->requestReset.invoke( this->host->handle ) ;
            }
            else {
                this->host->inputDevice = host::HardwareInputDevice ;
                this->extraInputPanel->hide() ;
                this->host->setKeyboardLayout.invoke( this->host->handle, Q_ARG( int, 1 ) ) ;
                this->host->requestReset.invoke( this->host->handle ) ;
            }
        }
    }
}

void Adaptor::setFocusedWindowId( quint64 id ) {
    //qDebug() << "setFocusedWindowId" << id ;
    this->focusedWindowId = id ;
}

quint64 Adaptor::getFocusedWindowId() {
    //qDebug() << "getFocusedWindowId" ;
    return this->focusedWindowId ;
}

#endif

}
