import Qt 4.7

FakeMouseArea {
    id : proxy
    property Item target : null
    property alias proxyTarget : proxy.target
    /*onMouseEntered : {*/
        /*if ( target ) {*/
            /*if ( target.takeMouse ) {*/
                /*var pos = mapToItem( target, x, y )*/
                /*target.containsMouse = true*/
                /*target.mouseEntered( pos.x, pos.y )*/
            /*}*/
        /*}*/
    /*}*/
    /*onMouseExited : {*/
        /*if ( target ) {*/
            /*if ( target.takeMouse ) {*/
                /*var pos = mapToItem( target, x, y )*/
                /*target.containsMouse = false*/
                /*target.mouseExited( pos.x, pos.y )*/
            /*}*/
        /*}*/
    /*}*/
    /*onMousePressed : {*/
        /*if ( target ) {*/
            /*if ( target.takeMouse ) {*/
                /*var pos = mapToItem( target, x, y )*/
                /*target.pressed = true*/
                /*target.mousePressed( pos.x, pos.y )*/
            /*}*/
        /*}*/
    /*}*/
    /*onMouseReleased : {*/
        /*if ( target ) {*/
            /*if ( target.takeMouse ) {*/
                /*var pos = mapToItem( target, x, y )*/
                /*target.pressed = false*/
                /*target.mouseReleased( pos.x, pos.y )*/
            /*}*/
        /*}*/
    /*}*/
    /*onMouseMoved : {*/
        /*if ( target ) {*/
            /*if ( target.takeMouse ) {*/
                /*var pos = mapToItem( target, x, y )*/
                /*target.pressed = pressed*/
                /*target.mouseMoved( pos.x, pos.y )*/
            /*}*/
        /*}*/
    /*}*/
}
