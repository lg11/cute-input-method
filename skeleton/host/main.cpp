#include <QApplication>
#include <QDBusConnection>
#include <QDeclarativeContext>
#include <QUrl>
#include <QDesktopWidget>

#include <QDebug>

#include "host.h"
#include "view.h"
#include "adaptor.h"
#include "../engine/engine.h"

int main( int argc, char** argv ) {
    QApplication app( argc, argv ) ;
    app.setInputContext( NULL ) ;

    host::Host* host = new host::Host() ;

    engine::Engine* engine = new engine::Engine() ;
    host->setEngine( engine ) ;

    view::View* view = new view::View() ;
    host->setView( view ) ;

    QDesktopWidget* desktop = QApplication::desktop() ;
    view->setGeometry( desktop->geometry() ) ;
    view->move( 0, 1 ) ;
    view->displayOffsetY = 1 ;

    view->rootContext()->setContextProperty( "host", host ) ;
    view->rootContext()->setContextProperty( "view", view ) ;
    view->rootContext()->setContextProperty( "engine", engine ) ;

    view->setSource( QUrl("view/root.qml") ) ;
    //view->setSource( QUrl("qml/keyboard.qml") ) ;

    QDBusConnection::sessionBus().registerService( "me.inputmethod.host" ) ;
    QDBusConnection::sessionBus().registerObject( "/host", host ) ;

    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "sendMessage", host->adaptor, SLOT(receiveMessage( const QString& )) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "requestSoftwareInputPanel", host->adaptor, SLOT(show()) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "closeSoftwareInputPanel", host->adaptor, SLOT(hide()) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "focusIn", host->adaptor, SLOT(show()) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "focusOut", host->adaptor, SLOT(hide()) ) ;
    QDBusConnection::sessionBus().connect( "", "", "inputmethod.context", "cursorRectUpdate", host->adaptor, SIGNAL(cursorRectUpdate( int, int, int, int )) ) ;

    QObject::connect( host->adaptor, SIGNAL(cursorRectUpdate( int, int, int, int )), view, SLOT(cursorRectUpdate( int, int, int, int )) ) ;
    QObject::connect( engine, SIGNAL(candidateUpdate()), view, SIGNAL(candidateUpdate()) ) ;
    QObject::connect( engine, SIGNAL(sendCommit( const QString& )), host->adaptor, SIGNAL( sendCommit( const QString& ) ) ) ;

    qDebug() << "load start" ;
    engine->load( "~/.config/mcip/sysdict" ) ;
    engine->setKeyboardLayout( engine::Engine::FullKeyboardLayout ) ;
    host->inputDevice = host::Host::HardwareInputDevice ;
    qDebug() << "load end" ;

    return app.exec() ;
}
