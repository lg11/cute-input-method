import Qt 4.7

Rectangle {
    width : 800
    height : 480
    color : "#FFFFFFFF"

    TextView {
        width : 720
        height : 75
        x : 40
        y : 0
    }
    Keyboard {
        width : parent.width * 1.15
        height : width * 0.7
        x : -25
        y : 75
    }
}
