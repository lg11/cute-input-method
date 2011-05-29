#ifndef IMENGINE_H
#define IMENGINE_H

#include <QObject>

class IMEngine : public QObject {
    Q_OBJECT
    Q_PROPERTY( QString name READ name )
public:
    QString name_value ;
    inline IMEngine( QObject* parent = NULL ) : QObject( parent ), name_value( "IMEngine" ) {}
    inline QString name() { return this->name_value ; }
} ;

#endif

