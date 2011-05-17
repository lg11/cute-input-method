import Qt 4.7

Item {
    id : part
    property bool switchFlag : false
    property int sideSpacing : 50
    property alias view : textview

    Row {
        FakeMouseArea {
            width : sideSpacing
            height : part.height
            onMousePressed : switchFlag = true 
            onMouseReleased : {
                if ( switchFlag ) 
                    keyboard.switchMode()
            }
            onMouseExited : switchFlag = false
        }
        Item {
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
        }
        ProxyMouseArea {
            width : sideSpacing
            height : part.height
            target : keyboard.backspaceKey
        }
    }
}
