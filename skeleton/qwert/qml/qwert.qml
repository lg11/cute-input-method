import Qt 4.7

Rectangle {
    width : 800
    height : 480
    color : "#FFFFFFFF"

    TextView {
        id : textview
        width : 720
        height : 75
        x : 40
        y : 0
    }
    Preedit {
        id : preedit
        y : 15
        anchors.horizontalCenter : parent.horizontalCenter
        /*preeditString : imEngine.preeditString*/
    }
    Keyboard {
        width : parent.width * 1.15
        height : width * 0.7
        x : -25
        y : 75
    }
}
