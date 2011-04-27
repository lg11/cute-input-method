import Qt 4.7
import Qt.labs.gestures 1.0

Rectangle {
    id : key
    width : 80
    height : 80
    color : "#00000000"
    property int keycode : 0
    property variant keysym : [ "", "", "", "" ]
    property int mask : keyboard.mask
    property bool isDown : false
    property bool isToggle : false

    Rectangle {
        id : plat
        anchors.centerIn: parent
        /*width : parent.width * 0.985*/
        /*height : parent.height - parent.width + width*/
        width : parent.width - 1
        height : parent.height - 1
        color : "#FF444444"

        Text {
            id : titleText
            text : keysym[mask]
            anchors.centerIn : parent
            color : "#FFFFFFFF"
            font.pointSize: 30; font.bold: true
        }
    }

    MouseArea {
        id : mouseArea
        focus : false
        anchors.fill : parent
        hoverEnabled : false
        onPressed : { keyboard.keyPress( keycode ) }
        onReleased : { keyboard.keyRelease( keycode ) }
    }

    states {
        State {
            name : "DOWN" ; when : ( mouseArea.pressed == true && mouseArea.containsMouse == true ) || isDown == true
            PropertyChanges { target : plat ; color : "#FF2299FF" }
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
            /*axis.x : 0 ; axis.y : 1 ; axis.z : 0*/
            /*angle : 0*/
        /*}*/
    /*}*/

    /*Behavior on mask {*/
        /*SequentialAnimation {*/
            /*ParallelAnimation {*/
                /*NumberAnimation { target: flip ; property: "angle" ; to: 180 ; duration: 100 }*/
                /*NumberAnimation { target: key ; property: "scale" ; to: 0.7 ; duration: 100 }*/
            /*}*/
            /*ParallelAnimation {*/
                /*NumberAnimation { target: flip ; property: "angle" ; to: 360 ; duration: 100 }*/
                /*NumberAnimation { target: key ; property: "scale" ; to: 1.0 ; duration: 100 }*/
            /*}*/
            /*NumberAnimation { target: flip ; property: "angle" ; to: 0 ; duration: 0 }*/
        /*}*/
    /*}*/
}
