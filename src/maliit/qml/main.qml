import QtQuick 1.1
import com.meego 1.0

Rectangle {
    id : canvas
    transformOrigin : Item.Center
    width : inputmethod.screenWidth
    height : inputmethod.screenHeight
    color : "transparent"
    opacity : 1

    IMEngine {
        id : engine
    }

    Palette {
        id : palette
    }

    RootMouseArea {
        id : root
        x : 0
        y : 160
        width : parent.width
        height : 320
        /*Rectangle {*/
            /*anchors.fill : parent*/
            /*color : "#FF000000"*/
        /*}*/
        Keyboard {
            id : keyboard
            x : 0
            y : 0
            width : parent.width
            height : 320
        }
    }
    Preedit {
        id : preedit
        x : inputmethod.cursorRect.x
        y : inputmethod.cursorRect.y + inputmethod.cursorRect.height
    }
    Tooltip {
        id : tooltip
    }
    RealMouseArea {
        x : root.x
        y : root.y
        width : root.width
        height : root.height
        ProxyMouseArea {
            anchors.fill : parent
            target : root
        }
    }

    Component.onCompleted : {
        inputmethod.setInputMethodArea( Qt.rect( root.x, root.y, root.width, root.height ) )
        console.log( "load start" ) 
        engine.load( "/usr/share/cuteinputmethod/data/formated" )
        engine.setKeyboardLayout( 1 )
        console.log( "load end" ) 
    }
}

