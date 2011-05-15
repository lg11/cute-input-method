import Qt 4.7

Item {
    id : key
    width : 160
    height : 80
    /*color : "#00000000"*/
    property alias keycode_l : key_l.keycode
    property alias keycode_r : key_r.keycode
    property string candString
    property bool isActive : false

    Key {
        id : key_l
        x : 0
        y : 0
        width : key.width / 2
        height : key.height
    }
    Key {
        id : key_r
        x : key.width / 2
        y : 0
        width : key.width / 2
        height : key.height
        keepDown : key.isActive && key_l.down
    }

    property alias color_l : key_l.color
    property alias color_r : key_r.color

    Rectangle {
        id : plat
        x : 1
        y : 1
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

    Row {
        ProxyMouseArea {
            target : key_l
            width : key.width / 2
            height : key.height
        }
        ProxyMouseArea {
            target : key_r
            width : key.width / 2
            height : key.height
        }
    }

    states {
        State {
            name : "CAND" ; when : candString != ""
            PropertyChanges { target : plat ; color : key_r.color }
            PropertyChanges { target : key ; isActive : true }
            PropertyChanges { target : key_l ; text : candString }
            PropertyChanges { target : key_r ; text : candString }
            PropertyChanges { target : key_l ; x : key.width / 4 }
            PropertyChanges { target : key_r ; x : key.width / 4 }
            PropertyChanges { target : key_l ; opacity : 0 }
            PropertyChanges { target : key_r ; opacity : 0 }
        } 
    }
}
