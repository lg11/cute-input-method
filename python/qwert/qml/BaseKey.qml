import Qt 4.7
/*import Qt.labs.gestures 1.0*/

FakeMouseArea {
    id : key
    property bool keepDown : false 

    Rectangle {
        id : plat
        x : 1 ; y : 1
        width : parent.width - 1
        height : parent.height - 1
        Text {
            id : title
            anchors.centerIn : parent
            color : palette.keyTextColor
            font.pointSize: 30; font.bold: true
        }
    }
    property alias text : title.text
    property alias titleVisible : title.visible
    property alias textColor : title.color
    property alias color : plat.color
    property alias platVisible : plat.visible

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
}
