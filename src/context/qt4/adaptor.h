#ifndef ADAPTOR_H
#define ADAPTOR_H

#include <QDBusAbstractAdaptor>

namespace context {

class Context ;

}

namespace adaptor {

class Adaptor : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_CLASSINFO( "D-Bus Interface", "inputmethod.context" )

    friend class context::Context ;

signals :
    void sendMessage( const QString& message ) ;
    void requestSoftwareInputPanel() ;
    void closeSoftwareInputPanel() ;
    void focusIn() ;
    void focusOut() ;
    void cursorRectUpdate( int x, int y, int width, int height ) ;
    void sendSurrounding( const QString& surrounding ) ;
#ifdef Q_WS_MAEMO_5
    void setFocusedWindowId( quint64 id ) ;
#endif

public :
    context::Context* context ;
    
    Adaptor( context::Context* context ) ;

public slots :
    Q_NOREPLY void receiveMessage( const QString& message ) ;
    Q_NOREPLY void receiveCommit( const QString& text ) ;
    Q_NOREPLY void receiveKeyEvent( int type, int keycode, int modifiers ) ;
    Q_NOREPLY void querySurrounding() ;
    Q_NOREPLY void queryCursorRect() ;
    Q_NOREPLY void replaceSurrounding( const QString& text ) ;

} ;

}

#endif
