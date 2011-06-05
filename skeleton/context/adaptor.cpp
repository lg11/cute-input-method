#include "adaptor.h"
#include "context.h"

#include <QDebug>

namespace adaptor {

Adaptor::Adaptor( context::Context* context ) : QDBusAbstractAdaptor( context ), context( context ) {}

void Adaptor::receiveMessage( const QString& message ) {
    qDebug() << message ;
}

}
