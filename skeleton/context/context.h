#ifndef CONTEXT_H
#define CONTEXT_H

#include <QInputContext>
#include <QStack>
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
    QStack<QEvent> eventStack ;

    Context( QObject* parent = NULL ) ;
    virtual bool filterEvent( const QEvent* event ) ;
    virtual QString identifierName() ;
    virtual bool isComposing() const ;
    virtual void reset() ;
    virtual void setFocusWidget( QWidget* widget ) ;
    virtual void update() ;
    virtual QString language() ;
} ;

}

#endif 
