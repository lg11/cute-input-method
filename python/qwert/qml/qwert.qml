import Qt 4.7

Item {
    id : all
    width : 800
    height : 424
    signal close
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
        source : "/home/user/MyDocs/.images/water1.jpg"
        fillMode : Image.PreserveAspectCrop
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
        Item {
            id : textViewPart
            x : 0
            y : 0
            width : 800
            height : 80
            property bool needClose : false
            FakeMouseArea {
                /*takeMouse : false*/
                x : 0
                y : 0
                width : parent.width
                /*height : parent.height - 20*/
                height : parent.height
                onMousePressed : {
                    parent.needClose = true
                }
                onMouseReleased : {
                    if ( parent.needClose ) {
                        /*closeTimer.start()*/
                        stateFlag = 1
                    }
                    parent.needClose = false
                }
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
            Preedit {
                id : preedit
                anchors.centerIn : parent
                /*anchors.horizontalCenter : parent.horizontalCenter*/
            }
        }
        Keyboard {
            id : keyboard
            width : parent.width * 1.15
            height : width * 0.7
            x : -30
            y : 80
        }
        ProxyMouseArea{
            /*y : 125*/
            /*x : 0*/
            width : 800
            height : 480
            target : keyboard
        }
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
    Timer {
        id : closeTimer
        repeat : false
        interval : 300
        onTriggered : { close() }
    }
    /*states {*/
        /*State {*/
            /*name : "HIDE" ; when : stateFlag == 1*/
            /*PropertyChanges { target : textViewPart ; x : 1000 ; }*/
            /*PropertyChanges { target : keyboard ; y : 1200 ; }*/
            /*PropertyChanges { target : all ; opacity : 0.0 ; }*/
        /*} */
    /*}*/
    /*transitions {*/
        /*Transition {*/
            /*from : "" ; to : "HIDE" ; reversible : true*/
            /*ParallelAnimation {*/
                /*NumberAnimation { target : textViewPart ; properties : "x" ; duration : 200 }*/
                /*NumberAnimation { target : keyboard ; properties : "y" ; duration : 200 }*/
                /*NumberAnimation { target : all ; properties : "opacity" ; duration : 300 }*/
            /*}*/
        /*} */
    /*} */
    Component.onCompleted : {
        /*tooltip.proxyTarget = keyboard*/
    }
}
