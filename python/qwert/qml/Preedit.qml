import Qt 4.7

Rectangle {
    id : plat
    width : 0
    height : preeditStringText.paintedHeight + 10
    color : palette.preeditBackgroundColor

    property string selectedWord : ""
    property string preeditString : ""
    property string invaildCode : ""

    Row {
        anchors.centerIn : parent
        spacing : 5
        Text {
            id : selectedWordText
            font.pointSize : 28; font.bold: false
            color : palette.selectedWordColor
            text : selectedWord
        }
        Text {
            id : preeditStringText
            font.pointSize : 28; font.bold: false
            color : palette.preeditStringColor
            text : preeditString
        }
        Text {
            id : invaildCodeText
            font.pointSize : 28; font.bold: false
            color : palette.invaildCodeColor
            text : invaildCode
        }
    }

    /*onPreeditStringChanged : {*/
        /*console.log( preeditStringText.paintedWidth )*/
        /*console.log( preeditStringText.paintedHeight )*/
    /*}*/

    states {
        State {
            name : "ACTIVE" ; when : selectedWord.length > 0 || preeditString.length > 0 || invaildCode.length > 0
            /*PropertyChanges { target : plat ; width : selectedWordText.paintedWidth + preeditStringText.paintedWidth + invaildCodeText.paintedWidth + 30 }*/
            PropertyChanges { target : plat ; width : root.width }
        } 
    }
}
