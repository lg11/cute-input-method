#ifndef IMENGINE_H
#define IMENGINE_H

#include <QObject>
#include <QSet>
#include <QFile>
#include <QTextStream>

#include "../lookup/lookup.h"

class IMEngine : public QObject {
    Q_OBJECT
public:
    lookup::Lookup lookup ;
    const lookup::Candidate* candidate ;
    int pageIndex ;

    inline IMEngine( QObject* parent = NULL ) : QObject( parent ), lookup() { this->pageIndex = 0 ; this->candidate = NULL ; }
    
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
   
    Q_INVOKABLE inline void updateCandidate( int index ) {
        this->candidate = this->lookup.getCand( pageIndex * 5 + index ) ;
    }
    
    Q_INVOKABLE inline QString getCode() const { return this->lookup.spliter.code ; }
    
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
        if ( this->candidate )
            return this->lookup.spliter.code.right( this->getInvaildCodeLength() ) ;
        else
            return "" ;
    }
    Q_INVOKABLE inline void select( int index ) {
        //candIndex = self.pageIndex * self.pageLength + index
        //cand = self.lookup[self.mode].getCand( candIndex )
        //invaildCode = self.getInvaildCode( index )
        //if cand :
            //#print candIndex
            //key, word, freq, preeditString, candStartIndex = cand 
            //#print key, word, freq, preeditString, candStartIndex
            //freqArg = -1
            //if len( self.selected ) <= 0 :
                //halfIndex = ( candStartIndex + candIndex ) / 2
                //halfCand = self.lookup[self.mode].getCand( halfIndex )
                //halfKey, halfWord, halfFreq, halfPreeditString, halfCandStartIndex = halfCand
                //#print halfKey, halfWord, halfFreq, halfPreeditString, halfCandStartIndex
                //freqArg = halfFreq + 1
            //keys = key.split( "'" )
            //preeditStrings = preeditString.split( "'" )
            //for i in range( len( word ) ) :
                //self.selected.append( [ keys[i], word[i], -1, preeditStrings[i] ] )
            //self.selectedWord += word
            //self.selected[-1][2] = freqArg
            //#print self.selected
            //self.lookup[self.mode].clear()
            //self.pageIndex = 0
            //if len( invaildCode ) > 0 :
                //for c in invaildCode :
                    //self.lookup[self.mode].append( c )
        //else :
            //pass
    }
} ;

#endif

