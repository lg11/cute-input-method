#ifndef EXTRA_H
#define EXTRA_H

#include <QDeclarativeView>
#include <QSize>

namespace extra {

class ExtraInputPanel : public QDeclarativeView {
    Q_OBJECT

    Q_PROPERTY( int rotate READ readRotate WRITE writeRotate NOTIFY rotateChanged ) 

signals :
    //void candidateUpdate() ;
    void replaceSurrounding( const QString& text ) ;
    void receiveSurrounding( const QString& surrounding ) ;
    void hided() ;
    void rotateChanged( int rotate ) ;

public :
    int rotate ;
    ExtraInputPanel( QWidget* parent = NULL ) ;
public slots :
    void keepSize( QSize size ) ;
    int readRotate() ;
    void writeRotate( int rotate ) ;
    void checkRotate( int screen = 0 ) ;
protected :
    virtual void closeEvent( QCloseEvent* event ) ;
    virtual void hideEvent( QHideEvent* event ) ;
public slots :
} ;

}

#endif
