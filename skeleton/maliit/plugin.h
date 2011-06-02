#ifndef PLUGIN_H
#define PLUGIN_H

#include <minputmethodquickplugin.h>
#include <QObject>

class MPlugin : public QObject, public MInputMethodQuickPlugin {
    Q_OBJECT
    Q_INTERFACES( MInputMethodQuickPlugin MInputMethodPlugin )
public :
    //MPlugin( QObject* parent = NULL ) ;
    MPlugin() ;

    virtual QString name() const ;
    virtual QString qmlFileName() const ;
} ;

#endif
