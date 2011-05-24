import Qt 4.7
import "utils.js" as Utils

Item {
    id : keyboard
    width : keyWidth * 5
    height : keyHeight * 4
    clip : true

    property int keyWidth : 136
    property int keyHeight : 97

    property int mask : 0
    property int mode : 0
    property bool selectMode : false 
    property bool puncMode : false 
    property int puncPage : 0

    property alias backspaceKey : key_backspace

    function updatePunc() {
        if ( puncMode == true ) {
            key_1.candString = " "
            key_2.candString = Utils.t9PuncMap[puncPage][0]
            key_3.candString = Utils.t9PuncMap[puncPage][1]
            key_4.candString = Utils.t9PuncMap[puncPage][2]
            key_5.candString = Utils.t9PuncMap[puncPage][3]
            key_6.candString = Utils.t9PuncMap[puncPage][4]
            key_7.candString = Utils.t9PuncMap[puncPage][5]
            key_8.candString = Utils.t9PuncMap[puncPage][6]
            key_9.candString = Utils.t9PuncMap[puncPage][7]
        }
        else {
            key_1.candString = "" 
            key_2.candString = "" 
            key_3.candString = ""
            key_4.candString = ""
            key_5.candString = ""
            key_6.candString = ""
            key_7.candString = ""
            key_8.candString = ""
            key_9.candString = ""
        }
    }
    function rollPunc() {
        if ( puncMode == false ) {
            puncMode = true
            puncPage = 0
            updatePunc()
        }
        else if ( puncPage == 0 ) {
            puncPage = 1
            updatePunc()
        }
        else if ( puncPage == 1 ) {
            puncPage = 2
            updatePunc()
        }
        else if ( puncPage == 2 ) {
            puncPage = 3
            updatePunc()
        }
        else if ( puncPage == 3 ) {
            puncMode = false
            updatePunc()
        }
    }
    function updateCandString() {
        imEngine.updateCandString( 0 )
        key_1.candString = imEngine.candString

        imEngine.updatePreeditString( 0 )
        preedit.preeditString = imEngine.preeditString
        preedit.invaildCode = imEngine.invaildCode
        preedit.selectedWord = imEngine.selectedWord

        imEngine.updateCandString( 1 )
        key_2.candString = imEngine.candString
        imEngine.updateCandString( 2 )
        key_3.candString = imEngine.candString
        imEngine.updateCandString( 3 )
        key_4.candString = imEngine.candString
        imEngine.updateCandString( 4 )
        key_5.candString = imEngine.candString
        imEngine.updateCandString( 5 )
        key_6.candString = imEngine.candString
    }
    function commit() {
        if ( imEngine.hasSelected ) {
            root.textview.insert( imEngine.selectedWord )
            imEngine.commit()
        }
    }
    function backspace() {
        if ( !key_backspace.paused ) {
            if ( imEngine.hasSelected ) {
                imEngine.cancel()
                updateCandString()
            }
            else if ( imEngine.hasCode ) {
                if ( selectMode == true ) {
                    selectMode = false
                    /*key_backspace.pauseAutoRepeat()*/
                }
                else {
                    imEngine.backspace()
                    updateCandString()
                    if ( !imEngine.hasCode ) {
                        key_backspace.pauseAutoRepeat()
                    }
                }
            }
            else {
                root.textview.backspace()
            }
        }
    }
    function keyPress( key ) {
        var keycode = key.keycode
        /*var keysym = Utils.keysym[mode][keycode]*/
    }
    function keyRelease( key ) {
        var keycode = key.keycode
        var keysym = Utils.keysym[mode][keycode]
        if ( selectMode ) {
            if ( keycode >= Utils.keycode_1 && keycode <= Utils.keycode_6 ) {
                var index = keycode - Utils.keycode_1
                imEngine.select( index )
                updateCandString()
                if ( imEngine.needCommit ) {
                    commit()
                    updateCandString()
                    selectMode = false
                }
            }
            else if ( keycode == Utils.keycode_7 ) {
                imEngine.prevPage()
                updateCandString()
            }
            else if ( keycode == Utils.keycode_9 ) {
                imEngine.nextPage()
                updateCandString()
            }
            else if ( keycode == Utils.keycode_backspace ) {
                backspace()
            }
        }
        else if ( puncMode ) {
            if ( keycode >= Utils.keycode_2 && keycode <= Utils.keycode_9 ) {
                var index = keycode - Utils.keycode_2
                root.textview.insert( Utils.t9PuncMap[puncPage][index] )
                puncMode = false
                updatePunc()
            }
            else if ( keycode == Utils.keycode_1 ) {
                rollPunc()
            }
        }
        else {
            if ( keycode >= Utils.keycode_2 && keycode <= Utils.keycode_9 ) {
                if ( mask == Utils.keymask_null ) {
                    imEngine.appendCode( keysym[mask] )
                    updateCandString()
                }
                else if ( mask == Utils.keymask_shift ) {
                    root.textview.insert( keysym[mask] )
                }
            }
            else if ( keycode == Utils.keycode_0 ) {
                if ( mask == Utils.keymask_null ) {
                    if ( !imEngine.hasCode )
                        root.textview.insert( " " )
                }
                else if ( mask == Utils.keymask_shift )
                    root.textview.insert( keysym[mask] )
            }
            else if ( keycode == Utils.keycode_1 ) {
                if ( imEngine.hasCode ) {
                    selectMode = true
                }
                else if ( mask == Utils.keymask_shift ) {
                    root.textview.insert( keysym[mask] )
                }
                else {
                    rollPunc()
                }
            }
            else if ( keycode == Utils.keycode_backspace ) {
                backspace()
            }
            else if ( keycode == Utils.keycode_enter ) {
                if ( imEngine.hasCode ) {
                    root.textview.insert( imEngine.code )
                    imEngine.clear()
                    updateCandString()
                }
                else {
                    root.textview.insert( "\n" )
                }
            }
            else if ( keycode == Utils.keycode_shift_l ) {
                if ( !imEngine.hasCode ) {
                    if ( mask != Utils.keymask_shift ) {
                        mask = Utils.keymask_shift
                        key_shift_l.keepDown = true
                    }
                    else {
                        mask = Utils.keymask_null
                        key_shift_l.keepDown = false
                    }
                }
            }
        }
    }
    function keyEnter( key ) {
    }
    function keyExit( key ) {
    }

    Column {
        anchors.fill : parent
        Row {
            ProxyMouseArea { id : ikey_1 ; width : keyWidth ; height : keyHeight }
            T9CandKey { id : key_1 ; keycode : Utils.keycode_1 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            T9CandKey { id : key_2 ; keycode : Utils.keycode_2 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor ; subtitle : "abc" }
            T9CandKey { id : key_3 ; keycode : Utils.keycode_3 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor ; subtitle : "def" }
            AutoRepeatKey { id : key_backspace ; keycode : Utils.keycode_backspace ; width : keyWidth ; height : keyHeight ; color : Qt.darker( palette.keyNormalColor, 1.25 ) ; onRepeated : backspace() }
        }
        Row {
            ProxyMouseArea { id : ikey_4 ; width : keyWidth ; height : keyHeight }
            T9CandKey { id : key_4 ; keycode : Utils.keycode_4 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor ; subtitle : "ghi" }
            T9CandKey { id : key_5 ; keycode : Utils.keycode_5 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor ; subtitle : "jkl" }
            T9CandKey { id : key_6 ; keycode : Utils.keycode_6 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor ; subtitle : "mno" }
            ProxyMouseArea { id : ikey_6 ; width : keyWidth ; height : keyHeight }
        }
        Row {
            ProxyMouseArea { id : ikey_7 ; width : keyWidth ; height : keyHeight }
            T9CandKey { id : key_7 ; keycode : Utils.keycode_7 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor ; subtitle : "pqrs" }
            T9CandKey { id : key_8 ; keycode : Utils.keycode_8 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor ; subtitle : "tuv" }
            T9CandKey { id : key_9 ; keycode : Utils.keycode_9 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor ; subtitle : "wxyz" }
            ProxyMouseArea { id : ikey_9 ; width : keyWidth ; height : keyHeight }
            /*Key { id : key_enter ; keycode : Utils.keycode_enter ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }*/
        }
        Row {
            ProxyMouseArea { id : ikey_shift_l ; width : keyWidth ; height : keyHeight }
            Key { id : key_shift_l ; keycode : Utils.keycode_shift_l ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_0 ; keycode : Utils.keycode_0 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_enter ; keycode : Utils.keycode_enter ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            /*Key { id : key_alt_r ; keycode : Utils.keycode_alt_r ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }*/
            /*Key { id : key_space ; keycode : Utils.keycode_space ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }*/
        }
    }
    states {
        State {
            name : "SELECT" ; when : selectMode == true
            PropertyChanges { target : key_1 ; candSize : 21 ; candColor : palette.keyDownColor }
            PropertyChanges { target : key_2 ; candSize : 21 ; candColor : palette.keyDownColor }
            PropertyChanges { target : key_3 ; candSize : 21 ; candColor : palette.keyDownColor }
            PropertyChanges { target : key_4 ; candSize : 21 ; candColor : palette.keyDownColor }
            PropertyChanges { target : key_5 ; candSize : 21 ; candColor : palette.keyDownColor }
            PropertyChanges { target : key_6 ; candSize : 21 ; candColor : palette.keyDownColor }
            PropertyChanges { target : key_7 ; text : "◄" }
            PropertyChanges { target : key_8 ; text : "" }
            PropertyChanges { target : key_9 ; text : "►" }
        } 
    }
    Component.onCompleted : {
        ikey_1.target = key_1
        ikey_4.target = key_4
        ikey_6.target = key_6
        ikey_7.target = key_7
        ikey_9.target = key_9
        ikey_shift_l.target = key_shift_l

    }
}

/*}*/
