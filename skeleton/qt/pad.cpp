#include "pad.h"

Pad::Pad( QWidget* parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
    //this->setWindowFlags( Qt::FramelessWindowHint | Qt::Dialog );
    //this->setWindowFlags( Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint ) ;
    this->setAttribute( Qt::WA_Maemo5PortraitOrientation, true ) ;
    //this->setAttribute( Qt::WA_TranslucentBackground, true ) ;

    QPalette palette ;
    palette.setColor( QPalette::Base, Qt::transparent ) ;
    QDeclarativeView* view = new QDeclarativeView( this ) ;
    view->setAttribute( Qt::WA_TranslucentBackground, true ) ;
    view->setPalette( palette ) ;
    view->setSource( QUrl("./qml/Keyboard.qml") ) ;
}
