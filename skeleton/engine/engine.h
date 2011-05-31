#ifndef IMENGINE_H
#define IMENGINE_H

#include <QObject>
#include <QList>
#include <QString>
#include <QStringList>
#include <QSet>
#include <QFile>
#include <QTextStream>

#include "../lookup/lookup.h"
#include "../lookup/t9.h"

//#include <QDebug>

namespace engine {

typedef QPair<QString, QString> KeyPair ;
typedef QPair<QChar, qreal> WordPair ;
typedef QPair<KeyPair, WordPair> SelectedPair ;

//typedef QPair<QStringList, QStringList> KeyPair ;
//typedef QPair< QString, QList<qreal> > WordPair ;

class IMEngine : public QObject {
    Q_OBJECT
public:
    lookup::Lookup lookup ;
    t9::T9Lookup t9lookup ;
    QList<SelectedPair> selected ;
    QString selectedWord ;
    int pageIndex ;
    const lookup::Candidate* candidate ;
    int mode ;

    inline IMEngine( QObject* parent = NULL ) : QObject( parent ), lookup(), t9lookup(&(lookup.dict)), selected(), selectedWord() { this->pageIndex = 0 ; this->candidate = NULL ; mode = 0 ; }
    
    Q_INVOKABLE inline void load( const QString& path ) {
        QFile file( path ) ;
        if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
            QSet<QString> newKeySet ;
            QTextStream in( &file ) ;
            in.setCodec( "utf-8" ) ;
            while( !in.atEnd() ) {
                QString line = in.readLine() ;
                QStringList list = line.split( " " ) ;
                QString key = list.at(0) ;
                QString word = list.at(1) ;
                qreal freq = list.at(2).toFloat() ;
                //qDebug() << key << word << freq ;
                if ( !this->lookup.dict.hash.contains( key ) )
                    newKeySet.insert( key ) ;
                this->lookup.dict.insert( key, word, freq ) ;
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
        if ( this->mode == 0 )
            candidate = this->lookup.getCand( pageIndex * 5 ) ;
        else if ( this->mode == 1 )
            candidate = this->t9lookup.getCand( pageIndex * 6 ) ;
        else
            candidate = NULL ;
        if ( candidate )
            this->pageIndex = pageIndex ;
    }
    
    Q_INVOKABLE inline int getCodeLength() const {
        if ( this->mode == 0 )
            return this->lookup.spliter.code.length() ;
        else if ( this->mode == 1 )
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
    
    Q_INVOKABLE inline int getInvaildCodeLength() const { return this->getCodeLength() - this->getPreeditLength() ; }

    Q_INVOKABLE inline int getSelectedLength() const { return this->selected.length() ; }

    Q_INVOKABLE inline int getSelectedWordLength() const { return this->selectedWord.length() ; }
   
    Q_INVOKABLE inline void updateCandidate( int index ) {
        if ( this->mode == 0 ) {
            if ( this->lookup.spliter.code.isEmpty() )
                this->candidate = NULL ;
            else 
                this->candidate = this->lookup.getCand( pageIndex * 5 + index ) ;
        }
        else if ( this->mode == 1 ) {
            if ( this->t9lookup.code.isEmpty() )
                this->candidate = NULL ;
            else 
                this->candidate = this->t9lookup.getCand( pageIndex * 6 + index ) ;
        }
        //if ( this->candidate ) 
            //qDebug() << *(lookup::get_key( this->candidate )) << *(lookup::get_preedit( this->candidate )) << *(lookup::get_word( this->candidate )) << lookup::get_freq( this->candidate ) ;
    }
    

    Q_INVOKABLE inline QString getCode() const {
        if ( this->mode == 0 ) 
            return this->lookup.spliter.code ;
        else if ( this->mode == 1 ) 
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
    
    Q_INVOKABLE inline QString getPreedit() const {
        if ( this->candidate ) 
            return *(lookup::get_preedit( this->candidate )) ;
        else
            return "" ;
    }

    Q_INVOKABLE inline QString getInvaildCode() const {
        if ( this->mode == 0 ) {
            if ( this->lookup.spliter.code.isEmpty() )
                return "" ;
            else
                return this->lookup.spliter.code.right( this->getInvaildCodeLength() ) ;
        }
        else if ( this->mode == 1 ) {
            if ( this->t9lookup.code.isEmpty() )
                return "" ;
            else
                return this->t9lookup.code.right( this->getInvaildCodeLength() ) ;
        }
        else
            return "" ;
    }

    Q_INVOKABLE inline QString getSelectedWord() const { return this->selectedWord ; }

    Q_INVOKABLE inline void select( int index ) {
        if ( this->mode == 0 ) {
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
                    if ( freq <= 1.1 ) 
                        freq = 1.1 ;
                    else 
                        freq += 1.0 / freq + 1 ;
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
                if ( this->getInvaildCodeLength() > 0 ) {
                    QString code( this->getInvaildCode() ) ;
                    //qDebug() << "r" << code ; 
                    this->lookup.reset() ;
                    this->lookup.setCode( code ) ;
                    this->pageIndex = 0 ;
                }
                else {
                    this->lookup.reset() ;
                    this->pageIndex = 0 ;
                }
            }
            //else ;
        }
        else if ( this->mode == 1 ) {
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
                    if ( freq <= 1.1 ) 
                        freq = 1.1 ;
                    else 
                        freq += 1.0 / freq + 1 ;
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
                if ( this->getInvaildCodeLength() > 0 ) {
                    QString code( this->getInvaildCode() ) ;
                    //qDebug() << "r" << code ; 
                    this->t9lookup.reset() ;
                    this->t9lookup.setCode( code ) ;
                    this->pageIndex = 0 ;
                }
                else {
                    this->t9lookup.reset() ;
                    this->pageIndex = 0 ;
                }
            }
            //else ;
        }
    }
    Q_INVOKABLE inline void cancel() {
        if ( !this->selected.isEmpty() ) {
            QString code = this->selected.last().first.second ;
            this->selected.removeLast() ;
            this->selectedWord.chop(1) ;

            if ( this-> mode == 0 ) {
                code.append( this->lookup.spliter.code ) ;
                this->lookup.reset() ;
                this->lookup.setCode( code ) ;
                this->pageIndex = 0 ;
            }
            else if ( this-> mode == 1 ) {
                for ( int i = 0 ; i < code.length() ; i++ ) 
                    code[i] = this->t9lookup.tree.trans[ code.at(i).toAscii() - 'a' ] ;
                code.append( this->t9lookup.code ) ;
                this->t9lookup.reset() ;
                this->t9lookup.setCode( code ) ;
                this->pageIndex = 0 ;
            }
        }
    }
    Q_INVOKABLE inline void reset() {
        if ( this-> mode == 0 ) 
            this->lookup.reset() ;
        else if ( this-> mode == 1 ) 
            this->t9lookup.reset() ;
        this->selected.clear() ;
        this->selectedWord.clear() ;
        this->pageIndex = 0 ;
    }
    Q_INVOKABLE inline void appendCode( const QString& code ) {
        if ( this-> mode == 0 ) 
            this->lookup.appendCode( code.at(0) ) ;
        else if ( this-> mode == 1 ) 
            this->t9lookup.appendCode( code.at(0) ) ;
        this->pageIndex = 0 ;
    }
    Q_INVOKABLE inline void popCode() {
        if ( this-> mode == 0 ) 
            this->lookup.popCode() ;
        else if ( this-> mode == 1 ) 
            this->t9lookup.popCode() ;
        this->pageIndex = 0 ;
    }
    Q_INVOKABLE inline void commit() {
        if ( !this->selected.isEmpty() ) {
            QStringList key ;
            for ( int i = 0 ; i < this->selected.length() ; i++ )
                key.append( this->selected.at(i).first.first ) ;
            QString k = key.join( QChar( '\'' ) ) ;
            qreal freq = this->selected.last().second.second ;
            this->lookup.dict.update( k, this->selectedWord, freq ) ;
            if ( k.count( '\'' ) <= 0 )
                split::add_key( &(this->lookup.spliter.keySet), k ) ;
            fit::add_key( &(this->lookup.keyMap), k ) ;
            this->t9lookup.tree.addKey( k ) ;
            this->reset() ;
        }
    }
    Q_INVOKABLE inline void setMode( int flag ) {
        if ( flag != this->mode ) {
            this->reset() ;
            this->mode = flag ;
        }
    }

} ;

}

#endif

