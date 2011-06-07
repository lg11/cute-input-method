#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QList>
#include <QString>
#include <QStringList>
#include <QSet>
#include <QFile>
#include <QTextStream>
#include <QDir>

//#include <unistd.h>

#include "../lookup/lookup.h"
#include "../lookup/t9.h"

//#include <QDebug>

namespace engine {

typedef QPair<QString, QString> KeyPair ;
typedef QPair<QChar, qreal> WordPair ;
typedef QPair<KeyPair, WordPair> SelectedPair ;

//typedef QPair<QStringList, QStringList> KeyPair ;
//typedef QPair< QString, QList<qreal> > WordPair ;

class Engine : public QObject {
    Q_OBJECT
signals :
    void sendCommit( const QString& text ) ;
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

    inline Engine( QObject* parent = NULL ) : QObject( parent ), lookup(), t9lookup(&(lookup.dict)), selected(), selectedWord() {
        this->pageIndex = 0 ;
        this->candidate = NULL ;
        this->keyboardLayout = UnknownKeyboardLayout ;
        this->logFile = NULL ;
        this->textStream = NULL ;
    }

    inline ~Engine() {
        if ( this->logFile ) {
            delete this->textStream ;
            this->logFile->close() ;
            delete this->logFile ;
        }
    }

    Q_INVOKABLE inline void startLog( const QString& path ) {
        QString p( QDir::homePath() ) ;
        p.append( path.right( path.length() - 1 ) ) ;
        this->logFile = new QFile( p ) ;
        if ( this->logFile->exists() ) {
            this->logFile->open( QIODevice::WriteOnly | QIODevice::Append ) ;
            //this->logFile->open( QIODevice::WriteOnly | QIODevice::Append | QIODevice::Unbuffered ) ;
            this->textStream = new QTextStream( this->logFile ) ;
            this->textStream->setCodec( "utf-8" ) ;
            this->textStream->setRealNumberNotation( QTextStream::SmartNotation ) ;
            this->textStream->setRealNumberPrecision( 16 ) ;
        }
        else {
            delete this->logFile ;
            this->logFile = NULL ;
        }
    }

    Q_INVOKABLE inline void stopLog() {
        if ( this->logFile ) {
            delete this->textStream ;
            this->logFile->close() ;
            delete this->logFile ;
            this->logFile = NULL ;
            this->textStream = NULL ;
        }
    }

    Q_INVOKABLE inline void flushLog() {
        if ( this->logFile ) {
            this->logFile->flush() ;
            //this->logFile->close() ;
            //this->logFile->open( QIODevice::WriteOnly | QIODevice::Append ) ;
            //fsync( this->logFile->handle() ) ;
        }
    }
    
    Q_INVOKABLE inline void load( const QString& path ) {
        QString p ;
        if ( path.at(0) == QChar( '~' ) ) {
            p.append( QDir::homePath() ) ;
            p.append( path.right( path.length() - 1 ) ) ;
        }
        else
            p.append( path ) ;
        QFile file( p ) ;
        if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
            QSet<QString> newKeySet ;
            QTextStream in( &file ) ;
            in.setCodec( "utf-8" ) ;
            while( !in.atEnd() ) {
                QString line = in.readLine() ;
                QStringList list = line.split( " " ) ;
                if ( list.length() == 3 ) {
                    QString key = list.at(0) ;
                    QString word = list.at(1) ;
                    qreal freq = list.at(2).toDouble() ;
                    //qDebug() << key << word << freq ;
                    if ( !this->lookup.dict.hash.contains( key ) )
                        newKeySet.insert( key ) ;
                    this->lookup.dict.insert( key, word, freq ) ;
                }
            }
            foreach( const QString& key, newKeySet ) {
                if ( key.count( '\'' ) <= 0 )
                    split::add_key( &(this->lookup.spliter.keySet), key ) ;
                fit::add_key( &(this->lookup.keyMap), key ) ;
                this->t9lookup.tree.addKey( key ) ;
            }
        }
    }
    
    Q_INVOKABLE inline void prevPage() {
        if ( this->pageIndex > 0 )
            this->pageIndex-- ;
    }
    
    Q_INVOKABLE inline void nextPage() {
        int pageIndex = this->pageIndex + 1 ;
        const lookup::Candidate* candidate ;
        if ( this->keyboardLayout == FullKeyboardLayout )
            candidate = this->lookup.getCand( pageIndex * 5 ) ;
        else if ( this->keyboardLayout == T9KeyboardLayout )
            candidate = this->t9lookup.getCand( pageIndex * 6 ) ;
        else
            candidate = NULL ;
        if ( candidate )
            this->pageIndex = pageIndex ;
    }
    
