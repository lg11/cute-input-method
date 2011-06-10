#include "view.h"

#include <QPalette>
#include <QApplication>
#include <QDesktopWidget>
#include <QResizeEvent>

#include <QDebug>

#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/extensions/shape.h>
// use libX11 for mouse transparency
// ref colibri (a notify app of KDE) code


namespace view {

View::View( QWidget* parent ) : QDeclarativeView( parent ) {
    QPalette palette ;
    palette.setColor( QPalette::Base, Qt::transparent ) ;
    this->setPalette( palette ) ;

    this->setWindowFlags( Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::BypassGraphicsProxyWidget ) ;
    this->setAttribute( Qt::WA_TranslucentBackground, true ) ;

    this->displayOffsetX = 0 ;
    this->displayOffsetY = 0 ;
    this->displayWidthHint = 0 ;
    this->displayHeightHint = 0 ;

    this->checkDisplaySize( QApplication::desktop()->primaryScreen() ) ;
    QObject::connect( QApplication::desktop(), SIGNAL(resized(int)), this, SLOT(checkDisplaySize(int)) ) ;

    this->clearInputRegion() ;
}

void View::addInputRegion( const QRect& rect ) {
    XRectangle xrect ;
    xrect.x = rect.x() ;
    xrect.y = rect.y() ;
    xrect.width = rect.width() ;
    xrect.height = rect.height() ;
    
    XShapeCombineRectangles( QX11Info::display(), this->winId(), ShapeInput, 0, 0, &xrect, 1, ShapeUnion, 0 ) ;
}

void View::clearInputRegion() {
    XRectangle xrect ;
    xrect.x = 0 ;
    xrect.y = 0 ;
    xrect.width = 0 ;
    xrect.height = 0 ;

    XShapeCombineRectangles( QX11Info::display(), this->winId(), ShapeInput, 0, 0, &xrect, 1, ShapeSet, 0 ) ;
}

int View::displayWidth() {
    return this->width() ;
}

int View::displayHeight() {
    return this->height() ;
}

void View::checkDisplaySize( int screen ) {
    QWidget* widget = QApplication::desktop()->screen( screen ) ;
    this->displaySize.setWidth( widget->width() + this->displayWidthHint ) ;
    this->displaySize.setHeight( widget->height() + this->displayHeightHint ) ;
    emit this->displayWidthChanged( this->displaySize.width() ) ;
    emit this->displayWidthChanged( this->displaySize.width() ) ;
}

const QRect& View::readCursorRect() {
    return this->cursorRect ;
}

void View::cursorRectUpdate( int x, int y, int width, int height ) {
    //qDebug() << "cursorRectUpdate" << x << y << width << height ;
    QRect cursorRect( x, y, width, height ) ;
    cursorRect.moveTopLeft( this->mapFromGlobal( cursorRect.topLeft() ) ) ;
    if ( this->cursorRect != cursorRect ) {
        this->cursorRect = cursorRect ;
        emit this->cursorRectUpdate( this->cursorRect ) ;
    }
}

}
