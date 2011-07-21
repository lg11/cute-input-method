#include <qdeclarative.h>

#include "plugin.h"
#include "simpletoucharea.h"

void SimpleTouchAreaPlugin::registerTypes( const char *uri ) {
    qmlRegisterType<SimpleTouchArea>( uri, 1, 0, "SimpleTouchArea" ) ;
}

Q_EXPORT_PLUGIN2( simpletouchareaplugin, SimpleTouchAreaPlugin ) ;

