import Qt 4.7

Rectangle {
    id : key
    width : 160
    height : 80
    color : "#00000000"
    property int keycode_l : 0
    property variant keysym_l : [ "", "", "", "" ]
    property int keycode_r : 0
    property variant keysym_r : [ "", "", "", "" ]
    property string candString
    property bool isActive : false

    Row {
        Key {
            id : key_l
            width : key.width / 2
            height : key.height
            keycode : key.keycode_l
            keysym : key.keysym_l
        }
        Key {
            id : key_r
            width : key.width / 2
            height : key.height
            keycode : key.keycode_r
            keysym : key.keysym_r
            isDown : key.isActive && key_l.isPressed
        }
    }

    Rectangle {
        id : plat
        anchors.centerIn: parent
        width : parent.width - 1
        height : parent.height - 1
        color : "#00000000"
        Text {
            id : candText
            text : candString
            anchors.centerIn : parent
            color : "#FFFFFFFF"
            font.pointSize: 24; font.bold: false
        }
    }


    states {
        State {
            name : "CAND" ; when : candString != ""
            PropertyChanges { target : plat ; color : key_r.platColor }
            PropertyChanges { target : key ; isActive : true }
        } 
    }
}
