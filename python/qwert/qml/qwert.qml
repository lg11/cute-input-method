import Qt 4.7

RealMouseArea {
    width : 800
    height : 480

    Palette {
        id : palette
    }
    Image {
        /*anchors.fill : parent*/
        x : 0
        y : 0
        width : 800
        height : 480
        source : "/home/user/MyDocs/.images/water1.jpg"
        /*fillMode : Image.PreserveAspectFit*/
        fillMode : Image.PreserveAspectCrop
    }
    Rectangle {
        anchors.fill : parent
        color : "#00FFFFFF"
    }
    Rectangle {
        width : 720
        height : 65
        x : 40
        y : 5
        color : palette.backgroundColor
        TextView {
            id : textview
            x : 2
            y : 2
            width : parent.width - 4
            height : parent.height - 4
        }
    }
    Preedit {
        id : preedit
        y : 10
        anchors.horizontalCenter : parent.horizontalCenter
        /*preeditString : imEngine.preeditString*/
    }
    Keyboard {
        id : keyboard
        width : parent.width * 1.15
        height : width * 0.7
        x : -25
        y : 75
    }
    Tooltip {
        id : tooltip
        /*width : 65*/
        height : 100
        /*text : "t"*/
    }
    function setText( text ) {
        textview.set( text )
        imEngine.clear()
        keyboard.updateCandString()
    }
    function getText() {
        return textview.get()
    }
    Component.onCompleted : {
        tooltip.proxyTarget = keyboard
    }
}
