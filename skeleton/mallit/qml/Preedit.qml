import Qt 4.7

Rectangle {
    id : plat
    width : selectedWordText.paintedWidth + break_1.paintedWidth + preeditCodeText.paintedWidth + break_2.paintedWidth + invaildCodeText.paintedWidth + 10
    height : preeditCodeText.paintedHeight + 10
    color : palette.preeditBackgroundColor
    visible : false

    property string selectedWord : ""
    property string preeditCode : ""
    property string invaildCode : ""

    Row {
        anchors.centerIn : parent
        Text {
            id : selectedWordText
            text : selectedWord
            font.pointSize : 28; font.bold: false
            color : palette.selectedWordColor
        }
        Text {
            id : break_1
            text : ""
            font.pointSize : 28; font.bold: false
            color : palette.preeditStringColor
        }
        Text {
            id : preeditCodeText
            text : preeditCode
            font.pointSize : 28; font.bold: false
            color : palette.preeditStringColor
            onTextChanged : break_1.text = text.length > 0 ? "'" : ""
        }
        Text {
            id : break_2
            text : ""
            font.pointSize : 28; font.bold: false
            color : palette.invaildCodeColor
        }
        Text {
            id : invaildCodeText
            text : invaildCode
            font.pointSize : 28; font.bold: false
            color : palette.invaildCodeColor
            onTextChanged : break_2.text = text.length > 0 ? "'" : ""
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
            PropertyChanges { target : plat ; visible : true }
        } 
    }
}
