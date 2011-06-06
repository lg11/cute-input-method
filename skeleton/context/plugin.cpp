#include "plugin.h"
#include "context.h"

namespace plugin {

InputMethodPlugin::InputMethodPlugin( QObject* parent ) : QInputContextPlugin( parent ) {}

InputMethodPlugin::~InputMethodPlugin() {}

QInputContext* InputMethodPlugin::create( const QString& key ) {
    QInputContext* context = NULL ;

    if ( !key.isEmpty() )
        context = new context::Context() ;

    return context ;
}

QString InputMethodPlugin::description( const QString& key ) {
    Q_UNUSED( key ) ;
    return "cuteinputmethod" ;
}

QString InputMethodPlugin::displayName( const QString& key ) {
    Q_UNUSED( key ) ;
    return "cuteinputmethod" ;
}

QStringList InputMethodPlugin::keys() const {
    return QStringList( "cuteinputmethod" ) ;
}

QStringList InputMethodPlugin::languages( const QString &key ) {
    Q_UNUSED( key ) ;
    return QStringList( "zh_CN" ) ;
}

}

Q_EXPORT_PLUGIN2( cuteinputmethod, plugin::InputMethodPlugin )
