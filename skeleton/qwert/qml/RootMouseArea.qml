import Qt 4.7

MouseArea {
    property Item prevMouseTarget
    property int prevX
    property int prevY

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
            if ( target ) {
                var pos = mapToItem( target, x, y )
                target.mouseEntered( pos.x, pos.y )
                target.containsMouse = true
            }
            if ( prevMouseTarget ) {
                var pos = mapToItem( target, x, y )
                prevMouseTarget.mouseExited( pos.x, pos.y )
                prevMouseTarget.containsMouse = false
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
        prevX = mouse.x
        prevY = mouse.y
    }
    onReleased : {
        var target = switchMouseTarget( mouse.x, mouse.y )
        if ( target ) {
            var pos = mapToItem( target, mouse.x, mouse.y )
            target.pressed = false
            target.mouseReleased( pos.x, pos.y )
        }
        prevX = mouse.x
        prevY = mouse.y
    }
    function move( x, y ) {
        var target = switchMouseTarget( x, y )
        if ( target ) {
            var pos = mapToItem( target, x, y )
            target.pressed = pressed
            target.mouseMoved( x, y )
        }
    }
    function step( dx, dy ) {
        var d = dx * dx + dy * dy
        while ( d > 1024 ) {
            dx = dx / 2
            dy = dy / 2
            d = dx * dx + dy * dy
        }
        return Qt.point( dx, dy )
    }
    onPositionChanged : {
        var x = mouse.x
        var y = mouse.y
        var dx = prevX - x
        var dy = prevY - y
        var d = step( dx, dy )
        var stepX = d.x
        var stepY = d.y
        console.log( "start", x, y )
        /*console.log( "start", stepX, stepY )*/
        d = dx * dx + dy * dy
        while ( d > 1024 ) {
            x = x + stepX
            y = y + stepY
            move( x, y )
            console.log( "step", x, y )
            dx = prevX - x
            dy = prevY - y
            d = dx * dx + dy * dy
        }
        console.log( "end", x, y )
        /*console.log( "end", mouse.x, mouse.y )*/
        move( mouse.x, mouse.y )
        prevX = mouse.x
        prevY = mouse.y
    }
}
