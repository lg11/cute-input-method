import Qt 4.7
import "utils.js" as Utils

Item {
    id : all
    width : 800
    height : 424
    signal rotateSignal
    property int stateFlag : 0

    Palette {
        id : palette
    }
    Config {
        id : config
    }
    Rectangle {
        anchors.fill : parent
        color : palette.backgroundColor
    }
    Image {
        id : backgroundImage
        x : 0
        y : 0
        width : 800
        height : 480
        fillMode : Image.PreserveAspectCrop
        source : config.backgroundImagePath
        visible : config.backgroundImageVisible
        opacity : config.backgroundImageOpacity
    }
    /*Rectangle {*/
        /*id : shadowPart*/
        /*x : 0*/
        /*y : 0*/
        /*width : 800*/
        /*height : 480*/
        /*gradient : Gradient {*/
            /*GradientStop { position : 0.0 ; color : "#66000000" }*/
            /*GradientStop { position : 0.25 ; color : "#00000000" }*/
            /*GradientStop { position : 0.6 ; color : "#00000000" }*/
            /*GradientStop { position : 1.0 ; color : "#CC000000" }*/
        /*}*/
    /*}*/
    RealMouseArea {
        anchors.fill : parent
        Text {
            x : 6
            y : 6
            text : Utils.modeString[keyboard.mode]
            color : "#EEFFFFFF"
            font.pointSize: 26; font.bold: true
        }
        Text {
            x : 5
            y : 5
            text : Utils.modeString[keyboard.mode]
            color : "#EE666666"
            font.pointSize: 26; font.bold: true
        }
        Item {
            id : textViewPart
            x : 0
            y : 0
            width : 800
            height : 80
            property bool switchFlag : false
            FakeMouseArea {
                id : switchArea
                /*takeMouse : false*/
                x : 0
                y : 0
                width : parent.width
                height : parent.height
                onMousePressed : {
                    parent.switchFlag = true
                    /*rotateTimer.restart()*/
                    needRotate = false
                }
                onMouseReleased : {
                    if ( parent.switchFlag ) {
                        parent.switchFlag = false
                        if ( needRotate ) {
                            rotateSignal()
                        }
                        else {
                            keyboard.switchMode()
                        }
                    }
                    needRotate = false
                    rotateTimer.stop()
                }
            }
            ProxyMouseArea {
                x : parent.width / 2
                y : 0
                width : parent.width / 2
                height : parent.height
                target : keyboard.backspaceKey
            }
            Item {
                width : parent.width - 90
                height : parent.height
                anchors.centerIn : parent
                Rectangle {
                    width : parent.width - 60
                    height : parent.height - 10
                    anchors.centerIn : parent
                    color : palette.textviewBackgroundColor
                    TextView {
                        id : textview
                        width : parent.width - 4
                        height : parent.height - 4
                        anchors.centerIn : parent
                    }
                }
            }
        }
        Keyboard {
            id : keyboard
            width : parent.width * 1.15
            height : width * 0.7
            x : -30
            y : 80
        }
    }
    Preedit {
        id : preedit
        anchors.horizontalCenter : parent.horizontalCenter
        y : ( textview.height - height ) / 2
    }
    Tooltip {
        id : tooltip
        /*width : 65*/
        height : 100
        /*text : "t"*/
    }
    function setText( text ) {
        textview.set( text )
        stateFlag = 0
        imEngine.clear()
        keyboard.updateCandString()
    }
    function getText() {
        return textview.get()
    }
    property bool needRotate : false
    Timer {
        id : rotateTimer
        interval : 750
        repeat : false
        onTriggered : { needRotate = true }
    }
    Rectangle {
        x : 100
        y : 10
        color : palette.preeditBackgroundColor
        width : 85
        height : 85
        visible : needRotate
        Text {
            anchors.centerIn : parent
            color : "#FFFFFFFF"
            font.pointSize : 36 ; font.bold : true
            text : "R"
        }
    }
    Component.onCompleted : {
        /*tooltip.proxyTarget = keyboard*/
    }
}
