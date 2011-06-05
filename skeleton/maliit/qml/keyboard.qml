import Qt 4.7
import "utils.js" as Utils

Rectangle {
    id : canvas
    transformOrigin: Item.Center
    width: inputmethod.screenWidth
    height: inputmethod.screenHeight
    /*width: 1440*/
    /*height: 1080*/
    color: "transparent"
    opacity: 1

    property int rotateFlag : 0
    property bool t9Mode : false

    property alias keyWidth : keyboard.keyWidth
    property alias keyHeight : keyboard.keyHeight
    property alias numKeyWidth : keyboard.numKeyWidth
    property alias numKeyHeight : keyboard.numKeyHeight
    property alias t9KeyWidth : t9Keyboard.keyWidth
    property alias t9KeyHeight : t9Keyboard.keyHeight
    property alias useIKey_l : keyboard.useIKey_l
    property int keyboardModeRecord : 0
    property alias t9Text : t9SwitcherText.text

    IMEngine {
        id : imEngine
    }

    Palette { id : palette }
    Config { id : config }

    Preedit {
        id : preedit
        anchors.horizontalCenter : parent.horizontalCenter
        y : root.y - height - 20
    }
    Rectangle {
        anchors.centerIn : root
        width : canvas.width
        height : root.height + 10
        color : "#99FFFFFF"
    }
    Rectangle {
        id : root
        anchors.horizontalCenter : parent.horizontalCenter
        width : keyboard.width
        height : keyboard.height 
        y : canvas.height - height - 70
        clip : true
        color: "transparent"
        opacity: 1
        /*Rectangle {*/
            /*anchors.fill : parent*/
            /*color : palette.backgroundColor*/
        /*}*/
        /*Image {*/
            /*id : backgroundImage*/
            /*anchors.fill : parent*/
            /*fillMode : Image.PreserveAspectCrop*/
            /*source : config.backgroundImagePath*/
            /*visible : config.backgroundImageVisible*/
            /*opacity : config.backgroundImageOpacity*/
        /*}*/
        RootMouseArea {
            id : mouseLayer
            anchors.fill : parent
            Keyboard {
                id : keyboard
                anchors.horizontalCenter : parent.horizontalCenter
                anchors.top : parent.top
                width : keyWidth * 13
                height : numKeyHeight + keyHeight * 4
            }
            T9Keyboard {
                id : t9Keyboard
                anchors.horizontalCenter : parent.horizontalCenter
                anchors.top : parent.top
                width : keyWidth * 11
                height : numKeyHeight + keyHeight * 4
            }
            Item {
                id : t9Switcher
                x : 0 ; y : keyHeight * 5 + 50
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
        }
        RealMouseArea {
            anchors.fill : parent
            /*useMouseTracker : true*/
            ProxyMouseArea {
                anchors.fill : parent
                target : mouseLayer
            }
        }
    }
    Tooltip {
        id : tooltip
        height : 100
    }

    /*function setText( text ) {*/
        /*controlPadPart.mode = 0*/
        /*controlPadPart.stateFlag = 0*/
        /*textview.selectionEndPos = 0*/
        /*textview.selectEnd()*/
        /*textview.set( text )*/
        /*imEngine.reset()*/
        /*keyboard.updateCandString()*/
    /*}*/
    /*function getText() {*/
        /*imEngine.flushLog()*/
        /*return textview.get()*/
    /*}*/
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
                target : canvas
                /*width : 800*/
                /*height : 424*/
                keyWidth : canvas.width / config.ppcm * 3.5
                keyHeight : keyWidth * 0.875
                numKeyWidth : keyWidth
                numKeyHeight : numKeyWidth * 0.875
                useIKey_l : true
                t9KeyWidth : 0
                t9KeyHeight : 0
            }
        } 
        State {
            name : "PORT_FULL" ; when : rotateFlag == 1 && t9Mode == false
            PropertyChanges {
                target : canvas
                /*width : 480*/
                /*height : 700*/
                sideSpacing : 50
                keyWidth : 480 / 10 * 0.975 * 1.045
                keyHeight : keyWidth * 1.75
                numKeyWidth : keyWidth 
                numKeyHeight : numKeyWidth * 1.75
                useIKey_l : false
                t9KeyWidth : 0
                t9KeyHeight : 0
                t9Text : "t9"
            }
        } 
        State {
            name : "PORT_T9" ; when : rotateFlag == 1 && t9Mode == true
            PropertyChanges {
                target : canvas
                /*width : 480*/
                /*height : 700*/
                textviewPartHeight : 160
                keyWidth : 0
                keyHeight : 0
                numKeyWidth : keyWidth 
                numKeyHeight : numKeyWidth * 1.75
                useIKey_l : false
                t9KeyWidth : 140
                t9KeyHeight : 100
                t9Text : "qwert"
            }
        } 
     }
    Component.onCompleted : {
        console.log( "load start" ) 
        imEngine.load( "~/.config/mcip/sysdict" )
        imEngine.load( "~/.config/mcip/userdict.log" )
        console.log( "load end" ) 
        imEngine.startLog( "~/.config/mcip/userdict.log" )
        /*t9Mode = true*/
        rotateFlag = 0
        inputmethod.setInputMethodArea( Qt.rect( root.x, root.y, root.width, root.height ) )
    }
    Component.onDestruction : {
        console.log( "destruction" ) 
        imEngine.stopLog()
    }

}
