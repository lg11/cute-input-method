#ifndef HOST_H
#define HOST_H

#include <QObject>
#include <QWidget>

namespace engine {
class Engine ;
}

namespace adaptor {
class Adaptor ;
}


namespace host {

class Host : public QObject {

    Q_OBJECT

    friend class adaptor::Adaptor ;

signals :

public :
    QWidget* view ;
    adaptor::Adaptor* adaptor ;
    engine::Engine* engine ;
    QRect cursorRect ;

    Host( QObject* parent = NULL ) ;
    void setView( QWidget* view ) ;

    Q_INVOKABLE void show() ;
    Q_INVOKABLE void hide() ;
    Q_INVOKABLE bool keyPress( int keycode, int modifiers ) ;
    Q_INVOKABLE bool keyRelease( int keycode, int modifiers ) ;
    Q_INVOKABLE void sendCommit( const QString& text ) ;
    Q_INVOKABLE void sendKeyPress( int keycode, int modifiers ) ;
    Q_INVOKABLE void sendKeyRelease( int keycode, int modifiers ) ;
} ;

}

#endif 
