import Qt 4.7

Item {
    property alias text : item.text
    width : item.text.length > 0 ? item.paintedWidth + 10 : 0
    height : item.text.length > 0 ? item.paintedHeight + 10 : 0

    Text {
        anchors.centerIn : parent
        id : item
    }

}
