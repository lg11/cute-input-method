import Qt 4.7
import "utils.js" as Utils

/*RootMouseArea {*/
Item {
    id : keyboard
    width : 800
    height : 480
    clip : true
    /*color : "#00FF0000"*/

    property int keyWidth
    property int keyHeight
    property int numKeyWidth
    property int numKeyHeight

    property bool useIKey_l : true
    property Item pressedKey
    property alias backspaceKey : key_backspace

    /*keyWidth : 800 / 10 * 1.010*/
    /*keyHeight : keyWidth * 0.975*/

    property int mask : 0
    property int mode : 0

    function updateCandString() {
        engine.updateCandidate( 0 )
        key_5_6.candString = engine.getWord()

        preedit.preeditString = engine.getPreeditCode()
        preedit.invaildCode = engine.getInvalidCode()
        preedit.selectedWord = engine.getSelectedWord()

        engine.updateCandidate( 1 )
        key_3_4.candString = engine.getWord()
        engine.updateCandidate( 2 )
        key_7_8.candString = engine.getWord()
        engine.updateCandidate( 3 )
        key_9_0.candString = engine.getWord()
        engine.updateCandidate( 4 )
        key_1_2.candString = engine.getWord()
    }
    function commit() {
        /*if ( engine.getSelectedLength() > 0 ) {*/
        root.textview.insert( engine.getSelectedWord() )
        engine.commit()
        /*}*/
    }
    property bool needClearShift : false
    property bool needClearAlt : false
    function keyPress( key ) {
        var keycode = key.keycode
        if ( keycode == Utils.keycode_space ) {
            if ( engine.getCodeLength() <= 0 ) {
                if ( mask == Utils.keymask_null ) {
                    clearMask()
                    key_space.keepDown = true
                    mask = Utils.keymask_space
                }
            }
        }
        else if ( keycode == Utils.keycode_shift_l || keycode == Utils.keycode_shift_r ) {
            if ( engine.getCodeLength() <= 0 ) {
                if ( mask != Utils.keymask_shift ) {
                    clearMask()
                    key_shift_l.keepDown = true
                    key_shift_r.keepDown = true
                    mask = Utils.keymask_shift
                }
                else
                    needClearShift = true
            }
        }
        else if ( keycode == Utils.keycode_alt_l || keycode == Utils.keycode_alt_r ) {
            if ( engine.getCodeLength() <= 0 ) {
                if ( mask != Utils.keymask_alt ) {
                    clearMask()
                    key_alt_l.keepDown = true
                    key_alt_r.keepDown = true
                    mask = Utils.keymask_alt
                }
                else
                    needClearAlt = true
            }
        }
        moveTooltip( key )
    }
    function clearMask() {
        key_alt_l.keepDown = false
        key_alt_r.keepDown = false
        key_shift_l.keepDown = false
        key_shift_r.keepDown = false
        key_space.keepDown = false
        mask = Utils.keymask_null
        needClearAlt = false
        needClearShift = false
    }
    function switchMode() {
        if ( mode == Utils.mode_CN ) {
            if ( engine.getCodeLength() <= 0 ) {
                mode = Utils.mode_EN 
            }
        }
        else if ( mode == Utils.mode_EN ) {
            mode = Utils.mode_CN 
        }
    }
    function backspace() {
        if ( !key_backspace.paused ) {
            if ( engine.getSelectedLength() > 0 ) {
                engine.cancel()
                updateCandString()
            }
            else if ( engine.getCodeLength() > 0 ) {
                engine.popCode()
                updateCandString()
                if ( engine.getCodeLength() <= 0 ) 
                    key_backspace.pauseAutoRepeat()
            }
            else {
                root.textview.backspace()
            }
        }
    }
    function keyRelease( key ) {
        var keycode = key.keycode
        var keysym = Utils.keysym[mode][keycode]
        if ( keycode >= Utils.keycode_a && keycode <= Utils.keycode_z && mask == Utils.keymask_null ) {
            /*engine.appendCode( keysym[mask][mode] )*/
            if ( mode == Utils.mode_CN ) {
                engine.appendCode( keysym[mask] )
                updateCandString()
            }
            else {
                root.textview.insert( keysym[mask] )
            }
        }
        else if ( keycode == Utils.keycode_backspace ) {
            backspace()
        }
        else if ( keycode == Utils.keycode_shift_l ) {
            if ( engine.getCodeLength() > 0 ) {
                engine.prevPage()
                updateCandString()
            }
        }
        else if ( keycode == Utils.keycode_shift_r ) {
            if ( engine.getCodeLength() > 0 ) {
                engine.nextPage()
                updateCandString()
            }
        }
        else if ( keycode == Utils.keycode_alt_l ) {
            if ( engine.getCodeLength() > 0 ) {
                engine.prevPage()
                updateCandString()
            }
        }
        else if ( keycode == Utils.keycode_alt_r ) {
            if ( engine.getCodeLength() > 0 ) {
                engine.nextPage()
                updateCandString()
            }
        }
        else if ( keycode == Utils.keycode_enter ) {
            if ( engine.getCodeLength() > 0 ) {
                root.textview.insert( engine.getCode() )
                engine.reset()
                updateCandString()
            }
            else {
                root.textview.insert( "\n" )
            }
        }
        else if ( keycode == Utils.keycode_space ) {
            if ( engine.getCodeLength() > 0 ) {
                engine.select( 0 )
                updateCandString()
                if ( engine.getCodeLength() <= 0 && engine.getInvalidCodeLength() <= 0 && engine.getSelectedLength() > 0 ) {
                    commit()
                    updateCandString()
                }
            }
            else {
                root.textview.insert( keysym[mask] )
            }
        }
        else if ( keycode >= Utils.keycode_0 && keycode <= Utils.keycode_9 ) {
            if ( engine.getCodeLength() > 0 ) {
                var index = keycode - Utils.keycode_0
                index = Utils.candIndex[index]
                engine.select( index )
                updateCandString()
                if ( engine.getCodeLength() <= 0 && engine.getInvalidCodeLength() <= 0 && engine.getSelectedLength() > 0 ) {
                    commit()
                    updateCandString()
                }
            }
            else {
                root.textview.insert( keysym[mask] )
            }
        }
        else if ( keycode != Utils.keycode_ctrl && keycode != Utils.keycode_alt_l && keycode != Utils.keycode_alt_r ) {
            root.textview.insert( keysym[mask] )
        }
        tooltip.text = ""
        if ( keycode == Utils.keycode_shift_l || keycode == Utils.keycode_shift_r ) {
            if ( needClearShift ) {
                clearMask()
                /*needClearShift = false*/
            }
            /*else*/
                /*needClearShift = true*/
        }
        else if ( keycode == Utils.keycode_alt_l || keycode == Utils.keycode_alt_r ) {
            if ( needClearAlt ) {
                clearMask()
                /*needClearAlt = false*/
            }
            /*else*/
                /*needClearAlt = true*/
        }
        else {
            clearMask()
            /*if ( !needClearAlt && !needClearShift ) {*/
                /*clearMask()*/
            /*}*/
        }
    }
    function keyExit( key ) {
        pressedKey = null
        tooltip.text = ""
        /*tooltip.visible = false*/
        /*console.log( "exit", key.keysym[0] )*/
    }
    function keyEnter( key ) {
        /*console.log( "enter", key.keysym[0] )*/
        pressedKey = key
        moveTooltip( key )
    }
    function moveTooltip( key ) {
        /*var keycode = key.keycode*/
        /*var keysym = Utils.keysym[keycode]*/
        if ( !key.keepDown ) {
            var parent = key.parent
            var pos = parent.mapToItem( tooltip.parent, key.x, key.y )
            var x = pos.x + key.width / 2 - tooltip.width / 2
            var y = pos.y - tooltip.height - keyHeight * 0.1
            if ( y < -10 ) {
                y = -10
            }
            tooltip.x = x
            tooltip.y = y
            
            tooltip.text = key.text
        }
        else {
            tooltip.text = ""
        }
    }

    Column {
        anchors.fill : parent
        Row {
            CandKey { id : key_1_2 ; keycode_l : Utils.keycode_1 ; keycode_r : Utils.keycode_2 ; width : numKeyWidth * 2.0 ; height : numKeyHeight ; color_l : palette.keyNormalColor ; color_r : palette.keyNormalColor }
            CandKey { id : key_3_4 ; keycode_l : Utils.keycode_3 ; keycode_r : Utils.keycode_4 ; width : numKeyWidth * 2.0 ; height : numKeyHeight ; color_l : palette.keyNormalColor ; color_r : palette.keyNormalColor }
            CandKey { id : key_5_6 ; keycode_l : Utils.keycode_5 ; keycode_r : Utils.keycode_6 ; width : numKeyWidth * 2.0 ; height : numKeyHeight ; color_l : palette.keyNormalColor ; color_r : palette.keyNormalColor }
            CandKey { id : key_7_8 ; keycode_l : Utils.keycode_7 ; keycode_r : Utils.keycode_8 ; width : numKeyWidth * 2.0 ; height : numKeyHeight ; color_l : palette.keyNormalColor ; color_r : palette.keyNormalColor }
            CandKey { id : key_9_0 ; keycode_l : Utils.keycode_9 ; keycode_r : Utils.keycode_0 ; width : numKeyWidth * 2.0 ; height : numKeyHeight ; color_l : palette.keyNormalColor ; color_r : palette.keyNormalColor }
            AutoRepeatKey { id : key_backspace ; keycode : Utils.keycode_backspace ; width : numKeyWidth ; height : numKeyHeight ; color : Qt.darker( palette.keyNormalColor, 1.25 ) ; onRepeated : backspace() }
        }
        Row {
            Item { width : keyWidth * 0.25 ; height : keyHeight }
            Key { id : key_q ; keycode : Utils.keycode_q ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_w ; keycode : Utils.keycode_w ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_e ; keycode : Utils.keycode_e ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_r ; keycode : Utils.keycode_r ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_t ; keycode : Utils.keycode_t ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_y ; keycode : Utils.keycode_y ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_u ; keycode : Utils.keycode_u ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_i ; keycode : Utils.keycode_i ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_o ; keycode : Utils.keycode_o ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_p ; keycode : Utils.keycode_p ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            /*ProxyMouseArea { id : ikey_backspace ; width : keyWidth ; height : keyHeight }*/
            ProxyMouseArea { id : ikey_p ; width : keyWidth ; height : keyHeight }
        }
        Row {
            ProxyMouseArea { id : ikey_a ; width : keyWidth * 0.5 ; height : keyHeight }
            Key { id : key_a ; keycode : Utils.keycode_a ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_s ; keycode : Utils.keycode_s ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_d ; keycode : Utils.keycode_d ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_f ; keycode : Utils.keycode_f ; width : keyWidth ; height : keyHeight ; color : Qt.darker( palette.keyNormalColor, 1.25 ) }
            Key { id : key_g ; keycode : Utils.keycode_g ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_h ; keycode : Utils.keycode_h ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_j ; keycode : Utils.keycode_j ; width : keyWidth ; height : keyHeight ; color : Qt.darker( palette.keyNormalColor, 1.25 ) }
            Key { id : key_k ; keycode : Utils.keycode_k ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_l ; keycode : Utils.keycode_l ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_enter ; keycode : Utils.keycode_enter ; width : keyWidth * 2.0 ; height : keyHeight ; color : Qt.darker( palette.keyNormalColor, 1.25 ) }
        }
        Row {
            ProxyMouseArea { id : ikey_shift_l ; width : keyWidth ; height : keyHeight }
            Key { id : key_z ; keycode : Utils.keycode_z ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_x ; keycode : Utils.keycode_x ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_c ; keycode : Utils.keycode_c ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_v ; keycode : Utils.keycode_v ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_b ; keycode : Utils.keycode_b ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_n ; keycode : Utils.keycode_n ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_m ; keycode : Utils.keycode_m ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_comma ; keycode : Utils.keycode_comma ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            Key { id : key_dot ; keycode : Utils.keycode_dot ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor }
            ProxyMouseArea { id : ikey_shift_r ; width : keyWidth ; height : keyHeight }
        }
        Row {
            Key { id : key_shift_l ; keycode : Utils.keycode_shift_l ; width : keyWidth * 2.0 ; height : keyHeight ; color : palette.keyNormalColor }
            ProxyMouseArea { id : ikey_shift_l_2 ; width : keyWidth * 0.25 ; height : keyHeight }
            Key { id : key_alt_l ; keycode : Utils.keycode_alt_l ; width : keyWidth * 1.5 ; height : keyHeight ; color : Qt.darker( palette.keyNormalColor, 1.25 ) }
            ProxyMouseArea { id : ikey_alt_l ; width : keyWidth * 0.25 ; height : keyHeight }
            Key { id : key_space ; keycode : Utils.keycode_space ; width : keyWidth * 3.0 ; height : keyHeight ; color : palette.keyNormalColor }
            ProxyMouseArea { id : ikey_alt_r ; width : keyWidth * 0.25 ; height : keyHeight }
            Key { id : key_alt_r ; keycode : Utils.keycode_alt_r ; width : keyWidth * 1.5 ; height : keyHeight ; color : Qt.darker( palette.keyNormalColor, 1.25 ) }
            ProxyMouseArea { id : ikey_shift_r_2 ; width : keyWidth * 0.25 ; height : keyHeight }
            Key { id : key_shift_r ; keycode : Utils.keycode_shift_r ; width : keyWidth * 2.0 ; height : keyHeight ; color : palette.keyNormalColor }
        }
    }
    ProxyMouseArea {
        id : ikey_l ; width : keyWidth * 0.35 ; height : keyHeight
        x : key_l.x + key_l.parent.x + key_l.parent.parent.x + key_l.width
        y : key_l.y + key_l.parent.y + key_l.parent.parent.y
    }

    Component.onCompleted : {
        ikey_a.target = key_a
        if ( useIKey_l )
            ikey_l.target = key_l
        else
            ikey_l.target = key_enter
        ikey_p.target = key_p
        ikey_shift_l.target = key_shift_l
        ikey_shift_r.target = key_shift_r
        ikey_shift_l_2.target = key_shift_l
        ikey_shift_r_2.target = key_shift_r
        ikey_alt_l.target = key_alt_l
        ikey_alt_r.target = key_alt_r
    }
}
