#ifndef HANDLE_H
#define HANDLE_H

#include <QObject>

namespace engine {
class Engine ;
}
namespace host {
class Host ;
}

namespace handle {

//enum Modifiers { NoModifier = 1, CtrlModifier = 2, FnModifier = 4, ShiftModifier = 8 } ;

class Handle : public QObject {
    Q_OBJECT 
signals :

public :
    host::Host* host ;
    engine::Engine* engine ;
    //Modifiers modifiers ;
    int pressCount ;

    Handle( host::Host* host, engine::Engine* engine, QObject* parent = NULL ) ;
    Q_INVOKABLE bool processKeyPress( int keycode ) ;
    Q_INVOKABLE bool processKeyRelease( int keycode ) ;
    Q_INVOKABLE void requestReset() ;
    Q_INVOKABLE void setKeyboardLayout( int layout ) ;
} ;

} 


#endif
