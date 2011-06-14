#include "extra.h"

#include <QPalette>
#include <QSize>
#include <QCloseEvent>
#include <QApplication>
#include <QDesktopWidget>

namespace extra {

ExtraInputPanel::ExtraInputPanel( QWidget* parent ) : QDeclarativeView( parent ) {
    QPalette palette ;
    palette.setColor( QPalette::Base, Qt::transparent ) ;
    this->setPalette( palette ) ;

    this->setWindowFlags( Qt::FramelessWindowHint | Qt::Dialog ) ;
    this->setAttribute( Qt::WA_TranslucentBackground, true ) ;
    this->setAttribute( Qt::WA_Maemo5AutoOrientation, true ) ; 

    QObject::connect( this, SIGNAL(sceneResized(QSize)), this, SLOT(keepSize(QSize)) ) ;
    QObject::connect( QApplication::desktop(), SIGNAL(resized(int)), this, SLOT(checkRotate(int)) ) ;
    this->checkRotate() ;
}

void ExtraInputPanel::closeEvent( QCloseEvent* event ) {
    this->hide() ;
    event->ignore() ;
}

void ExtraInputPanel::hideEvent( QHideEvent* event ) {
    emit this->hided() ;
    QDeclarativeView::hideEvent( event ) ;
}

void ExtraInputPanel::keepSize( QSize size ) {
    //QGraphicsObject* object = this->rootObject() ;
    if ( this->size() != size )
        this->resize( size ) ;
}

int ExtraInputPanel::readRotate() {
    return this->rotate ;
}

void ExtraInputPanel::writeRotate( int rotate ) {
    this->rotate = rotate ;
    emit this->rotateChanged( rotate ) ;
}

void ExtraInputPanel::checkRotate( int screen ) {
    Q_UNUSED( screen ) ;
    int desktopWidth = QApplication::desktop()->width() ;
    int desktopHeight = QApplication::desktop()->height() ;
    if ( desktopWidth >= desktopHeight )
        this->writeRotate( 0 ) ;
    else 
        this->writeRotate( 1 ) ;
}

}
