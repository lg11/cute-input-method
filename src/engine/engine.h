#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QPair>
#include <QList>
#include <QString>
#include <QFile>
#include <QTimer>
#include <QTextStream>

namespace lookup {
class Lookup ;
}

namespace t9 {
class T9Lookup ;
}

namespace handle {
class Handle ;
}

namespace engine {

typedef QPair<const QString*, const QString*> KeyPair ;
typedef QPair<const QString*, qreal > WordPair ;
typedef QPair<KeyPair, WordPair> CandPair ;
typedef QPair<CandPair, int> Candidate ;

typedef QPair<QString, QString> SelectedKeyPair ;
typedef QPair< QString, QList<qreal> > SelectedWordPair ;
typedef QPair<SelectedKeyPair, SelectedWordPair> SelectedPair ;

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
    lookup::Lookup* lookup ;
    t9::T9Lookup* t9lookup ;
    SelectedPair selected ;
    QString* selectedWord ;
    int pageIndex ;
    const Candidate* candidate ;
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
    
    int getPreeditCodeLength() const ;
    
    int getInvalidCodeLength() const ;

    //int getSelectedLength() const ;

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

    bool appendCode( const QString& code ) ;

    bool popCode() ;

    void commit() ;

    bool setKeyboardLayout( KeyboardLayout layout ) ;

    bool setKeyboardLayout( int layout ) ;

} ;

}

#endif

