import Qt 4.7

MouseArea {
    property Item prevMouseTarget
    /*property int prevX*/
    /*property int prevY*/

    function getMouseTarget( x, y ) {
        var pos = Qt.point( x, y )
        var target = childAt( pos.x, pos.y )
        var parent = null
        var flag = true
        if ( target ) {
            parent = target.parent
            while ( flag ) {
                if ( target.takeMouse ) {
                    /*if ( target.takeMouse == true ) {*/
                    flag = false
                    /*}*/
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

    onPressed : {
        var target = switchMouseTarget( mouse.x, mouse.y )
        if ( target ) {
            var pos = mapToItem( target, mouse.x, mouse.y )
            target.pressed = true
            target.mousePressed( pos.x, pos.y )
        }
        /*prevX = mouse.x*/
        /*prevY = mouse.y*/
    }
    onReleased : {
        var target = switchMouseTarget( mouse.x, mouse.y )
        if ( target ) {
            var pos = mapToItem( target, mouse.x, mouse.y )
            target.pressed = false
            target.mouseReleased( pos.x, pos.y )
        }
        /*prevX = mouse.x*/
        /*prevY = mouse.y*/
    }
    onPositionChanged : {
        var target = switchMouseTarget( mouse.x, mouse.y )
        if ( target ) {
            var pos = mapToItem( target, mouse.x, mouse.y )
            target.pressed = pressed
            target.mouseMoved( pos.x, pos.y )
        }
        /*prevX = mouse.x*/
        /*prevY = mouse.y*/
    }
}
