#ifndef CONTEXT_H
#define CONTEXT_H

#include <QInputContext>
#include <QDBusInterface>

namespace adaptor {
class Adaptor ;
}

namespace context {

class Context : public QInputContext {
    Q_OBJECT

    friend class adaptor::Adaptor ;

public :
    adaptor::Adaptor* adaptor ;
    QDBusInterface* interface ;
    //QRect cursorRect ;

    Context( QObject* parent = NULL ) ;
    virtual bool filterEvent( const QEvent* event ) ;
    virtual QString identifierName() ;
    virtual bool isComposing() const ;
    virtual QString language() ;
    virtual void mouseHandler( int x, QMouseEvent* event ) ;
    virtual void reset() ;
    virtual void setFocusWidget( QWidget* widget ) ;
    virtual void update() ;

    void checkCursorRect() ;
} ;

}

#endif 
