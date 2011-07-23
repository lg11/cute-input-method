#ifndef SIMPLETOUCHAREA_H
#define SIMPLETOUCHAREA_H

#include <QObject>
#include <QDeclarativeItem>
#include <QEvent>
#include <QTouchEvent>

#include <QDebug>

class SimpleTouchArea : public QDeclarativeItem {
    Q_OBJECT
public:
    SimpleTouchArea( QDeclarativeItem* parent = NULL ) : QDeclarativeItem( parent ) {
        this->setAcceptTouchEvents( true ) ;
        this->setFiltersChildEvents( true ) ;
    }
    ~SimpleTouchArea() {}
    bool processTouchBegin( QTouchEvent* event ) {
        const QList<QTouchEvent::TouchPoint>& points = event->touchPoints() ;
        foreach( const QTouchEvent::TouchPoint& point, points )
            qDebug() << "id = " << point.id() ;
        return true ;
    }
    virtual bool event( QEvent* event ) {
        //qDebug() << "event" ;
        //qDebug() << "start" ;
        bool flag ;
        switch ( event->type() ) {
            case QEvent::TouchBegin :
                qDebug() << "TouchBegin" ;
                this->processTouchBegin( static_cast<QTouchEvent*>(event) ) ;
                flag = true ;
                break ;
            case QEvent::TouchUpdate :
                qDebug() << "TouchUpdate" ;
                flag = true ;
                break ;
            case QEvent::TouchEnd :
                qDebug() << "TouchEnd" ;
                flag = true ;
                break ;
            default :
                //qDebug() << "default" ;
                flag = QDeclarativeItem::event( event ) ;
                break ;
        }
        //qDebug() << "end" ;
        return flag ;
    }
    //virtual bool sceneEvent( QGraphicsItem* item, QEvent* event ) {}
    //Q_INVOKABLE inline void reset() { this->length = 0 ; this->time.restart() ; }
} ;

#endif

