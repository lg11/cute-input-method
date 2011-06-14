#ifndef HOST_H
#define HOST_H

#include <QObject>
#include <QWidget>
#include <QMetaMethod>

//namespace engine {
//class Engine ;
//}

namespace adaptor {
class Adaptor ;
}


namespace host {

enum InputDevice { UnknownInputDevice = 0, HardwareInputDevice = 1, OnscreenInputDevice = 2 } ;

class Host : public QObject {

    Q_OBJECT

    friend class adaptor::Adaptor ;

signals :
    void inputDeviceChanged() ;
    void cursorRectUpdate( int x, int y, int width, int height ) ;
    void receiveSurrounding( const QString& surrounding ) ;
    void setKeyboardLayout( int layout ) ;
    void queryStatus() ;
    void sendStatus( int status ) ;

public :
    QWidget* view ;
    QWidget* extraInputPanel ;
    QObject* engine ;
    QRect cursorRect ;
    InputDevice inputDevice ;
    adaptor::Adaptor* adaptor ;

    QMetaMethod processKeyPress ;
    QMetaMethod processKeyRelease ;

    Host( QObject* parent = NULL ) ;
    void setView( QWidget* view ) ;
    void setExtraInputPanel( QWidget* extraInputPanel ) ;
    void setEngine( QObject* engine ) ;

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
