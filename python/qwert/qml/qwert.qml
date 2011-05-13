import Qt 4.7

Item {
    id : all
    width : 800
    height : 480
    signal close
    property int stateFlag : 0

    Palette {
        id : palette
    }
    Image {
        id : backgroundImage
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
        id : shadowPart
        x : 0
        y : 0
        width : 800
        height : 480
        /*color : "#FF000000"*/
        gradient : Gradient {
            GradientStop { position : 0.0 ; color : "#66000000" }
            GradientStop { position : 0.25 ; color : "#00000000" }
            GradientStop { position : 0.6 ; color : "#00000000" }
            GradientStop { position : 1.0 ; color : "#CC000000" }
        }
    }
    RealMouseArea {
        anchors.fill : parent
        Item {
            id : textViewPart
            x : 0
            y : 0
            width : 800
            height : 135
            property bool needClose : false
            FakeMouseArea {
                x : 0
                y : 0
                width : parent.width
                height : parent.height - 20
                onMousePressed : {
                    parent.needClose = true
                }
                onMouseReleased : {
                    if ( parent.needClose ) {
                        closeTimer.start()
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
                    color : palette.backgroundColor
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
            y : 135
        }
    Tooltip {
        id : tooltip
        /*width : 65*/
        height : 100
        /*text : "t"*/
    }
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
    Component.onCompleted : {
        tooltip.proxyTarget = keyboard
    }
    Timer {
        id : closeTimer
        repeat : false
        interval : 300
        onTriggered : { close() }
    }
    states {
        State {
            name : "HIDE" ; when : stateFlag == 1
            PropertyChanges { target : textViewPart ; x : 1000 ; }
            PropertyChanges { target : keyboard ; y : 1200 ; }
            PropertyChanges { target : all ; opacity : 0.0 ; }
        } 
    }
    transitions {
        Transition {
            from : "" ; to : "HIDE" ; reversible : true
            ParallelAnimation {
                NumberAnimation { target : textViewPart ; properties : "x" ; duration : 200 }
                NumberAnimation { target : keyboard ; properties : "y" ; duration : 200 }
                NumberAnimation { target : all ; properties : "opacity" ; duration : 300 }
            }
        } 
    } 
}
