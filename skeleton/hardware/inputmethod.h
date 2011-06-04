#ifndef INPUTMETHOD_H
#define INPUTMETHOD_H

#include <mabstractinputmethod.h>

#include <QTimer>

namespace inputmethod {

class InputMethodPrivate ;

class InputMethod : public MAbstractInputMethod {
    Q_OBJECT

public :
    explicit InputMethod( MAbstractInputMethodHost *host, QWidget *mainWindow ) ;
    virtual ~InputMethod() ;

    /*! \brief Shows the input method.
     */
    virtual void show() ;

    /*! \brief Hides the input method
     */
    virtual void hide() ;

    /*! \brief Sets preedit string of the input method server
     *  \param preeditString preedit string
     *  \param cursorPos the cursor position inside preedit.
     *
     *  Note: This method is used by application to initiate the predit and the cursor
     *  position for input method server. Input method server fully controls the preedit
     *  and the cursor inside it. (Input method server decides whether and where to show
     *  cursor inside preedit).
     */
    //virtual void setPreedit( const QString &preeditString, int cursorPos ) ;

    /*! \brief Update input method server state
     */
    virtual void update() ;

    /*! \brief Resets input method server state
     */
    //virtual void reset() ;

    /*! \brief Notifies input method server about mouse click on the preedit string
     */
    //virtual void handleMouseClickOnPreedit( const QPoint &pos, const QRect &preeditRect ) ;

    /*! \brief Notifies input method server about changed focus
     *  \param focusIn true - focus has entered a widget, false - focus has left a widget
     */
    virtual void handleFocusChange( bool focusIn ) ;

    /*! \brief Notifies that the focus widget in application changed visualization priority
     */
    //virtual void handleVisualizationPriorityChange( bool priority ) ;

    /*! \brief Target application is about to change orientation. Input method usually changes its
     *  own orientation according to this.
     */
    //virtual void handleAppOrientationAboutToChange( int angle ) ;

    /*! \brief Target application already finish changing orientation. Input method usually
     *  changes its own orientation according to this.
     */
    //virtual void handleAppOrientationChanged( int angle) ;

    /*!
     * \brief Uses a custom toolbar which is defined by given parameter.
     * \param toolbar Pointer to toolbar definition.
     */
    //virtual void setToolbar( QSharedPointer<const MToolbarData> toolbar );

    /*!
     * \brief Process a key event redirected from hardware keyboard to input method.
     *
     * This is called only if one has enabled redirection by calling
     * \a MInputContextConnection::setRedirectKeys.
     */
    virtual void processKeyEvent( QEvent::Type keyType, Qt::Key keyCode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count, quint32 nativeScanCode, quint32 nativeModifiers, unsigned long time) ;

    /* \brief This method is called to inform about keyboard status changes
     *
     * That is, hardware keyboard is opened or closed, BT keyboard is connected or
     * disconnected
     * \param state set of current states for this plugin
     */
    //virtual void setState( const QSet<MInputMethod::HandlerState> &state ) ;

    /*! \brief This method is called when target client is changed.
     */
    //virtual void handleClientChange() ;

    /*!
     * \brief Switch context to given direction
     * \param direction Switching direction
     * \param enableAnimation Contains true if swipe should be animated
     */
    //virtual void switchContext( MInputMethod::SwitchDirection direction, bool enableAnimation ) ;

    /*! \brief Returns all subviews (IDs and titles) which are supported for \a state.
     *
     * Implement this function to return the subviews which are supported by this input
     * method for the specified state. The subview titles will be shown in the input method settings.
     */
    //virtual QList<MInputMethodSubView> subViews( MInputMethod::HandlerState state = MInputMethod::OnScreen ) const ;  
 
    /*!
     * \brief Sets \a subViewId as the active subview for \a state.
     * \param subViewId the identifier of subview.
     * \param state the state which \a subViewId belongs to.
     *
     *  Implement this method to set the active subview. Input method plugins manager will call
     *  this method when active subview for specified state is changed from the input method
     *  settings.
     */
    //virtual void setActiveSubView( const QString &subViewId, MInputMethod::HandlerState state = MInputMethod::OnScreen ) ;

    /*!
     * \brief Returns current active subview ID for \a state.
     *
     *  Implement this method to inform input method plugins manager about current active subview
     *  for specified state.
     */
    //virtual QString activeSubView( MInputMethod::HandlerState state = MInputMethod::OnScreen ) const ;

    //! Show notification informing about current language
    //virtual void showLanguageNotification() ;

    /*!
     * \brief Uses custom key overrides which are defined by given parameter.
     * \param overrides Pointer to key override definitions.
     */
    //virtual void setKeyOverrides( const QMap<QString, QSharedPointer<MKeyOverride> > &overrides ) ;

    /*!
     * \brief handles extension event not covered by separate method.
     * \param event event to handle
     * 
     * Should return true if event is handled, otherwise false.
     */
    virtual bool imExtensionEvent( MImExtensionEvent *event) ;

private :
    Q_DISABLE_COPY( InputMethod ) ;
    Q_DECLARE_PRIVATE( InputMethod ) ;
    InputMethodPrivate* const d_ptr ;
} ;

}
#endif
