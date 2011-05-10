import Qt 4.7

RootMouseArea {
    MouseArea {
        anchors.fill : parent
        onPressed : {
            parent.pressed = true
            parent.mousePressed( mouse.x, mouse.y )
        }
        onReleased : {
            parent.pressed = false
            parent.mouseReleased( mouse.x, mouse.y )
        }
        onPositionChanged : {
            parent.pressed = pressed
            parent.mouseMoved( mouse.x, mouse.y )
        }
    }
}
