import Qt 4.7

Rectangle {
    id : plat
    width : 0
    height : preeditStringText.paintedHeight
    color : config.preeditBackgroundColor

    property string preeditString : ""
    property string invaildCode : ""

    Row {
        anchors.centerIn : parent
        spacing : 5
        Text {
            id : preeditStringText
            font.pointSize : 30; font.bold: false
            color : config.preeditStringColor
            text : preeditString
        }
        Text {
            id : invaildCodeText
            font.pointSize : 30; font.bold: false
            color : config.invaildCodeColor
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
            PropertyChanges { target : plat ; width : preeditStringText.paintedWidth + invaildCodeText.paintedWidth + 20 }
        } 
    }
}
