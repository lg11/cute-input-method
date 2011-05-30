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
    QList<SelectedPair> selected ;
    QString selectedWord ;
    int pageIndex ;
    const lookup::Candidate* candidate ;

    inline IMEngine( QObject* parent = NULL ) : QObject( parent ), lookup(), selected(), selectedWord() { this->pageIndex = 0 ; this->candidate = NULL ; }
    
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
                if ( key.count( "'" ) <= 0 )
                    split::add_key( &(this->lookup.spliter.keySet), key ) ;
                fit::add_key( &(this->lookup.keyMap), key ) ;

            }
        }
    }
    
    Q_INVOKABLE inline void prevPage() {
        if ( this->pageIndex > 0 )
            this->pageIndex-- ;
    }
    
    Q_INVOKABLE inline void nextPage() {
        int pageIndex = this->pageIndex + 1 ;
        const lookup::Candidate* candidate = this->lookup.getCand( pageIndex * 5 ) ;
        if ( candidate )
            this->pageIndex = pageIndex ;
    }
    
    Q_INVOKABLE inline int getCodeLength() const { return this->lookup.spliter.code.length() ; }
    
    Q_INVOKABLE inline int getPreeditLength() const {
        if ( this->candidate ) {
            const QString* preedit = lookup::get_preedit( this->candidate ) ;
            return preedit->length() - preedit->count( "'" ) ;
        }
        return 0 ;
    }
    
    Q_INVOKABLE inline int getInvaildCodeLength() const { return this->getCodeLength() - this->getPreeditLength() ; }

    Q_INVOKABLE inline int getSelectedLength() const { return this->selected.length() ; }

    Q_INVOKABLE inline int getSelectedWordLength() const { return this->selectedWord.length() ; }
   
    Q_INVOKABLE inline void updateCandidate( int index ) {
        if ( this->lookup.spliter.code.isEmpty() )
            this->candidate = NULL ;
        else 
            this->candidate = this->lookup.getCand( pageIndex * 5 + index ) ;
    }
    

    Q_INVOKABLE inline QString getCode() const { return this->lookup.spliter.code ; }
    
    Q_INVOKABLE inline QString getWord() const {
        if ( this->candidate ) {
            //qDebug() << "check" << lookup::get_word( this->candidate ) ;
            return *(lookup::get_word( this->candidate )) ;
        }
        else {
            //qDebug() << "check no" ;
            return "" ;
        }
    }
    
    Q_INVOKABLE inline QString getPreedit() const {
        if ( this->candidate ) {
            //qDebug() << this->candidate ;
            return *(lookup::get_preedit( this->candidate )) ;
        }
        else
            return "" ;
    }

    Q_INVOKABLE inline QString getInvaildCode() const {
        if ( this->lookup.spliter.code.isEmpty() )
            return "" ;
        else
            return this->lookup.spliter.code.right( this->getInvaildCodeLength() ) ;
    }

    Q_INVOKABLE inline QString getSelectedWord() const { return this->selectedWord ; }

    Q_INVOKABLE inline void select( int index ) {
        index = this->pageIndex * 5 + index ;
        const lookup::Candidate* candidate = this->lookup.getCand( index ) ;

        if ( candidate ) {
            qreal freq = -0x1000 ;
            if ( this->selected.isEmpty() ) {
                int halfIndex = ( candidate->second + index ) / 2 ;
                const lookup::Candidate* candidate = this->lookup.getCand( halfIndex ) ;
                freq = lookup::get_freq( candidate ) ;
            }
            
            const QString* word = lookup::get_word( candidate ) ;
            if ( word->length() > 1 ) {
                QStringList key = lookup::get_key( candidate )->split( "'" ) ;
                QStringList preedit = lookup::get_preedit( candidate )->split( "'" ) ;
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
    Q_INVOKABLE inline void cancel() {
        if ( !this->selected.isEmpty() ) {
            QString code = this->selected.last().first.second ;
            this->selected.removeLast() ;
            this->selectedWord.chop(1) ;

            code.append( this->lookup.spliter.code ) ;
            this->lookup.reset() ;
            this->lookup.setCode( code ) ;
            this->pageIndex = 0 ;
        }
    }
    Q_INVOKABLE inline void reset() {
        this->lookup.reset() ;
        this->selected.clear() ;
        this->selectedWord.clear() ;
        this->pageIndex = 0 ;
    }
    Q_INVOKABLE inline void appendCode( const QString& code ) {
        this->lookup.appendCode( code.at(0) ) ;
        this->pageIndex = 0 ;
    }
    Q_INVOKABLE inline void popCode() {
        this->lookup.popCode() ;
        this->pageIndex = 0 ;
    }
    Q_INVOKABLE inline void commit() {
        if ( !this->selected.isEmpty() ) {
            QStringList key ;
            for ( int i = 0 ; i < this->selected.length() ; i++ )
                key.append( this->selected.at(i).first.first ) ;
            QString k = key.join( "'" ) ;
            //qreal freq = this->selected.last().second.second ;
            //this->lookup.update( k, this->selectedWord, freq ) ;
            this->reset() ;
        }
    }
    Q_INVOKABLE inline void setMode( int index ) {
    }

} ;

}

#endif

