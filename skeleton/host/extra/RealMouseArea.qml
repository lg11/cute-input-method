import Qt 4.7

RootMouseArea {
    /*property bool useMouseTracker : false*/
    MouseTrack {
        id : mouseTracker
    }
    MouseArea {
        anchors.fill : parent
        onPressed : {
            parent.pressed = true
            mouseTracker.reset()
            mouseTracker.push( mouse.x, mouse.y )
            parent.mousePressed( mouse.x, mouse.y )
        }
        onReleased : {
            parent.pressed = false
            mouseTracker.push( mouse.x, mouse.y )
            mouseTracker.stop()
            var pos = mouseTracker.get() 
            parent.mouseReleased( pos.x, pos.y )
            /*console.log( "release", pos.x, pos.y )*/
        }
        onPositionChanged : {
            parent.pressed = pressed
            mouseTracker.push( mouse.x, mouse.y )
            parent.mouseMoved( mouse.x, mouse.y )
        }
    }
}
