import Qt 4.7

Rectangle {
    id : key
    width : 160
    height : 80
    color : "#00000000"
    property alias keycode_l : key_l.keycode
    property alias keysym_l : key_l.keysym
    property alias keycode_r : key_r.keycode
    property alias keysym_r : key_r.keysym
    property string candString
    property bool isActive : false

    Row {
        Key {
            id : key_l
            width : key.width / 2
            height : key.height
        }
        Key {
            id : key_r
            width : key.width / 2
            height : key.height
            keepDown : key.isActive && key_l.down
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
