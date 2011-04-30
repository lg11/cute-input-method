import Qt 4.7

Rectangle {
    id : plat
    width : 0
    height : preeditStringText.paintedHeight
    color : "#00000000"

    property string preeditString : ""

    Text {
        id : preeditStringText
        anchors.centerIn : parent
        font.pointSize : 30; font.bold: false
        color : "#EEFFFFFF"
        text : preeditString
    }

    /*onPreeditStringChanged : {*/
        /*console.log( preeditStringText.paintedWidth )*/
        /*console.log( preeditStringText.paintedHeight )*/
    /*}*/

    states {
        State {
            name : "ACTIVE" ; when : preeditString.length > 0
            PropertyChanges { target : plat ; color : "#EE333333" ; width : preeditStringText.paintedWidth + 10 }
        } 
    }
}
