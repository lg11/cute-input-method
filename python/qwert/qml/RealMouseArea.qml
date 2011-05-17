import Qt 4.7

RootMouseArea {
    property bool useMouseTracker : false
    MouseArea {
        anchors.fill : parent
        onPressed : {
            parent.pressed = true
            if ( useMouseTracker ) {
                mouseTracker.reset()
                mouseTracker.push( mouse.x, mouse.y )
            }
            parent.mousePressed( mouse.x, mouse.y )
        }
        onReleased : {
            parent.pressed = false
            if ( useMouseTracker ) {
                mouseTracker.push( mouse.x, mouse.y )
                mouseTracker.end()
                parent.mouseReleased( mouseTracker.endX, mouseTracker.endY )
            }
            else
                parent.mouseReleased( mouse.x, mouse.y )
        }
        onPositionChanged : {
            parent.pressed = pressed
            if ( useMouseTracker ) {
                mouseTracker.push( mouse.x, mouse.y )
            }
            parent.mouseMoved( mouse.x, mouse.y )
        }
    }
}
