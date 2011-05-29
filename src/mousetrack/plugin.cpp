#include <qdeclarative.h>

#include "plugin.h"
#include "track.h"

void MouseTrackPlugin::registerTypes( const char *uri ) {
    qmlRegisterType<MouseTrack>( uri, 1, 0, "MouseTrack" ) ;
}

Q_EXPORT_PLUGIN2( mousetrackplugin, MouseTrackPlugin ) ;

