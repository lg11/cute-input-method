import Qt 4.7
/*import Qt.labs.gestures 1.0*/
import "utils.js" as Utils

FakeMouseArea {
    id : key
    property int keycode : 0
    property variant keysym : [ "", "", "", "" ]
    property int mask : 0
    /*property int mode : keyboard.mode*/
    property bool keepDown : false 

    Rectangle {
        id : plat
        x : 1
        y : 1
        width : parent.width - 1
        height : parent.height - 1
        /*color : palette.keyNormalColor*/
        radius : config.keyRadius

        Text {
            id : title
            text : Utils.keysym[keyboard.mode][keycode][keyboard.mask]
            anchors.centerIn : parent
            color : palette.keyTextColor
            font.pointSize: 30; font.bold: true
        }
    }

    property alias text : title.text
    property alias color : plat.color
    property alias platVisible : plat.visible
    /*property bool showTooltip : true*/

    onMousePressed : { keyboard.keyPress( key ) }
    onMouseReleased : { keyboard.keyRelease( key ) }
    onMouseEntered : { keyboard.keyEnter( key ) }
    onMouseExited : { keyboard.keyExit( key ) }

    states {
        State {
            name : "DOWN" ; when : down || keepDown
            PropertyChanges { target : plat ; color : palette.keyDownColor }
        } 
    }

    transitions {
        Transition {
            from : "" ; to : "DOWN" ; reversible : true
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
