#include <QGraphicsView>
#include <QGraphicsObject>
#include <QApplication>
#include <QDesktopWidget>
#include <QUrl>
#include <QRect>
#include <QRegion>
#include <QKeyEvent>

#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeComponent>

#include <mabstractinputmethodhost.h>
#include <mimgraphicsview.h>


#include "inputmethod.h"

#include <QDebug>

namespace inputmethod {

const QRect& display_rect( QWidget* widget = NULL ) {
    static const QRect rect( widget ? QApplication::desktop()->screenGeometry( widget ) : QApplication::desktop()->screenGeometry() ) ;
    return rect ;
}

class InputMethodPrivate {
public :
    Q_DECLARE_PUBLIC( InputMethod ) ;
    InputMethod* const q_ptr ;
    QGraphicsScene* const scene ;
    QGraphicsView* const view ;
    QDeclarativeEngine* const engine ;
    QGraphicsObject* content ;
    QDeclarativeComponent* component ;
    QRect inputMethodArea ;
    QRect cursorRect ;
    
    InputMethodPrivate( InputMethod* inputmethod, QWidget* mainWindow ) :
        q_ptr( inputmethod ) ,
        scene( new QGraphicsScene( display_rect(), inputmethod ) ),
        view( new QGraphicsView( this->scene, mainWindow ) ) ,
        engine( new QDeclarativeEngine( inputmethod ) ),
        content( NULL ),
        component( NULL )
    {
        this->engine->rootContext()->setContextProperty( "inputmethod", inputmethod ) ;
    }

    ~InputMethodPrivate() {
        if ( this->content )
            delete this->content ;
        if ( this->component )
            delete this->component ;
        delete this->engine ;
        delete this->view ;
    }

    void show() {
        if ( this->content )
            this->content->show() ;
    }

    void hide() {
        if ( this->content )
            this->content->hide() ;
    }

    void load( const QString& path ) {
        this->component = new QDeclarativeComponent( this->engine, QUrl( path ) ) ;
        this->content = qobject_cast<QGraphicsObject*>( this->component->create() ) ;
        this->scene->addItem( content ) ;
    }

} ;



InputMethod::InputMethod( MAbstractInputMethodHost *host, QWidget *mainWindow ) : MAbstractInputMethod( host, mainWindow ), d_ptr( new InputMethodPrivate( this, mainWindow ) ) {
    qDebug() << "inputmethod" << "construct" ;
    Q_D( InputMethod ) ;
    d->load( ".inputmethod/main.qml" ) ;

    QWidget* viewport = d->view->viewport() ;

    if ( viewport->nativeParentWidget() )
            viewport = viewport->nativeParentWidget() ;

    const QRect& rect( display_rect( viewport ) ) ;
    d->view->resize( rect.size() ) ;
    d->view->setSceneRect( rect ) ;
    d->view->show() ;
    d->view->setFrameShape( QFrame::NoFrame ) ;
    d->view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff ) ;
    d->view->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff ) ;
}

InputMethod::~InputMethod() { delete this->d_ptr ; }

void InputMethod::show() {
    qDebug() << "inputmethod" << "show" ;
    Q_D( InputMethod ) ;
    this->inputMethodHost()->setRedirectKeys( true ) ;
    d->show() ;
    d->view->show() ;

    //const QRegion r( display_rect() ) ;
    const QRegion region( d->inputMethodArea ) ;
    this->inputMethodHost()->setScreenRegion( region ) ;
    this->inputMethodHost()->setInputMethodArea( region ) ;
}

void InputMethod::hide() {
    qDebug() << "inputmethod" << "hide" ;
    Q_D( InputMethod ) ;
    d->hide() ;
    d->view->hide() ;

    const QRegion region ;
    this->inputMethodHost()->setScreenRegion( region ) ;
    this->inputMethodHost()->setInputMethodArea( region ) ;
}

void InputMethod::setPreedit( const QString &preeditString, int cursorPos ) {
    qDebug() << "inputmethod" << "setPreedit" ;
}

void InputMethod::update() {
    qDebug() << "inputmethod" << "update" ;
    Q_D( InputMethod ) ;
    bool flag ;
    const QRect cursorRect( this->inputMethodHost()->cursorRectangle( flag ) ) ;
    if ( flag && d->cursorRect != cursorRect ) {
        d->cursorRect = cursorRect ;
        emit this->cursorRectChanged( d->cursorRect ) ;
    }
}

void InputMethod::reset() {
    qDebug() << "inputmethod" << "reset" ;
}

void InputMethod::handleMouseClickOnPreedit( const QPoint &pos, const QRect &preeditRect ) {
    qDebug() << "inputmethod" << "handleMouseClickOnPreedit" ;
}

