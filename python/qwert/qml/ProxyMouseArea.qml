import Qt 4.7

FakeMouseArea {
    property Item target : null
    onMouseEntered : {
        if ( target ) {
            if ( target.takeMouse ) {
                var pos = mapToItem( target, x, y )
                target.containsMouse = true
                target.mouseEntered( pos.x, pos.y )
            }
        }
    }
    onMouseExited : {
        if ( target ) {
            if ( target.takeMouse ) {
                var pos = mapToItem( target, x, y )
                target.containsMouse = false
                target.mouseExited( pos.x, pos.y )
            }
        }
    }
    onMousePressed : {
        if ( target ) {
            if ( target.takeMouse ) {
                var pos = mapToItem( target, x, y )
                target.pressed = true
                target.mousePressed( pos.x, pos.y )
            }
        }
    }
    onMouseReleased : {
        if ( target ) {
            if ( target.takeMouse ) {
                var pos = mapToItem( target, x, y )
                target.pressed = false
                target.mouseReleased( pos.x, pos.y )
            }
        }
    }
    onMouseMoved : {
        if ( target ) {
            if ( target.takeMouse ) {
                var pos = mapToItem( target, x, y )
                target.pressed = pressed
                target.mouseMoved( pos.x, pos.y )
            }
        }
    }
}
