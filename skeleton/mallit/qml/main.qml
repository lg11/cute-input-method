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

    RealMouseArea {
        id : root
        x : 0
        y : 160
        width : 854
        height : 320
        Keyboard {
            id : keyboard
            x : 0
            y : 0
            width : 854
            height : 320
        }
    }
    Tooltip {
        id : tooltip
    }

    Component.onCompleted : {
        inputmethod.setInputMethodArea( Qt.rect( root.x, root.y, root.width, root.height ) )
        console.log( "load start" ) 
        engine.load( "workspace/cim/data/formated" )
        engine.setKeyboardLayout( 1 )
        console.log( "load end" ) 
    }
}

