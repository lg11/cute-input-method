#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QList>
#include <QString>
#include <QStringList>
#include <QSet>
#include <QFile>
#include <QTimer>
#include <QTextStream>

#include "../lookup/lookup.h"
#include "../lookup/t9.h"

namespace handle {
class Handle ;
}

namespace engine {

typedef QPair<QString, QString> KeyPair ;
typedef QPair<QChar, qreal> WordPair ;
typedef QPair<KeyPair, WordPair> SelectedPair ;

//typedef QPair<QStringList, QStringList> KeyPair ;
//typedef QPair< QString, QList<qreal> > WordPair ;

class Engine : public QObject {
    Q_OBJECT

    friend class handle::Handle ;

signals :
    void preeditStart() ;
    void preeditEnd() ;
    void sendCommit( const QString& text ) ;
    void candidateUpdate() ;

public:
    enum KeyboardLayout { UnknownKeyboardLayout = 0, FullKeyboardLayout = 1, T9KeyboardLayout = 2 } ;
    lookup::Lookup lookup ;
    t9::T9Lookup t9lookup ;
    QList<SelectedPair> selected ;
    QString selectedWord ;
    int pageIndex ;
    const lookup::Candidate* candidate ;
    KeyboardLayout keyboardLayout ;
    QFile* logFile ;
    QTextStream* textStream ;
    QTimer flushTimer ;

    Engine( QObject* parent = NULL ) ;

    ~Engine() ;

public slots :

    void startLog( const QString& path ) ;

    void stopLog() ;

    void flushLog() ;
    
    void load( const QString& path ) ;
    
    bool prevPage() ;
    
    bool nextPage() ;
    
    int getCodeLength() const ;
    
    int getPreeditLength() const ;
    
    int getInvalidCodeLength() const ;

    int getSelectedLength() const ;

    int getSelectedWordLength() const ;
   
    bool updateCandidate( int index ) ;
    
    QString getCode() const ;

    QString getWord() const ;
    
    QString getPreeditCode() const ;

    QString getInvalidCode() const ;

    QString getSelectedWord() const ;

    bool checkCommit() ;

    bool select( int index ) ;

    bool deselect() ;

    void reset() ;

    bool appendCode( QChar code ) ;

    //bool processKey( int keycode ) ;

    bool appendCode( const QString& code ) ;

    bool popCode() ;

    void commit() ;

    bool setKeyboardLayout( KeyboardLayout layout ) ;

    bool setKeyboardLayout( int layout ) ;

} ;

}

#endif

