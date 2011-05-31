#include <qdeclarative.h>

#include "plugin.h"
#include "clipboard.h"

void ClipboardPlugin::registerTypes( const char *uri ) {
    qmlRegisterType<Clipboard>( uri, 1, 0, "Clipboard" ) ;
}

Q_EXPORT_PLUGIN2( clipboardplugin, ClipboardPlugin ) ;

