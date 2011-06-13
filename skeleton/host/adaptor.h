#ifndef ADAPTOR_H
#define ADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QDBusInterface>

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
    void querySurrounding() ;
    void queryCursorRect() ;
    void replaceSurrounding( const QString& text ) ;

public :
    //int extraCallCount ;
    host::Host* host ;
#ifdef Q_WS_MAEMO_5
    QDBusInterface* interface ;
#endif
    
    Adaptor( host::Host* host ) ;

public slots :
    //Q_NOREPLY void show() ;
    //Q_NOREPLY void hide() ;
    Q_NOREPLY void receiveMessage( const QString& message ) ;
    bool keyPress( int keycode, int modifiers ) ;
    bool keyRelease( int keycode, int modifiers ) ;
    Q_NOREPLY void receiveSurrounding( const QString& surrounding ) ;
    Q_NOREPLY void cursorRectUpdate( int x, int y, int width, int height ) ;
    Q_NOREPLY void focusIn() ;
    Q_NOREPLY void focusOut() ;
    Q_NOREPLY void requestSoftwareInputPanel() ;
    Q_NOREPLY void closeSoftwareInputPanel() ;
    Q_NOREPLY void preeditStart() ;
    Q_NOREPLY void preeditEnd() ;
    Q_NOREPLY void setInputDevice( int index ) ;
#ifdef Q_WS_MAEMO_5
    Q_NOREPLY void checkKeyboardStatus() ;
#endif
} ;

}

#endif
