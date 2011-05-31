#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>
#include <QString>
#include <QApplication>
#include <QClipboard>
//#include <QDebug>

class Clipboard : public QObject {
    Q_OBJECT
public:
    QClipboard* clipboard ;
    inline Clipboard( QObject* parent = NULL ) : QObject( parent ) { this->clipboard = QApplication::clipboard() ; }
    Q_INVOKABLE inline QString get() {
        return this->clipboard->text() ;
    }
    Q_INVOKABLE inline void set( const QString& text ) {
        this->clipboard->setText( text ) ;
    }
} ;

#endif

