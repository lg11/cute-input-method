import Qt 4.7

Item {
    id : plat
    width : title.paintedWidth > 75 ? Math.ceil( title.paintedWidth / 25 ) * 25 : 75

    visible : false

    Rectangle {
        id : platBackground
        anchors.horizontalCenter : parent.horizontalCenter
        color : palette.tooltipBorderColor
        width : parent.width
        height : parent.height * 0.8
    }
    Rectangle {
        color : palette.tooltipBorderColor
        anchors.centerIn : parent
        anchors.verticalCenterOffset : parent.height * 0.3
        width : parent.height * 0.15
        height : width
        rotation : 45
        Rectangle {
            color : palette.tooltipBackgroundColor
            anchors.centerIn : parent
            width : parent.width - 2
            height : parent.height - 2
        }
    }
    Rectangle {
        id : post
        color : palette.tooltipBackgroundColor
        anchors.centerIn : platBackground
        width : platBackground.width - 2
        height : platBackground.height - 2
    }
    Text {
        id : title
        anchors.centerIn : post
        color : palette.keyTextColor
        font.pointSize: 36; font.bold: true
    }
    property alias text : title.text

    states {
        State {
            name : "ACTIVE" ; when : text.length > 0
            PropertyChanges { target : plat ; visible : true }
        }
    }
}
