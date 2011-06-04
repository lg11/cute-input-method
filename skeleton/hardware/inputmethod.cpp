#include <QGraphicsView>
#include <QGraphicsObject>
#include <QApplication>
#include <QDesktopWidget>
#include <QUrl>
#include <QRegion>

#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeComponent>

#include <mabstractinputmethodhost.h>
#include <mimgraphicsview.h>


#include "inputmethod.h"

#include <QDebug>

namespace inputmethod {

namespace {
    const QRect& computeDisplayRect( QWidget* widget = 0 ) {
        static const QRect rect( widget ? qApp->desktop()->screenGeometry( widget ) : qApp->desktop()->screenGeometry() ) ;
        return rect ;
    }
}

class Loader {
public :
    QGraphicsScene* const scene ;
    QDeclarativeEngine* const engine ;
    QGraphicsObject* content ;
    QDeclarativeComponent* component ;
    InputMethod* const inputmethod ;
    QRect area ;

    Loader( InputMethod* inputmethod ) :
        scene( new QGraphicsScene( computeDisplayRect(), inputmethod ) ),
        engine( new QDeclarativeEngine( inputmethod ) ),
        content( NULL ),
        component( NULL ),
        inputmethod( inputmethod )
    {
        this->engine->rootContext()->setContextProperty( "inputmethod", this->inputmethod ) ;
    }

    ~Loader() {
        delete this->engine ;
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

class InputMethodPrivate {
public :
    InputMethod* const q_ptr ;
    Loader* const loader ;
    QGraphicsView* const view ;

    Q_DECLARE_PUBLIC( InputMethod ) ;
    
    InputMethodPrivate( InputMethod* inputmethod, QWidget* mainWindow ) :
        q_ptr( inputmethod ) ,
        loader( new Loader( inputmethod ) ) ,
        view( new QGraphicsView( this->loader->scene, mainWindow ) )
    {
    }
    ~InputMethodPrivate() {
        delete this->view ;
        delete this->loader ;
    }
} ;

InputMethod::InputMethod( MAbstractInputMethodHost *host, QWidget *mainWindow ) : MAbstractInputMethod( host, mainWindow ), d_ptr( new InputMethodPrivate( this, mainWindow ) ) {
    qDebug() << "construct" ;
    Q_D( InputMethod ) ;
    d->loader->load( ".inputmethod/main.qml" ) ;

    QWidget* p = d->view->viewport() ;

    if ( p->nativeParentWidget() )
            p = p->nativeParentWidget() ;

    const QRect& rect( computeDisplayRect(p) ) ;
    d->view->resize( rect.size() ) ;
    d->view->setSceneRect( rect ) ;
    d->view->show() ;
    d->view->setFrameShape( QFrame::NoFrame ) ;
    d->view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff ) ;
    d->view->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff ) ;
}

InputMethod::~InputMethod() { delete this->d_ptr ; }

void InputMethod::show() {
    qDebug() << "show" ;
    Q_D( InputMethod ) ;
    this->inputMethodHost()->setRedirectKeys( true ) ;
    d->loader->show() ;

    const QRegion region( d->loader->area ) ;
    this->inputMethodHost()->setScreenRegion( region ) ;
    this->inputMethodHost()->setInputMethodArea( region ) ;
}

void InputMethod::hide() {
    qDebug() << "hide" ;
    Q_D( InputMethod ) ;
    //this->inputMethodHost()->setRedirectKeys( false ) ;
    d->loader->hide() ;
}

void InputMethod::update() {
    qDebug() << "update" ;
}

void InputMethod::handleFocusChange( bool focusIn ) {
    qDebug() << "focus" << focusIn ;
}

void InputMethod::processKeyEvent( QEvent::Type keyType, Qt::Key keyCode, Qt::KeyboardModifiers modifiers, const QString& text, bool autoRepeat, int count, quint32 nativeScanCode, quint32 nativeModifiers, unsigned long time) {
    qDebug() << "processKeyEvent" ;
}

int InputMethod::screenWidth() {
    return computeDisplayRect().width() ;
}

int InputMethod::screenHeight() {
    return computeDisplayRect().height() ;
}

void InputMethod::setInputMethodArea( const QRect &area ) {
    Q_D( InputMethod ) ;
    if ( d->loader->area != area ) {
        d->loader->area = area ;
        this->inputMethodHost()->setScreenRegion( region ) ;
        this->inputMethodHost()->setInputMethodArea( region ) ;
    }
}

}
