#include "ui.h"

Pad::Pad( QString source, QWidget* parent ) : QWidget( parent ) {
    this->setWindowFlags( Qt::Dialog | Qt::FramelessWindowHint ) ;
    //QtGui.QWidget.__init__( self,  parent, QtCore.Qt.X11BypassWindowManagerHint | QtCore.Qt.WindowStaysOnTopHint )

    this->setAttribute( Qt::WA_TranslucentBackground, true ) ;

    QPalette palette = QPalette() ;
    palette.setColor( QPalette::Base, Qt::transparent ) ;

    this->view = new QDeclarativeView( this ) ;
    this->view->setAttribute( Qt::WA_TranslucentBackground, true ) ;
    this->view->setPalette( palette ) ;
    this->view->setSource( source ) ;

        //context = self.view.rootContext()
        //context.setContextProperty( "key", self )

        //self.setFocusPolicy( QtCore.Qt.NoFocus )
        //self.view.setFocusPolicy( QtCore.Qt.NoFocus )
}

//Pad::~Pad( QWidget* parent ) {
    //delete this->view ;
//}
