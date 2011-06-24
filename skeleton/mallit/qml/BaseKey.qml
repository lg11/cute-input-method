import QtQuick 1.1
import com.meego 1.0
/*import Qt.labs.gestures 1.0*/

FakeMouseArea {
    id : key
    property bool keepDown : false 
    property alias checked : button.checked

    Button {
        id : button
        x : 2
        y : 2
        width : parent.width - 4
        height : parent.height - 4
        /*anchors.fill :parent*/
        checked : down || keepDown
    }
    property alias text : button.text
    property bool titleVisible
    property color textColor
    property bool platVisible
    property color color

    /*states {*/
        /*State {*/
            /*name : "DOWN" ; when : down || keepDown*/
            /*PropertyChanges { target : plat ; color : palette.keyDownColor }*/
        /*} */
    /*}*/

}
