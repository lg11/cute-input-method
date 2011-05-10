import Qt 4.7

Rectangle {
    width : 480
    height : 800
    color : "#FFFFFFFF"

    Rectangle {
        width : 450
        height : 130
        color : "#FFEEEEEE"
        x : 15
        y : 10
        TextEdit {
            id : textview
            anchors.fill : parent
        }
    }
    
    NumPad {
        width : parent.width * 1.15
        height : width * 0.7
        x : 20
        y : 150
    }
}
