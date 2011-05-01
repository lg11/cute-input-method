import Qt 4.7

Rectangle {
    id : plat
    width : 0
    height : preeditStringText.paintedHeight
    color : "#00444444"

    property string preeditString : ""
    property string invaildCode : ""

    Row {
        anchors.centerIn : parent
        spacing : 5
        Text {
            id : preeditStringText
            font.pointSize : 30; font.bold: false
            color : "#FFFFFFFF"
            text : preeditString
        }
        Text {
            id : invaildCodeText
            font.pointSize : 30; font.bold: false
            color : "#FFFF0000"
            text : invaildCode
        }
    }

    /*onPreeditStringChanged : {*/
        /*console.log( preeditStringText.paintedWidth )*/
        /*console.log( preeditStringText.paintedHeight )*/
    /*}*/

    states {
        State {
            name : "ACTIVE" ; when : preeditString.length > 0 || invaildCode.length > 0
            PropertyChanges { target : plat ; color : "#EE333333" ; width : preeditStringText.paintedWidth + invaildCodeText.paintedWidth + 20 }
        } 
    }
}
