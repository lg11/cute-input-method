#ifndef ADAPTOR_H
#define ADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QDBusInterface>

#ifdef Q_WS_MAEMO_5
namespace extra {
class ExtraInputPanel ;
}
#endif
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
    void sendStatus( int inputDevice, int inputLanguage ) ;

public :
#ifdef Q_WS_MAEMO_5
    QDBusInterface* interface ;
    extra::ExtraInputPanel* extraInputPanel ;
    quint64 focusedWindowId ;
#endif
    host::Host* host ;
    
    Adaptor( host::Host* host ) ;
#ifdef Q_WS_MAEMO_5
    void setExtraInputPanel( extra::ExtraInputPanel* extraInputPanel ) ;
#endif

public slots :
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
    Q_NOREPLY void setInputDevice( int inputDevice ) ;
    Q_NOREPLY void setInputLanguage( int inputLanguage ) ;
    Q_NOREPLY void queryStatus() ;
#ifdef Q_WS_MAEMO_5
    Q_NOREPLY void checkKeyboardStatus() ;
    Q_NOREPLY void setFocusedWindowId( quint64 id ) ;
    quint64 getFocusedWindowId() ;
#endif
} ;

}

#endif
