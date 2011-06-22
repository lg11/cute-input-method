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
        id : imEngine
    }

    Button {
        id : button
        x : 200
        y : 200
        width : 200
        height : 80
        text : "test"
        onClicked : {
            imEngine.appendCode( "a" )
            imEngine.updateCandidate( 0 )
            console.log( "getcode", imEngine.getCode() )
            console.log( "getcode", imEngine.getPreeditCode() )
            button.text = imEngine.getWord()
        }
    }

    Component.onCompleted : {
        inputmethod.setInputMethodArea( Qt.rect( button.x, button.y, button.width, button.height ) )
        console.log( "load start" ) 
        imEngine.load( "workspace/cim/data/formated" )
        imEngine.setKeyboardLayout( 1 )
        console.log( "load end" ) 
    }
}

