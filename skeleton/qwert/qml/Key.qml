import Qt 4.7
/*import Qt.labs.gestures 1.0*/

Rectangle {
    id : key
    width : 80
    height : 80
    color : "#00000000"
    property int keycode : 0
    property variant keysym : [ "", "", "", "" ]
    property int mask : keyboard.mask
    property alias down : mouseArea.down
    property bool keepDown : false 

    Rectangle {
        id : plat
        x : 1
        y : 1
        width : parent.width - 1
        height : parent.height - 1
        color : config.keyNormalColor

        Text {
            id : titleText
            text : keysym[mask]
            anchors.centerIn : parent
            color : config.keyTextColor
            font.pointSize: 30; font.bold: true
        }
    }

    property alias platColor : plat.color

    FakeMouseArea {
        id : mouseArea
        anchors.fill : parent
        onMousePressed : { keyboard.keyPress( keycode ) }
        onMouseReleased : { keyboard.keyRelease( keycode ) }
    }

    /*property alias isPressed : mouseArea.pressed*/

    states {
        State {
            name : "DOWN" ; when : down || keepDown
            PropertyChanges { target : plat ; color : config.keyDownColor }
        } 
    }

    transitions {
        Transition {
            from : "" ; to : "DOWN" ; reversible : false
            ParallelAnimation {
                ColorAnimation { target : plat ; duration : 128 }
            }
        } 
        Transition {
            from : "DOWN" ; to : "" ; reversible : false
            ParallelAnimation {
                ColorAnimation { target : plat ; duration : 192 }
            }
        } 
    }

    /*transform {*/
        /*Rotation {*/
            /*id : flip*/
            /*origin.x : width / 2*/
            /*origin.y : height / 2*/
            /*axis.x : 0 ; axis.y : 0 ; axis.z : 1*/
            /*angle : 0*/
        /*}*/
    /*}*/

    /*property int rDuration : 0*/
    
    /*onMaskChanged : {*/
        /*rDuration = 200 + Math.random() * 200*/
    /*}*/

    /*Behavior on mask {*/
        /*SequentialAnimation {*/
            /*ParallelAnimation {*/
                /*NumberAnimation { target: flip ; property: "angle" ; to: 180 ; duration: rDuration }*/
                /*NumberAnimation { target: key ; property: "scale" ; to: 0.7 ; duration: rDuration }*/
            /*}*/
            /*ParallelAnimation {*/
                /*NumberAnimation { target: flip ; property: "angle" ; to: 360 ; duration: rDuration }*/
                /*NumberAnimation { target: key ; property: "scale" ; to: 1.0 ; duration: rDuration }*/
            /*}*/
            /*NumberAnimation { target: flip ; property: "angle" ; to: 0 ; duration: 0 }*/
        /*}*/
    /*}*/
}
