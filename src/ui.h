#ifndef __UI_H
#define __UI_H

#include <QWidget>
#include <QDeclarativeView>

class Pad : public QWidget {
    //Q_OBJECT ;
public :
    QDeclarativeView* view ;
    Pad( QString source, QWidget* parent = NULL ) ;
    //~Pad() ;
} ;

#endif
