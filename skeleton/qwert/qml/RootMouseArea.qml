import Qt 4.7

FakeMouseArea {
    property Item prevMouseTarget

    function getMouseTarget( x, y ) {
        var pos = Qt.point( x, y )
        var target = childAt( pos.x, pos.y )
        var parent = null
        var flag = true
        if ( target ) {
            parent = target.parent
            while ( flag ) {
                if ( target.takeMouse ) {
                    flag = false
                }
                else {
                    pos = target.mapFromItem( parent, pos.x, pos.y )
                    parent = target
                    target = parent.childAt( pos.x, pos.y )
                    if ( !target ) {
                        flag = false
                    }
                }
            }
        }
        return target
    }
    function switchMouseTarget( x, y ) {
        var target = getMouseTarget( x, y )
        if ( target != prevMouseTarget ) {
            if ( prevMouseTarget ) {
                var pos = mapToItem( target, x, y )
                prevMouseTarget.containsMouse = false
                prevMouseTarget.mouseExited( pos.x, pos.y )
            }
            if ( target ) {
                var pos = mapToItem( target, x, y )
                target.containsMouse = true
                target.mouseEntered( pos.x, pos.y )
            }
            prevMouseTarget = target
        }
        return target
    }

    onMousePressed : {
        var target = switchMouseTarget( x, y )
        if ( target ) {
            var pos = mapToItem( target, x, y )
            target.pressed = true
            target.mousePressed( pos.x, pos.y )
        }
    }
    onMouseReleased : {
        var target = switchMouseTarget( x, y )
        if ( target ) {
            var pos = mapToItem( target, x, y )
            target.pressed = false
            target.mouseReleased( pos.x, pos.y )
        }
    }
    onMouseMoved : {
        var target = switchMouseTarget( x, y )
        if ( target ) {
            var pos = mapToItem( target, x, y )
            target.pressed = pressed
            target.mouseMoved( pos.x, pos.y )
        }
    }
}
