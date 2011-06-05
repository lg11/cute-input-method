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

void Adaptor::receiveMessage( const QString& message ) {
    qDebug() << message ;
}

}
