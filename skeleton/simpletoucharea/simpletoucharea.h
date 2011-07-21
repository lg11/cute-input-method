#ifndef SIMPLETOUCHAREA_H
#define SIMPLETOUCHAREA_H

#include <QObject>
#include <QDeclarativeItem>
#include <QEvent>

class SimpleTouchArea : public QDeclarativeItem {
    Q_OBJECT
public:
    inline SimpleTouchArea( QDeclarativeItem* parent = NULL ) : QDeclarativeItem( parent ) {
        this->setAcceptTouchEvents( true ) ;
        this->setFiltersChildEvents( true ) ;
    }
    inline ~SimpleTouchArea() {}
    //inline sceneEvent( QGraphicsItem* item, Q
    //Q_INVOKABLE inline void reset() { this->length = 0 ; this->time.restart() ; }
} ;

#endif

