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

    /*! \brief Implement this function to return the identifier for this input method.
     */
    virtual QString name() const ;

    /*! \brief Implement this function to return the languages supported for this virtual keyboard.
     */
    virtual QStringList languages() const ;

    /*! \brief Creates and returns the MAbstractInputMethod object for
     * this plugin. This function will be only called once and the allocated
     * resources will be owned by the input method server.
     */
    virtual MAbstractInputMethod* createInputMethod( MAbstractInputMethodHost *host, QWidget *mainWindow ) ;

    /*! \brief Creates and returns the MAbstractInputMethodSettings object for
     * this plugin. This function will be only called once and the allocated
     * resources will be owned by the input method server.
     */
    virtual MAbstractInputMethodSettings* createInputMethodSettings() ;

    /*!
     * \brief Returns set of states which could be handled by this plugin.
     *
     * WARNING: If result is empty then this plugin will not be loaded
     * during startup.
     */
    virtual QSet<MInputMethod::HandlerState> supportedStates() const ;

private :
    Q_DISABLE_COPY( Plugin ) ;
    Q_DECLARE_PRIVATE( Plugin ) ;
    PluginPrivate* const d_ptr ;
} ;

}

//Q_DECLARE_INTERFACE( plugin::Plugin, "com.meego.meegoimframework.Plugin/1.1" )

#endif
