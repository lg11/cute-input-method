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
    property alias rightProxyTarget : textViewPart.rightProxyTarget
    property alias rightProxyOffset : textViewPart.rightProxyOffset 
    property alias modeTextVisible : modeText.visible
    property bool t9Mode : false
    property int keyboardModeRecord : 0
    property alias t9Text : t9SwitcherText.text

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
            id : modeText
            x : 5 ; y : 5
            text : Utils.modeString[keyboard.mode]
            color : palette.keyNormalColor
            font.pointSize: 26; font.bold: true
        }
        TextViewPart {
            id : textViewPart
            x : 0 ; y : 0
            width : parent.width ; height : textviewPartHeight
            rightProxyTarget : keyboard.backspaceKey
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
            x : keyboardOffset
            y : textviewPartHeight
        }
        Item {
            id : t9Switcher
            x : 0 ; y : 580
            width : root.width ; height : 120
            Text {
                id : t9SwitcherText
                anchors.centerIn : parent
                text : "t9"
                color : palette.keyNormalColor
            }
            FakeMouseArea {
                anchors.fill : parent
                onMouseReleased : {
                    if ( t9Mode == false ) {
                        t9Mode = true
                        /*if ( !imEngine.hasCode )*/
                            /*t9Mode = true*/
                    }
                    else if ( t9Mode == true ) {
                        t9Mode = false
                        /*if ( !imEngine.hasCode )*/
                            /*t9Mode = false*/
                    }
                }
            }
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
        /*useMouseTracker : true*/
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

    onT9ModeChanged : {
        if ( t9Mode == false ) {
            if ( rotateFlag == 1 ) {
                imEngine.setMode( 0 )
                keyboard.updateCandString()
                keyboard.mode = 1
            }
        }
        else if ( t9Mode == true ) {
            if ( rotateFlag == 1 ) {
                imEngine.setMode( 1 )
                t9Keyboard.selectMode = false
                t9Keyboard.updateCandString()
                if ( t9Keyboard.puncMode ) {
                    t9Keyboard.puncMode = false
                    t9Keyboard.updatePunc()
                }
            }
        }
    }
    onRotateFlagChanged : {
        if ( rotateFlag == 0 ) {
            if ( t9Mode == true ) {
                imEngine.setMode( 0 )
                keyboard.updateCandString()
                keyboard.mode = keyboardModeRecord
            }
        }
        else if ( rotateFlag == 1 ) {
            if ( t9Mode == true ) {
                imEngine.setMode( 1 )
                t9Keyboard.selectMode = false
                t9Keyboard.updateCandString()
                if ( t9Keyboard.puncMode ) {
                    t9Keyboard.puncMode = false
                    t9Keyboard.updatePunc()
                }
            }
            keyboardModeRecord = keyboard.mode
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
                rightProxyTarget : keyboard.backspaceKey
                rightProxyOffset : 550
                modeTextVisible : true
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
                rightProxyTarget : keyboard.backspaceKey
                rightProxyOffset : 290
                modeTextVisible : true
                t9Text : "t9"
            }
        } 
        State {
            name : "PORT_T9" ; when : rotateFlag == 1 && t9Mode == true
            PropertyChanges {
                target : root
                width : 480
                height : 700
                keyboardOffset : 15 - t9KeyWidth
                textviewPartHeight : 160
                sideSpacing : 50
                keyWidth : 0
                keyHeight : 0
                numKeyWidth : keyWidth 
                numKeyHeight : numKeyWidth * 1.75
                useIKey_l : false
                t9KeyWidth : 140
                t9KeyHeight : 100
                rightProxyTarget : t9Keyboard.backspaceKey
                rightProxyOffset : 290
                modeTextVisible : false
                t9Text : "qwert"
            }
        } 
     }
    Component.onCompleted : {
        t9Mode = true
    }
}
