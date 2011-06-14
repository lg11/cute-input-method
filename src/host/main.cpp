#include <QApplication>
#include <QDBusConnection>
#include <QDeclarativeContext>
#include <QUrl>
#include <QDir>
#include <QDesktopWidget>

#include <QDebug>

#include "host.h"
#include "view.h"
#include "extra.h"
#include "adaptor.h"
#include "handle.h"
#include "../engine/engine.h"

QString extendHome( const QString& path ) {
    QString p ;
    if ( path.at(0) == QChar( '~' ) ) {
        p.append( QDir::homePath() ) ;
        p.append( path.right( path.length() - 1 ) ) ;
    }
    else
        p.append( path ) ;
    return p ;
}

int main( int argc, char** argv ) {
    QApplication app( argc, argv ) ;
    app.setInputContext( NULL ) ;

    host::Host* host = new host::Host() ;

    engine::Engine* engine = new engine::Engine() ;
    handle::Handle* handle = new handle::Handle( engine ) ;
    host->setEngine( handle ) ;

    view::View* view = new view::View() ;
    host->setView( view ) ;

    extra::ExtraInputPanel* extraInputPanel = new extra::ExtraInputPanel() ;
    host->setExtraInputPanel( extraInputPanel ) ;
    extraInputPanel->setInputContext( NULL ) ;

    QDesktopWidget* desktop = QApplication::desktop() ;
    view->setGeometry( desktop->geometry() ) ;
    view->move( 0, 1 ) ;
    view->displayOffsetY = 1 ;

    view->rootContext()->setContextProperty( "host", host ) ;
    view->rootContext()->setContextProperty( "view", view ) ;
    view->rootContext()->setContextProperty( "engine", engine ) ;
    view->rootContext()->setContextProperty( "handle", handle ) ;
    
    extraInputPanel->rootContext()->setContextProperty( "engine", engine ) ;
    extraInputPanel->rootContext()->setContextProperty( "view", extraInputPanel ) ;

    view->setSource( QUrl(extendHome( "~/.config/mcip/view/root.qml") ) ) ;
    extraInputPanel->setSource( QUrl(extendHome( "~/.config/mcip/extra/root.qml") ) ) ;
    //view->setSource( QUrl("qml/keyboard.qml") ) ;

    QDBusConnection::sessionBus().registerService( "me.inputmethod.host" ) ;
    QDBusConnection::sessionBus().registerObject( "/host", host ) ;

    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "sendMessage", host->adaptor, SLOT(receiveMessage( const QString& )) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "focusIn", host->adaptor, SLOT(focusIn()) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "focusOut", host->adaptor, SLOT(focusOut()) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "requestSoftwareInputPanel", host->adaptor, SLOT(requestSoftwareInputPanel()) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "closeSoftwareInputPanel", host->adaptor, SLOT(closeSoftwareInputPanel()) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "cursorRectUpdate", host->adaptor, SLOT(cursorRectUpdate( int, int, int, int )) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "sendSurrounding", host->adaptor, SIGNAL(receiveSurrounding( const QString& )) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.console", "setInputDevice", host->adaptor, SIGNAL(receiveSurrounding(int)) ) ;

    QObject::connect( host, SIGNAL(cursorRectUpdate( int, int, int, int )), view, SLOT(cursorRectUpdate( int, int, int, int )) ) ;
    QObject::connect( engine, SIGNAL(candidateUpdate()), view, SIGNAL(candidateUpdate()) ) ;
    QObject::connect( engine, SIGNAL(sendCommit( const QString& )), host->adaptor, SIGNAL( sendCommit( const QString& ) ) ) ;
    QObject::connect( engine, SIGNAL(preeditStart()), host->adaptor, SLOT(preeditStart()) ) ;
    QObject::connect( engine, SIGNAL(preeditEnd()), host->adaptor, SLOT(preeditEnd()) ) ;
    QObject::connect( host, SIGNAL(receiveSurrounding( const QString& )), extraInputPanel, SIGNAL(receiveSurrounding( const QString& )) ) ;
    QObject::connect( extraInputPanel, SIGNAL(replaceSurrounding( const QString& )), host->adaptor, SIGNAL(replaceSurrounding( const QString& )) ) ;

    qDebug() << "load start" ;
    engine->load( extendHome( "~/.config/mcip/sysdict" ) ) ;
    engine->load( extendHome( "~/.config/mcip/userdict.log" ) ) ;
    engine->startLog( extendHome( "~/.config/mcip/userdict.log" ) ) ;
    //engine->setKeyboardLayout( engine::Engine::FullKeyboardLayout ) ;
    //host->inputDevice = host::HardwareInputDevice ;
    //host->inputDevice = host::OnscreenInputDevice ;
    qDebug() << "load end" ;

#ifdef Q_WS_MAEMO_5
    qDebug() << "start track keyboard status" ;
    QDBusConnection::systemBus().connect( "org.freedesktop.Hal", "/org/freedesktop/Hal/devices/platform_slide", "org.freedesktop.Hal.Device", "PropertyModified", host->adaptor, SLOT(checkKeyboardStatus()) ) ;
    host->adaptor->checkKeyboardStatus() ;
    QObject::connect( host, SIGNAL(setKeyboardLayout(int)), handle, SLOT(setKeyboardLayout(int)) ) ;
#endif 
    return app.exec() ;
}
