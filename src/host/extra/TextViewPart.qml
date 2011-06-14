import Qt 4.7

Item {
    id : part
    property bool switchFlag : false
    property int sideSpacing : 50
    property alias view : textview
    property alias rightProxyTarget : rightProxyArea.target
    property alias rightProxyOffset : rightProxyArea.x
    /*property alias onMouseReleased : middlePart.onMousePressed*/

    Row {
        FakeMouseArea {
            width : sideSpacing
            height : part.height
            onMousePressed : switchFlag = true 
            onMouseReleased : {
                if ( switchFlag && engine.getCodeLength() <= 0 ) {
                    if ( !( root.rotateFlag == 1 && root.t9Mode == true ) )
                        keyboard.switchMode()
                }
            }
            onMouseExited : switchFlag = false
        }
        FakeMouseArea {
            id : middlePart
            width : part.width - sideSpacing * 2
            height : part.height
            Rectangle {
                width : parent.width - 20
                height : parent.height - 10
                anchors.centerIn : parent
                color : palette.textviewBackgroundColor
                TextView {
                    id : textview
                    anchors.fill : parent
                }
            }
            onMouseReleased : {
                var pos = mapToItem( part, x, y )
                var padWidth = controlPadPart.keyWidth * 3
                var helfWidth = padWidth / 2
                var padX = pos.x - helfWidth
                if ( padX < 0 )
                    padX = 0
                else if ( padX + padWidth > part.width )
                    padX = part.width - padWidth
                controlPadPart.padX = padX
                controlPadPart.stateFlag = 1
            }
        }
    }
    ProxyMouseArea {
        id : rightProxyArea
        x : 550
        y : 0
        width : parent.width - x
        height : part.height
    }
}
