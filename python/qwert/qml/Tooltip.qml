import Qt 4.7

Item {
    id : plat
    width : title.paintedWidth > 75 ? Math.ceil( title.paintedWidth / 25 ) * 25 : 75

    visible : false
    Rectangle {
        id : platBackground
        anchors.horizontalCenter : parent.horizontalCenter
        color : palette.backgroundColor
        width : parent.width
        height : parent.height * 0.8
    }
    Rectangle {
        color : palette.backgroundColor
        anchors.centerIn : parent
        anchors.verticalCenterOffset : parent.height * 0.3
        width : parent.height * 0.15
        height : width
        rotation : 45
        Rectangle {
            color : palette.keyDownColor
            anchors.centerIn : parent
            width : parent.width - 2
            height : parent.height - 2
        }
    }
    Rectangle {
        color : palette.keyDownColor
        anchors.centerIn : platBackground
        width : platBackground.width - 2
        height : platBackground.height - 2
        Text {
            id : title
            anchors.centerIn : parent
            color : palette.keyTextColor
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
