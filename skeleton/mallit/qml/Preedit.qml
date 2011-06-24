import QtQuick 1.1
import com.meego 1.0

Button {
    id : plat
    width : selectedWordText.paintedWidth + break_1.paintedWidth + preeditCodeText.paintedWidth + break_2.paintedWidth + invaildCodeText.paintedWidth + 20
    height : preeditCodeText.paintedHeight + 10
    /*color : palette.preeditBackgroundColor*/
    visible : false

    property string selectedWord : ""
    property string preeditCode : ""
    property string invaildCode : ""

    Row {
        anchors.centerIn : parent
        Text {
            id : selectedWordText
            text : selectedWord
            font.pointSize : 22; font.bold: false
            color : palette.selectedWordColor
        }
        Text {
            id : break_1
            text : selectedWord.length > 0 && preeditCode.length > 0 ? "'" : ""
            font.pointSize : 22; font.bold: false
            color : palette.preeditCodeColor
        }
        Text {
            id : preeditCodeText
            text : preeditCode
            font.pointSize : 22; font.bold: false
            color : palette.preeditCodeColor
        }
        Text {
            id : break_2
            text : invaildCode.length > 0 && preeditCode.length > 0 ? "'" : ""
            font.pointSize : 22; font.bold: false
            color : palette.invaildCodeColor
        }
        Text {
            id : invaildCodeText
            text : invaildCode
            font.pointSize : 22; font.bold: false
            color : palette.invaildCodeColor
        }
    }

    /*onPreeditStringChanged : {*/
        /*console.log( preeditStringText.paintedWidth )*/
        /*console.log( preeditStringText.paintedHeight )*/
    /*}*/

    states {
        State {
            name : "ACTIVE" ; when : selectedWord.length > 0 || preeditCode.length > 0 || invaildCode.length > 0
            /*PropertyChanges { target : plat ; width : selectedWordText.paintedWidth + preeditStringText.paintedWidth + invaildCodeText.paintedWidth + 30 }*/
            PropertyChanges { target : plat ; visible : true }
        } 
    }
}
