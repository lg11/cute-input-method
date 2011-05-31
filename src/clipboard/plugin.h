#ifndef PLUGIN_H
#define PLUGIN_H

#include <QDeclarativeExtensionPlugin>

class ClipboardPlugin : public QDeclarativeExtensionPlugin {
    Q_OBJECT
public:
    void registerTypes( const char *uri ) ;
} ;

#endif
