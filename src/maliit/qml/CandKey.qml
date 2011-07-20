import QtQuick 1.1
import com.meego 1.0

Item {
    id : key
    width : 160
    height : 80
    /*color : "#00000000"*/
    property alias keycode_l : key_l.keycode
    property alias keycode_r : key_r.keycode
    property alias candString : candButton.text
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

    Button {
        id : candButton
        x : 2
        y : 2
        width : parent.width - 4
        height : parent.height - 4
        /*anchors.fill :parent*/
        checked : key_l.checked || key_r.checked
        visible : false
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
            PropertyChanges { target : key ; isActive : true }
            PropertyChanges { target : key_l ; text : candString }
            PropertyChanges { target : key_r ; text : candString }
            PropertyChanges { target : key_l ; x : key.width / 4 }
            PropertyChanges { target : key_r ; x : key.width / 4 }
            PropertyChanges { target : key_l ; visible : false }
            PropertyChanges { target : key_r ; visible : false }
            PropertyChanges { target : candButton ; visible : true }
        } 
    }
}
