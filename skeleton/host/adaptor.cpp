#include "adaptor.h"
#include "host.h"

#include <QDebug>

namespace adaptor {

Adaptor::Adaptor( host::Host* host ) : QDBusAbstractAdaptor( host ), host( host ) {}

void Adaptor::show() {
    this->host->show() ;
}

void Adaptor::hide() {
    this->host->hide() ;
}

bool Adaptor::keyPress( int keycode, int modifiers ) {
    return this->host->keyPress( keycode, modifiers ) ;
}

bool Adaptor::keyRelease( int keycode, int modifiers ) {
    return this->host->keyRelease( keycode, modifiers ) ;
}

void Adaptor::receiveMessage( const QString& message ) {
    qDebug() << "received" << message ;
}

}
