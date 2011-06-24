import QtQuick 1.1
import com.meego 1.0

Item {
    ButtonStyle {
        id : buttonStyle
    }
    property color keyNormalColor : "#FF444444"
    property color keyDownColor : "#FF2299FF"
    property color keyTextColor : "#FFFFFFFF"
    property color keyBorderColor : "#FF444444"
    property color preeditBackgroundColor : "#AA444444"
    property color selectedWordColor : buttonStyle.textColor
    property color preeditCodeColor : buttonStyle.textColor
    property color invaildCodeColor : "#FFFF0000"
    property color backgroundColor : "#FFFFFFFF"
    property color textviewBackgroundColor : "#FFFFFFFF"
    property color textviewSelectionColor : "#992299FF"
    property color textviewCursorColor : "#992299FF"
    property color tooltipBackgroundColor : keyDownColor
    property color tooltipBorderColor : "#FFFFFFFF"
    property color controlPadKeyNormalColor : "#FFFFFFFF"
    property color controlPadKeyTextColor : keyNormalColor

    /*property color keyNormalColor : "#DD444444"*/
    /*property color keyDownColor : "#DD2299FF"*/
    /*property color keyTextColor : "#DDFFFFFF"*/
    /*property color preeditBackgroundColor : "#DD444444"*/
    /*property color selectedWordColor : "#DDFFFFFF"*/
    /*property color preeditStringColor : "#DDFFFFFF"*/
    /*property color invaildCodeColor : "#DDFF0000"*/
    /*property color backgroundColor : "#99FFFFFF"*/
}
