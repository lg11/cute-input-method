#ifndef INPUTMETHOD_H
#define INPUTMETHOD_H

#include <mabstractinputmethod.h>

#include <QRect>

namespace inputmethod {

class InputMethodPrivate ;

class InputMethod : public MAbstractInputMethod {
    Q_OBJECT
    Q_PROPERTY( int screenWidth READ screenWidth NOTIFY screenWidthChanged )
    Q_PROPERTY( int screenHeight READ screenHeight NOTIFY screenHeightChanged )
    Q_PROPERTY( QRect cursorRect READ cursorRect NOTIFY cursorRectChanged )

signals :
    void screenWidthChanged( int width ) ;
    void screenHeightChanged( int height ) ;
    void cursorRectChanged( QRect& cursorRect ) ;
    //void keyEvent() ;

public :
    explicit InputMethod( MAbstractInputMethodHost *host, QWidget *mainWindow ) ;
    virtual ~InputMethod() ;

    virtual void show() ;
    virtual void hide() ;
    virtual void setPreedit( const QString &preeditString, int cursorPos ) ;
    virtual void update() ;
    virtual void reset() ;
    virtual void handleMouseClickOnPreedit( const QPoint &pos, const QRect &preeditRect ) ;
    virtual void handleFocusChange( bool focusIn ) ;
    virtual void handleVisualizationPriorityChange( bool priority ) ;
    virtual void handleAppOrientationAboutToChange( int angle ) ;
    virtual void handleAppOrientationChanged( int angle) ;
    virtual void setToolbar( QSharedPointer<const MToolbarData> toolbar ) ;
    virtual void processKeyEvent( QEvent::Type keyType, Qt::Key keyCode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count, quint32 nativeScanCode, quint32 nativeModifiers, unsigned long time) ;
    virtual void setState( const QSet<MInputMethod::HandlerState> &state ) ;
    virtual void handleClientChange() ;
    virtual void switchContext( MInputMethod::SwitchDirection direction, bool enableAnimation ) ;
    virtual QList<MInputMethodSubView> subViews( MInputMethod::HandlerState state = MInputMethod::OnScreen ) const ;
    virtual void setActiveSubView( const QString &subViewId, MInputMethod::HandlerState state = MInputMethod::OnScreen ) ;
    virtual QString activeSubView( MInputMethod::HandlerState state = MInputMethod::OnScreen ) const ;
    virtual void showLanguageNotification() ;
    virtual void setKeyOverrides( const QMap<QString, QSharedPointer<MKeyOverride> > &overrides ) ;
    virtual bool imExtensionEvent( MImExtensionEvent *event) ;

    int screenWidth() ;
    int screenHeight() ;
    QRect& cursorRect() ;
    Q_INVOKABLE void setScreenRegion( const QRect &area ) ;
    Q_INVOKABLE void setInputMethodArea( const QRect &area ) ;
    Q_INVOKABLE void sendCommit( const QString& text ) ;

private :
    Q_DISABLE_COPY( InputMethod ) ;
    Q_DECLARE_PRIVATE( InputMethod ) ;
    InputMethodPrivate* const d_ptr ;
} ;

}
#endif
