import Qt 4.7

RealMouseArea {
    width : 800
    height : 480

    Config {
        id : config
    }
    Rectangle {
        anchors.fill : parent
        color : "#FFFFFFFF"
    }
    TextView {
        id : textview
        width : 720
        height : 75
        x : 40
        y : 0
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
        width : 65
        height : 100
        /*text : "t"*/
    }
    function setText( text ) {
        textview.set( text )
    }
    function getText() {
        return textview.get()
    }
    Component.onCompleted : {
        tooltip.proxyTarget = keyboard
    }
}