    Q_INVOKABLE inline int getCodeLength() const {
        if ( this->keyboardLayout == FullKeyboardLayout )
            return this->lookup.spliter.code.length() ;
        else if ( this->keyboardLayout == T9KeyboardLayout )
            return this->t9lookup.code.length() ;
        else
            return 0 ;
    }
    
    Q_INVOKABLE inline int getPreeditLength() const {
        if ( this->candidate ) {
            const QString* preedit = lookup::get_preedit( this->candidate ) ;
            return preedit->length() - preedit->count( '\'' ) ;
        }
        return 0 ;
    }
    
    Q_INVOKABLE inline int getInvalidCodeLength() const { return this->getCodeLength() - this->getPreeditLength() ; }

    Q_INVOKABLE inline int getSelectedLength() const { return this->selected.length() ; }

    Q_INVOKABLE inline int getSelectedWordLength() const { return this->selectedWord.length() ; }
   
    Q_INVOKABLE inline bool updateCandidate( int index ) {
        if ( this->keyboardLayout == FullKeyboardLayout ) {
            if ( this->lookup.spliter.code.isEmpty() )
                this->candidate = NULL ;
            else 
                this->candidate = this->lookup.getCand( pageIndex * 5 + index ) ;
        }
        else if ( this->keyboardLayout == T9KeyboardLayout ) {
            if ( this->t9lookup.code.isEmpty() )
                this->candidate = NULL ;
            else 
                this->candidate = this->t9lookup.getCand( pageIndex * 6 + index ) ;
        }
        return this->candidate ;
        //if ( this->candidate ) 
            //qDebug() << *(lookup::get_key( this->candidate )) << *(lookup::get_preedit( this->candidate )) << *(lookup::get_word( this->candidate )) << lookup::get_freq( this->candidate ) ;
    }
    

    Q_INVOKABLE inline QString getCode() const {
        if ( this->keyboardLayout == FullKeyboardLayout ) 
            return this->lookup.spliter.code ;
        else if ( this->keyboardLayout == T9KeyboardLayout ) 
            return this->t9lookup.code ;
        else
            return "" ;
    }
    
    Q_INVOKABLE inline QString getWord() const {
        if ( this->candidate ) 
            return *(lookup::get_word( this->candidate )) ;
        else 
            return "" ;
    }
    
    Q_INVOKABLE inline QString getPreeditCode() const {
        if ( this->candidate ) 
            return *(lookup::get_preedit( this->candidate )) ;
        else
            return "" ;
    }

    Q_INVOKABLE inline QString getInvalidCode() const {
        if ( this->keyboardLayout == FullKeyboardLayout ) {
            if ( this->lookup.spliter.code.isEmpty() )
                return "" ;
            else
                return this->lookup.spliter.code.right( this->getInvalidCodeLength() ) ;
        }
        else if ( this->keyboardLayout == T9KeyboardLayout ) {
            if ( this->t9lookup.code.isEmpty() )
                return "" ;
            else
                return this->t9lookup.code.right( this->getInvalidCodeLength() ) ;
        }
        else
            return "" ;
    }

    Q_INVOKABLE inline QString getSelectedWord() const { return this->selectedWord ; }

    Q_INVOKABLE inline bool checkCommit() {
        bool flag = false ;
        if ( !this->selectedWord.isEmpty() && this->getCodeLength() <= 0 ) {
            emit this->sendCommit( this->selectedWord ) ;
            this->commit() ;
            flag = true ;
        }
        return flag ;
    }

