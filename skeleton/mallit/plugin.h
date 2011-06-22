#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QSet>

#include <minputmethodplugin.h>

namespace plugin {

class PluginPrivate ;

class Plugin : public QObject, public MInputMethodPlugin {
    Q_OBJECT
    Q_INTERFACES( MInputMethodPlugin )

public :
    Plugin() ;
    virtual ~Plugin() ;

    virtual QString name() const ;
    virtual QStringList languages() const ;
    virtual MAbstractInputMethod* createInputMethod( MAbstractInputMethodHost *host, QWidget *mainWindow ) ;
    virtual MAbstractInputMethodSettings* createInputMethodSettings() ;
    virtual QSet<MInputMethod::HandlerState> supportedStates() const ;

private :
    Q_DISABLE_COPY( Plugin ) ;
    Q_DECLARE_PRIVATE( Plugin ) ;
    PluginPrivate* const d_ptr ;
} ;

}

//Q_DECLARE_INTERFACE( plugin::Plugin, "com.meego.meegoimframework.Plugin/1.1" )

#endif