void InputMethod::handleFocusChange( bool focusIn ) {
    qDebug() << "inputmethod" << "handleFocusChange" ;
    if ( focusIn )
        this->show() ;
    else
        this->hide() ;
}

void InputMethod::handleVisualizationPriorityChange( bool priority ) {
    qDebug() << "inputmethod" << "handleVisualizationPriorityChange" ;
}

void InputMethod::handleAppOrientationAboutToChange( int angle ) {
    qDebug() << "inputmethod" << "handleAppOrientationAboutToChange" ;
}

void InputMethod::handleAppOrientationChanged( int angle) {
    qDebug() << "inputmethod" << "handleAppOrientationChanged" ;
}
void InputMethod::setToolbar( QSharedPointer<const MToolbarData> toolbar ) {
    qDebug() << "inputmethod" << "setToolbar" ;
}

void InputMethod::processKeyEvent( QEvent::Type keyType, Qt::Key keyCode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count, quint32 nativeScanCode, quint32 nativeModifiers, unsigned long time) {
    qDebug() << "inputmethod" << "processKeyEvent" << keyCode << nativeScanCode << text ;
    Q_D( InputMethod ) ;
    QVariant flag = false;
    if ( keyType == QEvent::KeyPress ) {
        if ( text.isEmpty() ) {
            QMetaObject::invokeMethod( d->content, "processKeyEvent", Q_RETURN_ARG( QVariant, flag ), Q_ARG( QVariant, keyCode ) ) ;
            if ( !flag.toBool() ) {
                QKeyEvent event( keyType, keyCode, modifiers ) ;
                this->inputMethodHost()->sendKeyEvent( event ) ;
            }
        }
        else {
            QMetaObject::invokeMethod( d->content, "processKeyEvent", Q_RETURN_ARG( QVariant, flag ), Q_ARG( QVariant, keyCode + 32 ) ) ;
            if ( !flag.toBool() ) {
                this->sendCommit( text ) ;
            }
        }
    }

}
void InputMethod::setState( const QSet<MInputMethod::HandlerState> &state ) {
    qDebug() << "inputmethod" << "setState" ;
}

void InputMethod::handleClientChange() {
    qDebug() << "inputmethod" << "handleClientChange" ;
}

void InputMethod::switchContext( MInputMethod::SwitchDirection direction, bool enableInAnimation ) {
    qDebug() << "inputmethod" << "switchContext" ;
}

QList<InputMethod::MInputMethodSubView> InputMethod::subViews( MInputMethod::HandlerState state ) const {
    qDebug() << "inputmethod" << "subViews" ;
    return QList<InputMethod::MInputMethodSubView>() ;
}

void InputMethod::setActiveSubView( const QString &subViewId, MInputMethod::HandlerState state ) {
    qDebug() << "inputmethod" << "setActiveSubView" ;
}

QString InputMethod::activeSubView( MInputMethod::HandlerState state ) const {
    qDebug() << "inputmethod" << "activeSubView" ;
    return "" ;
}

void InputMethod::showLanguageNotification() {
    qDebug() << "inputmethod" << "showLanguageNotification" ;
}

void InputMethod::setKeyOverrides( const QMap<QString, QSharedPointer<MKeyOverride> > &overrides ) {
    qDebug() << "inputmethod" << "setKeyOverrides" ;
}

bool InputMethod::imExtensionEvent( MImExtensionEvent *event) {
    qDebug() << "inputmethod" << "imExtensionEvent" ;
    return false ;
}

int InputMethod::screenWidth() {
    return display_rect().width() ;
}

int InputMethod::screenHeight() {
    return display_rect().height() ;
}

QRect& InputMethod::cursorRect() {
    Q_D( InputMethod ) ;
    return d->cursorRect ;
}

void InputMethod::setScreenRegion( const QRect &area ) {
    Q_D( InputMethod ) ;
    QRegion region( area ) ;
    this->inputMethodHost()->setScreenRegion( region ) ;
}

void InputMethod::setInputMethodArea( const QRect &area ) {
    Q_D( InputMethod ) ;
    if ( d->inputMethodArea != area ) {
        d->inputMethodArea = area ;
        QRegion region( d->inputMethodArea ) ;
        this->inputMethodHost()->setInputMethodArea( region ) ;
    }
}

//void InputMethod::sendKeyEvent( const QString& text ) {}

void InputMethod::sendCommit( const QString& text ) {
    if ( text == "\b" ) {
        QKeyEvent event( QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier ) ;
        this->inputMethodHost()->sendKeyEvent( event ) ;
    } 
    else if ( text == "\r\n" ) {
        QKeyEvent event( QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier );
        this->inputMethodHost()->sendKeyEvent( event ) ;
    } else {
        this->inputMethodHost()->sendCommitString( text ) ;
    }
}


}
