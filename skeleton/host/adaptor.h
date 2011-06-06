#ifndef ADAPTOR_H
#define ADAPTOR_H

#include <QDBusAbstractAdaptor>

namespace host {

class Host ;

}

namespace adaptor {

class Adaptor : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_CLASSINFO( "D-Bus Interface", "inputmethod.host" )

    friend class host::Host ;
 
signals :
    void sendMessage( const QString& message ) ;
    void sendCommit( const QString& text ) ;
    //void sendKeyEvent( int type, int keycode, int modifiers, bool autoRepeat, const QString& text, int count ) ;
    void sendKeyEvent( int type, int keycode, int modifiers ) ;
    void cursorRectUpdate( int x, int y, int width, int height ) ;

public :
    host::Host* host ;
    
    Adaptor( host::Host* host ) ;

public slots :
    Q_NOREPLY void show() ;
    Q_NOREPLY void hide() ;
    Q_NOREPLY void receiveMessage( const QString& message ) ;
    bool keyPress( int keycode, int modifiers ) ;
    bool keyRelease( int keycode, int modifiers ) ;
} ;

}

#endif
