import Qt 4.7


Rectangle {
    width : 800
    height : 480
    color : "#00FF0000"

    property int keyWidth
    property int keyHeight

    keyWidth : 80
    keyHeight : 75

    Column {
        anchors.fill : parent
        Row {
            Key { width : keyWidth ; height : keyHeight ; id : key_1 ; title: "1" }
            Key { width : keyWidth ; height : keyHeight ; id : key_2 ; title: "2" }
            Key { width : keyWidth ; height : keyHeight ; id : key_3 ; title: "3" }
            Key { width : keyWidth ; height : keyHeight ; id : key_4 ; title: "4" }
            Key { width : keyWidth ; height : keyHeight ; id : key_5 ; title: "5" }
            Key { width : keyWidth ; height : keyHeight ; id : key_6 ; title: "6" }
            Key { width : keyWidth ; height : keyHeight ; id : key_7 ; title: "7" }
            Key { width : keyWidth ; height : keyHeight ; id : key_8 ; title: "8" }
            Key { width : keyWidth ; height : keyHeight ; id : key_9 ; title: "9" }
            Key { width : keyWidth ; height : keyHeight ; id : key_0 ; title: "0" }
            Key { width : keyWidth ; height : keyHeight ; id : key_delete ; title: "←" }
        }
    }
}
