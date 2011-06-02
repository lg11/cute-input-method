import Qt 4.7

ProxyMouseArea {
    id : key
    property alias candString : candText.text
    property alias subtitle : subtitleText.text
    property alias keycode : baseKey.keycode
    property alias text : baseKey.text
    property alias color : baseKey.color
    /*property alias candSize : candText.font.pointSize*/
    property int candSize : 20
    property alias candColor : candText.color
    target : baseKey
     
    Key {
        id : baseKey
        anchors.fill : parent
    }
    Rectangle {
        id : plat
        visible : false
        x : 1
        y : 1
        width : parent.width - 1
        height : parent.height - 1
        color : baseKey.color
    }
    Text {
        id : candText
        anchors.centerIn : parent
        color : "#FFFFFFFF"
        /*font.pointSize: 20 ; font.bold: false*/
        font.pointSize: candSize ; font.bold: false
    }
    Text {
        id : subtitleText
        anchors.centerIn : parent
        anchors.verticalCenterOffset : parent.height / 3
        color : "#BBFFFFFF"
        font.pointSize: 15; font.bold: false
    }
    /*ProxyMouseArea {*/
        /*target : baseKey*/
        /*anchors.fill : parent*/
    /*}*/

    states {
        State {
            name : "CAND" ; when : candString.length > 0
            PropertyChanges { target : plat ; visible : true }
        }
    }
}
