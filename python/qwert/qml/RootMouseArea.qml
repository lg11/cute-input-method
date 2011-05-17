import Qt 4.7

FakeMouseArea {
    property Item mouseTarget : null

    function getMouseTarget( x, y ) {
        var pos = Qt.point( x, y )
        var target = childAt( pos.x, pos.y )
        var parent = null
        var flag = true
        if ( target ) {
            parent = target.parent
            while ( flag ) {
                /*console.log( target, target.takeMouse )*/
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
        /*console.log( target )*/
        return target
    }
    function switchMouseTarget( x, y ) {
        var target = getMouseTarget( x, y )
        if ( target != mouseTarget ) {
            if ( mouseTarget ) {
                var pos = mapToItem( mouseTarget, x, y )
                mouseTarget.containsMouse = false
                mouseTarget.mouseExited( pos.x, pos.y )
            }
            if ( target ) {
                var pos = mapToItem( target, x, y )
                target.containsMouse = true
                target.mouseEntered( pos.x, pos.y )
            }
            mouseTarget = target
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
        mouseTarget = null
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
