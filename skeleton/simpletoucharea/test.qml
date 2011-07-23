import Qt 4.7

Rectangle {
    width : 640
    height : 480
    color : "red"
    SimpleTouchArea {
        anchors.fill : parent
        Rectangle {
            width : 240
            height : 240
            color : "blue"
            MouseArea {
                anchors.fill : parent
            }
        }
    }
}
