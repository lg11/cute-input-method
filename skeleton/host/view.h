#ifndef VIEW_H
#define VIEW_H

#include <QDeclarativeView>

namespace view {

class View : public QDeclarativeView {
    Q_OBJECT

    Q_PROPERTY( int displayWidth READ displayWidth NOTIFY displayWidthChanged ) 
    Q_PROPERTY( int displayHeight READ displayHeight NOTIFY displayHeightChanged ) 
    Q_PROPERTY( QRect cursorRect READ readCursorRect NOTIFY cursorRectUpdate )

signals :
    void displayWidthChanged( int width ) ;
    void displayHeightChanged( int height ) ;
    void cursorRectUpdate( const QRect& cursorRect ) ;
public :
    int displayOffsetX ;
    int displayOffsetY ;
    int displayWidthHint ;
    int displayHeightHint ;
    QSize displaySize ;
    QRect cursorRect ;

    View( QWidget* parent = NULL ) ;
    Q_INVOKABLE int displayWidth() ;
    Q_INVOKABLE int displayHeight() ;
public slots :
    void addInputRegion( const QRect& rect) ;
    void clearInputRegion() ;
    void checkDisplaySize( int screen ) ;
    const QRect& readCursorRect() ;
    void cursorRectUpdate( int x, int y, int width, int height ) ;
} ;

}

#endif