    Q_INVOKABLE inline bool select( int index ) {
        bool flag = false ;
        if ( this->getCodeLength() > 0 ) {
            if ( this->keyboardLayout == FullKeyboardLayout ) {
                index = this->pageIndex * 5 + index ;
                const lookup::Candidate* candidate = this->lookup.getCand( index ) ;

                if ( candidate ) {
                    qreal freq = -0x1000 ;
                    if ( this->selected.isEmpty() ) {
                        int halfIndex = ( candidate->second + index ) / 2 ;
                        if ( halfIndex < 2 ) 
                            halfIndex = 0 ;
                        const lookup::Candidate* candidate = this->lookup.getCand( halfIndex ) ;
                        freq = lookup::get_freq( candidate ) ;
                        if ( freq <= 0.1 ) 
                            freq = 1.1 ;
                        else 
                            freq += 1 ;
                    }
                    
                    const QString* word = lookup::get_word( candidate ) ;
                    if ( word->length() > 1 ) {
                        QStringList key = lookup::get_key( candidate )->split( '\'' ) ;
                        QStringList preedit = lookup::get_preedit( candidate )->split( '\'' ) ;
                        for ( int i = 0 ; i < word->length() ; i++ )
                            this->selected.append( SelectedPair( KeyPair( key.at(i), preedit.at(i) ), WordPair( word->at(i), -0x1000 ) ) ) ;
                    }
                    else {
                        const QString* key = lookup::get_key( candidate ) ;
                        const QString* preedit = lookup::get_preedit( candidate ) ;
                        this->selected.append( SelectedPair( KeyPair( *key, *preedit ), WordPair( word->at(0), -0x1000 ) ) ) ;
                    }
                    this->selectedWord.append( *word ) ;
                    this->selected.last().second.second = freq ;

                    this->candidate = candidate ;
                    if ( this->getInvalidCodeLength() > 0 ) {
                        QString code( this->getInvalidCode() ) ;
                        //qDebug() << "r" << code ; 
                        this->lookup.reset() ;
                        this->lookup.setCode( code ) ;
                        this->pageIndex = 0 ;
                    }
                    else {
                        this->lookup.reset() ;
                        this->pageIndex = 0 ;
                    }

                    flag = true ;
                }
                //else ;
            }
            else if ( this->keyboardLayout == T9KeyboardLayout ) {
                index = this->pageIndex * 6 + index ;
                const lookup::Candidate* candidate = this->t9lookup.getCand( index ) ;

                if ( candidate ) {
                    qreal freq = -0x1000 ;
                    if ( this->selected.isEmpty() ) {
                        int halfIndex = ( candidate->second + index ) / 2 ;
                        if ( halfIndex < 2 ) 
                            halfIndex = 0 ;
                        const lookup::Candidate* candidate = this->t9lookup.getCand( halfIndex ) ;
                        freq = lookup::get_freq( candidate ) ;
                        if ( freq <= 0.1 ) 
                            freq = 1.1 ;
                        else 
                            freq += 1 ;
                    }
                    
                    const QString* word = lookup::get_word( candidate ) ;
                    if ( word->length() > 1 ) {
                        QStringList key = lookup::get_key( candidate )->split( '\'' ) ;
                        QStringList preedit = lookup::get_preedit( candidate )->split( '\'' ) ;
                        for ( int i = 0 ; i < word->length() ; i++ )
                            this->selected.append( SelectedPair( KeyPair( key.at(i), preedit.at(i) ), WordPair( word->at(i), -0x1000 ) ) ) ;
                    }
                    else {
                        const QString* key = lookup::get_key( candidate ) ;
                        const QString* preedit = lookup::get_preedit( candidate ) ;
                        this->selected.append( SelectedPair( KeyPair( *key, *preedit ), WordPair( word->at(0), -0x1000 ) ) ) ;
                    }
                    this->selectedWord.append( *word ) ;
                    this->selected.last().second.second = freq ;

                    this->candidate = candidate ;
                    if ( this->getInvalidCodeLength() > 0 ) {
                        QString code( this->getInvalidCode() ) ;
                        //qDebug() << "r" << code ; 
                        this->t9lookup.reset() ;
                        this->t9lookup.setCode( code ) ;
                        this->pageIndex = 0 ;
                    }
                    else {
                        this->t9lookup.reset() ;
                        this->pageIndex = 0 ;
                    }
                    flag = true ;
                }
                //else ;
            }
        }
        return flag ;
    }
    Q_INVOKABLE inline bool deselect() {
        bool flag = false ;
        if ( !this->selected.isEmpty() ) {
            QString code = this->selected.last().first.second ;
            this->selected.removeLast() ;
            this->selectedWord.chop(1) ;

            if ( this->keyboardLayout == FullKeyboardLayout ) {
                code.append( this->lookup.spliter.code ) ;
                this->lookup.reset() ;
                this->lookup.setCode( code ) ;
                this->pageIndex = 0 ;
            }
            else if ( this->keyboardLayout == T9KeyboardLayout ) {
                for ( int i = 0 ; i < code.length() ; i++ ) 
                    code[i] = this->t9lookup.tree.trans[ code.at(i).toAscii() - 'a' ] ;
                code.append( this->t9lookup.code ) ;
                this->t9lookup.reset() ;
                this->t9lookup.setCode( code ) ;
                this->pageIndex = 0 ;
            }

            flag = true ;
        }
        return flag ;
    }
    Q_INVOKABLE inline void reset() {
        if ( this->keyboardLayout == FullKeyboardLayout ) 
            this->lookup.reset() ;
        else if ( this->keyboardLayout == T9KeyboardLayout ) 
            this->t9lookup.reset() ;
        this->selected.clear() ;
        this->selectedWord.clear() ;
        this->pageIndex = 0 ;
    }
    Q_INVOKABLE inline bool appendCode( QChar code ) {
        bool flag = false ;
        if ( this->keyboardLayout == FullKeyboardLayout ) {
            if ( code >= 'a' && code <= 'z' ) {
                this->lookup.appendCode( code ) ;
                this->pageIndex = 0 ;
                flag = true ;
            }
        }
        else if ( this->keyboardLayout == T9KeyboardLayout ) {
            if ( code >= '2' && code <= '9' ) {
                this->t9lookup.appendCode( code ) ;
                this->pageIndex = 0 ;
                flag = true ;
            }
        }
        return flag ;
    }
    Q_INVOKABLE inline bool processKey( int keycode ) {
        bool flag = false ;
        if ( keycode >= Qt::Key_A && keycode <= Qt::Key_Z ) {
            keycode = keycode + 'a' - Qt::Key_A  ;
            QChar code( keycode )  ;
            flag = this->appendCode( code ) ;
        }
        else if ( keycode == Qt::Key_Backspace ) {
            flag = this->deselect() ? true : this->popCode() ;
        }
        else if ( keycode == Qt::Key_Space ) {
            flag = this->select( 0 ) ;
            if ( flag )
                this->checkCommit() ;
        }
        else if ( keycode >= Qt::Key_1 && keycode <= Qt::Key_5 ) {
            keycode = keycode - Qt::Key_1 ;
            flag = this->select( keycode ) ;
            if ( flag )
                this->checkCommit() ;
        }
        else if ( keycode == Qt::Key_Return || keycode == Qt::Key_Enter ) {
            if ( this->getCodeLength() > 0 ) {
                emit this->sendCommit( this->getCode() ) ;
                this->reset() ;
                flag = true ;
            }
        }
        return flag ;
    }

