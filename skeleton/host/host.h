#ifndef HOST_H
#define HOST_H

#include <QObject>
#include <QWidget>

namespace adaptor {

class Adaptor ;

}


namespace host {

class Host : public QObject {

    Q_OBJECT

    friend class adaptor::Adaptor ;

public :
    QWidget* view ;
    adaptor::Adaptor* adaptor ;

    Host( QObject* parent = NULL ) ;
    void setView( QWidget* view ) ;

    Q_INVOKABLE void show() ;
    Q_INVOKABLE void hide() ;
    Q_INVOKABLE bool keyPress( int keycode, int modifiers ) ;
    Q_INVOKABLE bool keyRelease( int keycode, int modifiers ) ;
} ;

}

#endif 
