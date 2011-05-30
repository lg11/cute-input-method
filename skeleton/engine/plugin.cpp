#include <qdeclarative.h>

#include "plugin.h"
#include "engine.h"

void IMEnginePlugin::registerTypes( const char *uri ) {
    qmlRegisterType<IMEngine>( uri, 1, 0, "IMEngine" ) ;
}

Q_EXPORT_PLUGIN2( imengineplugin, IMEnginePlugin ) ;

