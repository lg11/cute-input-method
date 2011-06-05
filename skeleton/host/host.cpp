#include "host.h"
#include "adaptor.h"

#include <QDebug>


namespace host {

Host::Host( QObject* parent ) : QObject( parent ), view( NULL ), adaptor( new adaptor::Adaptor( this ) ) {
}

void Host::setView( QWidget* view ) {
    this->view = view ;
}

void Host::show() {
    if ( this->view )
        view->show() ;
}

void Host::hide() {
    if ( this->view )
        view->hide() ;
}

}