    Q_INVOKABLE inline bool appendCode( const QString& code ) {
        return this->appendCode( code.at(0) ) ;
    }
    Q_INVOKABLE inline bool popCode() {
        bool flag = false ;
        if ( this->keyboardLayout == FullKeyboardLayout ) {
            if ( !this->lookup.spliter.code.isEmpty() ) {
                this->lookup.popCode() ;
                this->pageIndex = 0 ;
                flag = true ;
            }
        }
        else if ( this->keyboardLayout == T9KeyboardLayout ) {
            if ( !this->t9lookup.code.isEmpty() ) {
                this->t9lookup.popCode() ;
                this->pageIndex = 0 ;
                flag = true ;
            }
        }
        return flag ;
    }

    Q_INVOKABLE inline void commit() {
        if ( this->selectedWord.length() < 6 ) {
            QStringList key ;
            for ( int i = 0 ; i < this->selected.length() ; i++ )
                key.append( this->selected.at(i).first.first ) ;
            QString k = key.join( QChar( '\'' ) ) ;
            qreal freq = this->selected.last().second.second ;
            freq = this->lookup.dict.update( k, this->selectedWord, freq ) ;
            if ( k.count( '\'' ) <= 0 )
                split::add_key( &(this->lookup.spliter.keySet), k ) ;
            fit::add_key( &(this->lookup.keyMap), k ) ;
            this->t9lookup.tree.addKey( k ) ;
            if ( this->logFile ) {
                (*this->textStream) << k << QChar( ' ' ) << selectedWord << QChar( ' ' ) << freq << QChar( '\n' ) ;
                //this->flushLog() ;
            }
        }
        this->reset() ;
    }
    Q_INVOKABLE inline bool setKeyboardLayout( KeyboardLayout layout ) {
        if ( layout != this->keyboardLayout ) {
            this->reset() ;
            this->keyboardLayout = layout ;
            return true ;
        }
        else
            return false ;
    }

} ;

}

#endif

