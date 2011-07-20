import QtQuick 1.1
import com.meego 1.0

Item {
    id : plat
    width : title.paintedWidth > 75 ? Math.ceil( title.paintedWidth / 25 ) * 25 : 75
    height : title.paintedHeight + 25
    visible : false

    Button {
        anchors.fill : parent
        checked : true
    }

    Text {
        id : title
        anchors.centerIn : plat
        color : palette.keyTextColor
        font.pointSize: 36; font.bold: true
        /*visible : false*/
    }
    property alias text : title.text

    states {
        State {
            name : "ACTIVE" ; when : text.length > 0
            PropertyChanges { target : plat ; visible : true }
        }
    }
}
