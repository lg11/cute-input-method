#ifndef HANDLE_H
#define HANDLE_H

#include <QObject>

namespace engine {
class Engine ;
}

namespace handle {

//enum Modifiers { NoModifier = 1, CtrlModifier = 2, FnModifier = 4, ShiftModifier = 8 } ;

class Handle : public QObject {
    Q_OBJECT 
signals :
    void sendStatus( int status ) ;

public :
    engine::Engine* engine ;
    //Modifiers modifiers ;
    int pressCount ;
    bool flag ;

    Handle( engine::Engine* engine, QObject* parent = NULL ) ;
    Q_INVOKABLE bool processKeyPress( int keycode ) ;
    Q_INVOKABLE bool processKeyRelease( int keycode ) ;
    Q_INVOKABLE bool setKeyboardLayout( int layout ) ;
    Q_SLOT void queryStatus() ;
} ;

} 


#endif
