#ifndef IMENGINE_H
#define IMENGINE_H

#include <QObject>
#include <QList>
#include <QTime>
#include <QPoint>

class MouseTrack : public QObject {
    Q_OBJECT
public:
    QList<qreal> x ;
    QList<qreal> y ;
    QList<int> t ;
    int length ;
    QTime time ;
    inline MouseTrack( QObject* parent = NULL ) : QObject( parent ), x(), y(), t(), length(0), time() { this->time.start() ; }
    inline void check() {
        if ( this->length >= this->x.length() ) {
            this->x.append( 0 ) ;
            this->y.append( 0 ) ;
            this->t.append( 0 ) ;
        }
    }
    Q_INVOKABLE inline void reset() { this->length = 0 ; this->time.restart() ; }
    Q_INVOKABLE inline void push( qreal x, qreal y ) {
        this->check() ;
        this->x[this->length] = x ;
        this->y[this->length] = y ;
        this->t[this->length] = this->time.elapsed() ;
        this->length++ ;
    }
    Q_INVOKABLE inline void stop() {
        qreal endX ;
        qreal endY ;
        if ( this->length > 1 ) {
            int index = this->length - 1 ;
            qreal lastX = this->x.at(index) ;
            qreal lastY = this->y.at(index) ;
            int lastT = this->t.at(index) ;
            bool flag = false ;
            int i = index ;
            for ( ; i >= 0 && !flag ; i-- ) {
                if ( lastT - this->t.at(i) > 90 ) 
                    flag = true ;
            }
            if ( flag ) {
                qreal prevX = this->x.at(i) ; qreal prevY = this->y.at(i) ; int prevT = this->t.at(i) ;
                i++ ;
                qreal nextX = this->x.at(i) ; qreal nextY = this->y.at(i) ; int nextT = this->t.at(i) ;
                qreal r = qreal( lastT - 90 - prevT ) / qreal( nextT - prevT ) ;
                qreal dx = nextX - prevX ;
                qreal dy = nextY - prevY ;
                dx = dx * r ;
                dy = dy * r ;
                endX = prevX + dx ;
                endY = prevY + dy ;
            }
            else {
                qreal prevX = this->x.at(0) ; qreal prevY = this->y.at(0) ;
                qreal x = ( prevX + lastX ) / 2 ;
                qreal y = ( prevY + lastY ) / 2 ;
                endX = x ;
                endY = y ;
            }
        }
        else if ( this->length > 0 ) {
            endX = this->x.at(0) ; endY = this->y.at(0) ;
        }
        else {
            endX = 0 ; endY = 0 ;
        }
        this->push( endX, endY ) ;
    }
    Q_INVOKABLE inline QPoint get() {
        int index = this->length - 1 ;
        return QPoint( this->x.at(index), this->y.at(index) ) ;
    }
} ;

#endif

