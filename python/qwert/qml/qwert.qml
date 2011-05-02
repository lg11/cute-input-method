import Qt 4.7
import "utils.js" as Utils

Item {
    id : root
    height : 800
    width : 424
    property int rotateFlag : 0
    property int keyboardOffset
    property int textviewPartHeight
    property alias sideSpacing : textViewPart.sideSpacing
    property alias keyWidth : keyboard.keyWidth
    property alias keyHeight : keyboard.keyHeight
    property alias numKeyWidth : keyboard.numKeyWidth
    property alias numKeyHeight : keyboard.numKeyHeight
    property alias t9KeyWidth : t9Keyboard.keyWidth
    property alias t9KeyHeight : t9Keyboard.keyHeight
    property alias useIKey_l : keyboard.useIKey_l
    property alias textview : textViewPart.view
    property bool t9Mode : true

    Palette { id : palette }
    Config { id : config }
    Rectangle {
        anchors.fill : parent
        color : palette.backgroundColor
    }
    Image {
        id : backgroundImage
        anchors.fill : parent
        fillMode : Image.PreserveAspectCrop
        source : config.backgroundImagePath
        visible : config.backgroundImageVisible
        opacity : config.backgroundImageOpacity
    }
    RootMouseArea {
        id : mouseLayer
        anchors.fill : parent
        Text {
            x : 5 ; y : 5
            text : Utils.modeString[keyboard.mode]
            color : palette.keyNormalColor
            font.pointSize: 26; font.bold: true
        }
        TextViewPart {
            id : textViewPart
            x : 0 ; y : 0
            width : parent.width ; height : textviewPartHeight
        }
        Keyboard {
            id : keyboard
            width : keyWidth * 11
            height : numKeyHeight + keyHeight * 4
            x : keyboardOffset
            y : textviewPartHeight
        }
        T9Keyboard {
            id : t9Keyboard
            x : 20
            y : textviewPartHeight
        }
        ControlPadPart {
            id : controlPadPart
            keyWidth : 115
            keyHeight : 95
            textview : root.textview
            textviewHeight : textviewPartHeight + 1
        }
    }
    RealMouseArea {
        anchors.fill : parent
        useMouseTracker : true
        ProxyMouseArea {
            anchors.fill : parent
            target : mouseLayer
        }
    }
    Preedit {
        id : preedit
        anchors.horizontalCenter : parent.horizontalCenteR
        y : ( textViewPart.height - height ) / 2
    }
    Tooltip {
        id : tooltip
        height : 100
    }
    function setText( text ) {
        controlPadPart.mode = 0
        controlPadPart.stateFlag = 0
        textview.selectionEndPos = 0
        textview.selectEnd()
        textview.set( text )
        imEngine.clear()
        keyboard.updateCandString()
    }
    function getText() {
        return textview.get()
    }
    function setRotate( flag ) {
        rotateFlag = flag
    }

    onRotateFlagChanged : {
        if ( rotateFlag == 0 ) {
            t9Mode = false
            imEngine.setMode( 0 )
        }
        else if ( rotateFlag == 1 ) {
            t9Mode = true
            imEngine.setMode( 1 )
        }
    }
    states {
        State {
            name : "LAND" ; when : rotateFlag == 0
            PropertyChanges {
                target : root
                width : 800
                height : 424
                keyboardOffset : -30
                textviewPartHeight : 75
                sideSpacing : 80
                keyWidth : 800 / 10 * 0.975
                keyHeight : keyWidth * 0.975
                numKeyWidth : keyWidth
                numKeyHeight : numKeyWidth * 0.925
                useIKey_l : true
                t9KeyWidth : 0
                t9KeyHeight : 0
            }
        } 
        State {
            name : "PORT_FULL" ; when : rotateFlag == 1 && t9Mode == false
            PropertyChanges {
                target : root
                width : 480
                height : 700
                keyboardOffset : -18
                textviewPartHeight : 160
                sideSpacing : 50
                keyWidth : 480 / 10 * 0.975 * 1.045
                keyHeight : keyWidth * 1.75
                numKeyWidth : keyWidth 
                numKeyHeight : numKeyWidth * 1.75
                useIKey_l : false
                t9KeyWidth : 0
                t9KeyHeight : 0
            }
        } 
        State {
            name : "PORT_T9" ; when : rotateFlag == 1 && t9Mode == true
            PropertyChanges {
                target : root
                width : 480
                height : 700
                keyboardOffset : -18
                textviewPartHeight : 160
                sideSpacing : 50
                keyWidth : 0
                keyHeight : 0
                numKeyWidth : keyWidth 
                numKeyHeight : numKeyWidth * 1.75
                useIKey_l : false
                t9KeyWidth : 138
                t9KeyHeight : 97
            }
        } 
    }
}
