#ifndef HOST_H
#define HOST_H

#include <QObject>
#include <QWidget>
#include <QMetaMethod>

namespace handle {
class Handle ;
}
namespace adaptor {
class Adaptor ;
}

namespace host {

enum InputDevice { UnknownInputDevice = 0, HardwareInputDevice = 1, OnscreenInputDevice = 2 } ;
enum InputLanguage { UnknownLanguage = 0, SimplifiedChinese = 1 } ;

class Host : public QObject {

    Q_OBJECT

    friend class adaptor::Adaptor ;

signals :
    void inputDeviceChanged() ;
    void inputLanguageChanged() ;
    void cursorRectUpdate( int x, int y, int width, int height ) ;
    //void receiveSurrounding( const QString& surrounding ) ;
    //void setKeyboardLayout( int layout ) ;
    //void queryStatus() ;
    //void sendStatus( int inputDevice, int inputLanguage ) ;

public :
    QWidget* view ;
    QObject* handle ;
    QRect cursorRect ;
    InputDevice inputDevice ;
    InputLanguage inputLanguage ;
    adaptor::Adaptor* adaptor ;

    QMetaMethod processKeyPress ;
    QMetaMethod processKeyRelease ;
    QMetaMethod requestReset ;

    Host( QObject* parent = NULL ) ;
    void setView( QWidget* view ) ;
    void setHandle( QObject* handle ) ;

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
