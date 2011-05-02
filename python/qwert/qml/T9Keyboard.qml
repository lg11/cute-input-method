import Qt 4.7
import "utils.js" as Utils

Item {
    id : keyboard
    width : keyWidth * 4
    height : keyHeight * 4
    clip : true
    /*Rectangle { anchors.fill : parent ; color : "#FFFFFFFF" }*/
    /*Palette { id : palette }*/

    property int keyWidth : 136
    property int keyHeight : 97

    property int mask : 0
    property int mode : 0

    function updateCandString() {
        imEngine.updateCandString( 0 )

        imEngine.updatePreeditString( 0 )
        preedit.preeditString = imEngine.preeditString
        preedit.invaildCode = imEngine.invaildCode
        preedit.selectedWord = imEngine.selectedWord

        imEngine.updateCandString( 1 )
        imEngine.updateCandString( 2 )
        imEngine.updateCandString( 3 )
        imEngine.updateCandString( 4 )
    }
    function keyPress( key ) {
        var keycode = key.keycode
        /*var keysym = Utils.keysym[mode][keycode]*/
    }
    function keyRelease( key ) {
        var keycode = key.keycode
        var keysym = Utils.keysym[mode][keycode]
        if ( keycode >= Utils.keycode_2 && keycode <= Utils.keycode_9 && mask == Utils.keymask_null ) {
            if ( mode == 0 ) {
                imEngine.appendCode( keysym[mask] )
                updateCandString()
            }
            else {
                root.textview.insert( keysym[mask] )
            }
        }
    }
    function keyEnter( key ) {
    }
    function keyExit( key ) {
    }
    function backspace() {
    }

    Column {
        anchors.fill : parent
        Row {
            Key { id : key_1 ; keycode : Utils.keycode_1 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_2 ; keycode : Utils.keycode_2 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_3 ; keycode : Utils.keycode_3 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            AutoRepeatKey { id : key_backspace ; keycode : Utils.keycode_backspace ; width : keyWidth ; height : keyHeight ; color : Qt.darker( palette.keyNormalColor, 1.25 ) ; onRepeated : backspace() }
        }
        Row {
            Key { id : key_4 ; keycode : Utils.keycode_4 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_5 ; keycode : Utils.keycode_5 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_6 ; keycode : Utils.keycode_6 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
        }
        Row {
            Key { id : key_7 ; keycode : Utils.keycode_7 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_8 ; keycode : Utils.keycode_8 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_9 ; keycode : Utils.keycode_9 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_enter ; keycode : Utils.keycode_enter ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
        }
        Row {
            Key { id : key_shift_l ; keycode : Utils.keycode_shift_l ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_0 ; keycode : Utils.keycode_0 ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_alt_r ; keycode : Utils.keycode_alt_r ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_alt_space ; keycode : Utils.keycode_space ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
        }
    }
}

/*}*/
