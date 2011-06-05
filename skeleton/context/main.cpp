#include <QWidget>
#include <QApplication>
#include <QPlainTextEdit>
#include <QLayout>
#include <QDBusConnection>

#include <QDebug>

#include "context.h"

int main( int argc, char** argv ) {
    QApplication app( argc, argv ) ;

    QWidget* win = new QWidget() ;

    QLayout* layout = new QVBoxLayout() ;
    win->setLayout( layout ) ;
    
    QPlainTextEdit* edit = new QPlainTextEdit( win ) ;
    layout->addWidget( edit ) ;

    win->show() ;

    context::Context* context = new context::Context() ;
    app.setInputContext( context ) ;

    //QDBusConnection::sessionBus().registerService( "me.inputmethod" ) ;
    //QDBusConnection::sessionBus().registerObject( "/context", context ) ;

    qDebug() << QDBusConnection::sessionBus().isConnected() ;

    return app.exec() ;
}
