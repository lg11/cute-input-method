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

enum Modifier { NoModifier = 0, CtrlModifier = 1, FnModifier = 2, ShiftModifier = 4 } ;
Q_DECLARE_FLAGS( Modifiers, Modifier )

class Handle : public QObject {
    Q_OBJECT 
signals :

public :
    host::Host* host ;
    engine::Engine* engine ;
    Modifiers modifiers ;
    int pressCount ;
#ifdef Q_WS_MAEMO_5
    //int fnPressCount ;
    //int shiftPressCount ;
    bool fnPressed ;
    bool shiftPressed ;
#endif

    Handle( host::Host* host, engine::Engine* engine, QObject* parent = NULL ) ;
    Q_INVOKABLE bool processKeyPress( int keycode ) ;
    Q_INVOKABLE bool processKeyRelease( int keycode ) ;
    Q_INVOKABLE void requestReset() ;
    Q_INVOKABLE void setKeyboardLayout( int layout ) ;
} ;

Q_DECLARE_OPERATORS_FOR_FLAGS( Modifiers )

} 


#endif
