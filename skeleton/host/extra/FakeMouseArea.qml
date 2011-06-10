import Qt 4.7

Item {
    signal mouseEntered ( int x, int y )
    signal mouseExited ( int x, int y )
    signal mousePressed ( int x, int y )
    signal mouseReleased ( int x, int y )
    signal mouseMoved ( int x, int y )
    property bool takeMouse : true
    property bool containsMouse : false
    property bool pressed : false
    property bool down : containsMouse && pressed

    /*onEntered : {*/
        /*console.log( "entered", pressed )*/
    /*}*/
    /*onExited : {*/
        /*console.log( "exited", pressed )*/
    /*}*/
}
