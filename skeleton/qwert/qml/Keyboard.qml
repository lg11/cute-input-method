import Qt 4.7
import "utils.js" as Utils

RootMouseArea {
    id : keyboard
    width : 800
    height : 480
    /*color : "#00FF0000"*/

    property int keyWidth
    property int keyHeight
    property int numKeyWidth
    property int numKeyHeight

    property Item pressedKey

    keyWidth : 800 / 10 * 0.975
    keyHeight : keyWidth

    numKeyWidth : keyWidth
    numKeyHeight : numKeyWidth

    /*keyWidth : 800 / 10 * 1.010*/
    /*keyHeight : keyWidth * 0.975*/

    property int mask : 0

    function updateCandString() {
        imEngine.updateCandString( 0 )
        key_5_6.candString = imEngine.candString

        imEngine.updatePreeditString( 0 )
        preedit.preeditString = imEngine.preeditString
        preedit.invaildCode = imEngine.invaildCode
        preedit.selectedWord = imEngine.selectedWord

        imEngine.updateCandString( 1 )
        key_3_4.candString = imEngine.candString
        imEngine.updateCandString( 2 )
        key_7_8.candString = imEngine.candString
        imEngine.updateCandString( 3 )
        key_9_0.candString = imEngine.candString
        imEngine.updateCandString( 4 )
        key_1_2.candString = imEngine.candString
    }
    function commit() {
        if ( imEngine.hasSelected ) {
            textview.insert( imEngine.selectedWord )
            imEngine.clear()
        }
    }
    function keyPress( key ) {
        var keycode = key.keycode
        if ( keycode == Utils.keycode_shift_l || keycode == Utils.keycode_shift_r ) {
            if ( mask == Utils.keymask_shift ) {
                mask = Utils.keymask_null
                key_shift_l.keepDown = false
                key_shift_r.keepDown = false
            }
            else {
                if ( !imEngine.hasCode ) {
                    mask = Utils.keymask_shift
                    key_shift_l.keepDown = true
                    key_shift_r.keepDown = true
                }
            }
        }
    }
    function keyRelease( key ) {
        var keycode = key.keycode
        var keysym = Utils.keysym[keycode]
        if ( keycode >= Utils.keycode_a && keycode <= Utils.keycode_z && mask == Utils.keymask_null ) {
            imEngine.appendCode( keysym[mask] )
            updateCandString()
        }
        else if ( keycode == Utils.keycode_backspace ) {
            if ( imEngine.hasSelected ) {
                imEngine.cancel()
                updateCandString()
            }
            else if ( imEngine.hasCode ) {
                imEngine.backspace()
                updateCandString()
            }
            else {
                textview.backspace()
            }
        }
        else if ( keycode == Utils.keycode_shift_l ) {
            if ( imEngine.hasCode ) {
                imEngine.prevPage()
                updateCandString()
            }
        }
        else if ( keycode == Utils.keycode_shift_r ) {
            if ( imEngine.hasCode ) {
                imEngine.nextPage()
                updateCandString()
            }
        }
        else if ( keycode >= Utils.keycode_0 && keycode <= Utils.keycode_9 ) {
            if ( imEngine.hasCode ) {
                var index = keycode - Utils.keycode_0
                index = Utils.candIndex[index]
                imEngine.select( index )
                updateCandString()
                if ( imEngine.needCommit ) {
                    commit()
                    updateCandString()
                }
            }
            else {
                textview.insert( keysym[mask] )
            }
        }
        else if ( keycode != Utils.keycode_ctrl && keycode != Utils.keycode_alt && keycode != Utils.keycode_backspace && keycode != Utils.keycode_enter ) {
            textview.insert( keysym[mask] )
            /*preedit.preeditString = keysym[mask]*/
        }
        tooltip.text = ""
    }
    function keyExit( key ) {
        pressedKey = null
        /*tooltip.text = keysym[mask]*/
    }
    function keyEnter( key ) {
        pressedKey = key
        moveTooltip( key )
    }
    function moveTooltip( key ) {
        var keycode = key.keycode
        var keysym = Utils.keysym[keycode]
        var parent = key.parent
        var pos = parent.mapToItem( tooltip.parent, key.x, key.y )
        var x = pos.x + key.width / 2 - tooltip.width / 2
        var y = pos.y - tooltip.height - keyHeight * 0.1
        if ( y < -10 ) {
            y = -10
        }
        tooltip.x = x
        tooltip.y = y
        
        tooltip.text = keysym[mask]
    }

    Column {
        anchors.fill : parent
        Row {
            CandKey { id : key_1_2 ; keycode_l : Utils.keycode_1 ; keysym_l : Utils.keysym[Utils.keycode_1] ; keycode_r : Utils.keycode_2 ; keysym_r : Utils.keysym[Utils.keycode_2] ; width : numKeyWidth * 2.0 ; height : numKeyHeight }
            CandKey { id : key_3_4 ; keycode_l : Utils.keycode_3 ; keysym_l : Utils.keysym[Utils.keycode_3] ; keycode_r : Utils.keycode_4 ; keysym_r : Utils.keysym[Utils.keycode_4] ; width : numKeyWidth * 2.0 ; height : numKeyHeight }
            CandKey { id : key_5_6 ; keycode_l : Utils.keycode_5 ; keysym_l : Utils.keysym[Utils.keycode_5] ; keycode_r : Utils.keycode_6 ; keysym_r : Utils.keysym[Utils.keycode_6] ; width : numKeyWidth * 2.0 ; height : numKeyHeight }
            CandKey { id : key_7_8 ; keycode_l : Utils.keycode_7 ; keysym_l : Utils.keysym[Utils.keycode_7] ; keycode_r : Utils.keycode_8 ; keysym_r : Utils.keysym[Utils.keycode_8] ; width : numKeyWidth * 2.0 ; height : numKeyHeight }
            CandKey { id : key_9_0 ; keycode_l : Utils.keycode_9 ; keysym_l : Utils.keysym[Utils.keycode_9] ; keycode_r : Utils.keycode_0 ; keysym_r : Utils.keysym[Utils.keycode_0] ; width : numKeyWidth * 2.0 ; height : numKeyHeight }
            Key { id : key_backspace ; keycode : Utils.keycode_backspace ; keysym : Utils.keysym[Utils.keycode_backspace] ; width : numKeyWidth ; height : numKeyHeight ; mask : 0 }
        }
        Row {
            Rectangle { width : keyWidth * 0.25 ; height : keyHeight }
            Key { id : key_q ; keycode : Utils.keycode_q ; keysym : Utils.keysym[Utils.keycode_q] ; width : keyWidth ; height : keyHeight }
            Key { id : key_w ; keycode : Utils.keycode_w ; keysym : Utils.keysym[Utils.keycode_w] ; width : keyWidth ; height : keyHeight }
            Key { id : key_e ; keycode : Utils.keycode_e ; keysym : Utils.keysym[Utils.keycode_e] ; width : keyWidth ; height : keyHeight }
            Key { id : key_r ; keycode : Utils.keycode_r ; keysym : Utils.keysym[Utils.keycode_r] ; width : keyWidth ; height : keyHeight }
            Key { id : key_t ; keycode : Utils.keycode_t ; keysym : Utils.keysym[Utils.keycode_t] ; width : keyWidth ; height : keyHeight }
            Key { id : key_y ; keycode : Utils.keycode_y ; keysym : Utils.keysym[Utils.keycode_y] ; width : keyWidth ; height : keyHeight }
            Key { id : key_u ; keycode : Utils.keycode_u ; keysym : Utils.keysym[Utils.keycode_u] ; width : keyWidth ; height : keyHeight }
            Key { id : key_i ; keycode : Utils.keycode_i ; keysym : Utils.keysym[Utils.keycode_i] ; width : keyWidth ; height : keyHeight }
            Key { id : key_o ; keycode : Utils.keycode_o ; keysym : Utils.keysym[Utils.keycode_o] ; width : keyWidth ; height : keyHeight }
            Key { id : key_p ; keycode : Utils.keycode_p ; keysym : Utils.keysym[Utils.keycode_p] ; width : keyWidth ; height : keyHeight }
            ProxyMouseArea { id : ikey_backspace ; width : keyWidth ; height : keyHeight }
        }
        Row {
            Rectangle { width : keyWidth * 0.5 ; height : keyHeight }
            Key { id : key_a ; keycode : Utils.keycode_a ; keysym : Utils.keysym[Utils.keycode_a] ; width : keyWidth ; height : keyHeight }
            Key { id : key_s ; keycode : Utils.keycode_s ; keysym : Utils.keysym[Utils.keycode_s] ; width : keyWidth ; height : keyHeight }
            Key { id : key_d ; keycode : Utils.keycode_d ; keysym : Utils.keysym[Utils.keycode_d] ; width : keyWidth ; height : keyHeight }
            Key { id : key_f ; keycode : Utils.keycode_f ; keysym : Utils.keysym[Utils.keycode_f] ; width : keyWidth ; height : keyHeight }
            Key { id : key_g ; keycode : Utils.keycode_g ; keysym : Utils.keysym[Utils.keycode_g] ; width : keyWidth ; height : keyHeight }
            Key { id : key_h ; keycode : Utils.keycode_h ; keysym : Utils.keysym[Utils.keycode_h] ; width : keyWidth ; height : keyHeight }
            Key { id : key_j ; keycode : Utils.keycode_j ; keysym : Utils.keysym[Utils.keycode_j] ; width : keyWidth ; height : keyHeight }
            Key { id : key_k ; keycode : Utils.keycode_k ; keysym : Utils.keysym[Utils.keycode_k] ; width : keyWidth ; height : keyHeight }
            Key { id : key_l ; keycode : Utils.keycode_l ; keysym : Utils.keysym[Utils.keycode_l] ; width : keyWidth ; height : keyHeight }
            Key { id : key_enter ; keycode : Utils.keycode_enter ; keysym : Utils.keysym[Utils.keycode_enter] ; width : keyWidth * 2.0 ; height : keyHeight ; mask : 0 }
        }
        Row {
            ProxyMouseArea { id : ikey_shift_l ; width : keyWidth ; height : keyHeight }
            Key { id : key_z ; keycode : Utils.keycode_z ; keysym : Utils.keysym[Utils.keycode_z] ; width : keyWidth ; height : keyHeight }
            Key { id : key_x ; keycode : Utils.keycode_x ; keysym : Utils.keysym[Utils.keycode_x] ; width : keyWidth ; height : keyHeight }
            Key { id : key_c ; keycode : Utils.keycode_c ; keysym : Utils.keysym[Utils.keycode_c] ; width : keyWidth ; height : keyHeight }
            Key { id : key_v ; keycode : Utils.keycode_v ; keysym : Utils.keysym[Utils.keycode_v] ; width : keyWidth ; height : keyHeight }
            Key { id : key_b ; keycode : Utils.keycode_b ; keysym : Utils.keysym[Utils.keycode_b] ; width : keyWidth ; height : keyHeight }
            Key { id : key_n ; keycode : Utils.keycode_n ; keysym : Utils.keysym[Utils.keycode_n] ; width : keyWidth ; height : keyHeight }
            Key { id : key_m ; keycode : Utils.keycode_m ; keysym : Utils.keysym[Utils.keycode_m] ; width : keyWidth ; height : keyHeight }
            Key { id : key_comma ; keycode : Utils.keycode_comma ; keysym : Utils.keysym[Utils.keycode_comma] ; width : keyWidth ; height : keyHeight }
            Key { id : key_dot ; keycode : Utils.keycode_dot ; keysym : Utils.keysym[Utils.keycode_dot] ; width : keyWidth ; height : keyHeight }
            ProxyMouseArea { id : ikey_shift_r ; width : keyWidth ; height : keyHeight }
        }
        Row {
            Key { id : key_shift_l ; keycode : Utils.keycode_shift_l ; keysym : Utils.keysym[Utils.keycode_shift_l] ; width : keyWidth * 2.0 ; height : keyHeight * 0.8 ; mask : 0 }
            Rectangle { width : keyWidth * 1.0 ; height : keyHeight * 0.8 }
            Key { id : key_space ; keycode : Utils.keycode_space ; keysym : Utils.keysym[Utils.keycode_space] ; width : keyWidth * 4.0 ; height : keyHeight * 0.8 ; mask : 0 }
            Rectangle { width : keyWidth * 2.0 ; height : keyHeight * 0.8 }
            Key { id : key_shift_r ; keycode : Utils.keycode_shift_r ; keysym : Utils.keysym[Utils.keycode_shift_r] ; width : keyWidth * 2.0 ; height : keyHeight * 0.8 ; mask : 0 }
        }
    }

    Component.onCompleted : {
        ikey_backspace.target = key_backspace
        ikey_shift_l.target = key_shift_l
        ikey_shift_r.target = key_shift_r
    }
}
