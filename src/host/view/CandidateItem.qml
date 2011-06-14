import Qt 4.7

Item {
    property alias text : id_item.text
    property alias font : id_item.font
    property alias color : id_item.color
    property int verticalMargin : font.pointSize / 4
    property int horizontalMargin : font.pointSize * 1.5
    width : id_item.text.length > 0 ? id_item.paintedWidth + horizontalMargin : 0
    height : id_item.text.length > 0 ? id_item.paintedHeight + verticalMargin : 0

    Text {
        anchors.centerIn : parent
        id : id_item
    }
}
