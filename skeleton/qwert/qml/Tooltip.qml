import Qt 4.7

Item {
    id : plat

    visible : false
    Rectangle {
        color : config.keyDownColor
        anchors.centerIn : parent
        anchors.verticalCenterOffset : parent.height * 0.3
        width : parent.width * 0.2
        height : width
        rotation : 45
    }
    Rectangle {
        anchors.horizontalCenter : parent.horizontalCenter
        color : config.keyDownColor
        width : parent.width
        height : parent.height * 0.8
        Text {
            id : title
            anchors.centerIn : parent
            color : config.keyTextColor
            font.pointSize: 36; font.bold: true
        }
    }
    property alias text : title.text

    ProxyMouseArea {
        id : mouseArea
        anchors.fill : parent
    }
    property alias proxyTarget : mouseArea.target

    states {
        State {
            name : "ACTIVE" ; when : text.length > 0
            PropertyChanges { target : plat ; visible : true }
        }
    }
}
