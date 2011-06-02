#include "plugin.h"

//MPlugin::MPlugin( QObject* parent ) : QObject( parent ), MInputMethodQuickPlugin() {} 
MPlugin::MPlugin() {} 

QString MPlugin::name() const {
    return "mcip" ;
}

QString MPlugin::qmlFileName() const {
    return "qml/qwert.qml" ;
}

Q_EXPORT_PLUGIN2( mplugin, MPlugin ) ;
