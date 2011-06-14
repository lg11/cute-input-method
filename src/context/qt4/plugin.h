#ifndef PLUGIN_H
#define PLUGIN_H

#include <QInputContextPlugin>

namespace plugin {

class InputMethodPlugin : public QInputContextPlugin {
    Q_OBJECT

public :
    InputMethodPlugin( QObject* parent = NULL ) ;
    virtual ~InputMethodPlugin() ;

    QInputContext* create( const QString& key ) ;
    QString description( const QString& key ) ;
    QString displayName( const QString& key ) ;
    QStringList keys() const ;
    QStringList languages( const QString &key ) ;
} ;

}

#endif
