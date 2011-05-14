import Qt 4.7

RootMouseArea {
    MouseArea {
        anchors.fill : parent
        onPressed : {
            mouseTracker.reset()
            mouseTracker.push( mouse.x, mouse.y )
            parent.pressed = true
            parent.mousePressed( mouse.x, mouse.y )
        }
        onReleased : {
            mouseTracker.push( mouse.x, mouse.y )
            mouseTracker.end()
            parent.pressed = false
            parent.mouseReleased( mouseTracker.endX, mouseTracker.endY )
        }
        onPositionChanged : {
            mouseTracker.push( mouse.x, mouse.y )
            parent.pressed = pressed
            parent.mouseMoved( mouse.x, mouse.y )
        }
    }
}
