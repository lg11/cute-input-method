#include "pad.h"

#include <QApplication>

int main( int argc, char** argv ){
    QApplication app( argc, argv ) ;

    Pad* pad = new Pad() ;

    pad->show() ;

    return app.exec() ;
}

