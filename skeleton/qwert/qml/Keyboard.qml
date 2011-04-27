import Qt 4.7

Rectangle {
    id : keyboard
    width : 800
    height : 480
    color : "#00FF0000"

    property int keycode_0 : 48
    property int keycode_1 : 49
    property int keycode_2 : 50
    property int keycode_3 : 51
    property int keycode_4 : 52
    property int keycode_5 : 52
    property int keycode_6 : 54
    property int keycode_7 : 55
    property int keycode_8 : 56
    property int keycode_9 : 57

    property int keycode_a : 97
    property int keycode_b : 98
    property int keycode_c : 99
    property int keycode_d : 100
    property int keycode_e : 101
    property int keycode_f : 102
    property int keycode_g : 103
    property int keycode_h : 104
    property int keycode_i : 105
    property int keycode_j : 106
    property int keycode_k : 107
    property int keycode_l : 108
    property int keycode_m : 109
    property int keycode_n : 110
    property int keycode_o : 111
    property int keycode_p : 112
    property int keycode_q : 113
    property int keycode_r : 114
    property int keycode_s : 115
    property int keycode_t : 116
    property int keycode_u : 117
    property int keycode_v : 118
    property int keycode_w : 119
    property int keycode_x : 120
    property int keycode_y : 121
    property int keycode_z : 122

    property int keycode_comma : 44
    property int keycode_dot : 46

    property int keycode_enter : 10
    property int keycode_space : 32
    property int keycode_backspace : 201
    property int keycode_shift : 202
    property int keycode_ctrl : 203
    property int keycode_alt : 204

    property variant keysym_0 : [ "0", "0", "0", "0" ]
    property variant keysym_1 : [ "1", "1", "1", "1" ]
    property variant keysym_2 : [ "2", "2", "2", "2" ]
    property variant keysym_3 : [ "3", "3", "3", "3" ]
    property variant keysym_4 : [ "4", "4", "4", "4" ]
    property variant keysym_5 : [ "5", "5", "5", "5" ]
    property variant keysym_6 : [ "6", "6", "6", "6" ]
    property variant keysym_7 : [ "7", "7", "7", "7" ]
    property variant keysym_8 : [ "8", "8", "8", "8" ]
    property variant keysym_9 : [ "9", "9", "9", "9" ]
    
    property variant keysym_a : [ "a", "A", "a", "a" ]
    property variant keysym_b : [ "b", "B", "b", "b" ]
    property variant keysym_c : [ "c", "C", "c", "c" ]
    property variant keysym_d : [ "d", "D", "d", "d" ]
    property variant keysym_e : [ "e", "E", "e", "e" ]
    property variant keysym_f : [ "f", "F", "f", "f" ]
    property variant keysym_g : [ "g", "G", "g", "g" ]
    property variant keysym_h : [ "h", "H", "h", "h" ]
    property variant keysym_i : [ "i", "I", "i", "i" ]
    property variant keysym_j : [ "j", "J", "j", "j" ]
    property variant keysym_k : [ "k", "K", "k", "k" ]
    property variant keysym_l : [ "l", "L", "l", "l" ]
    property variant keysym_m : [ "m", "M", "m", "m" ]
    property variant keysym_n : [ "n", "N", "n", "n" ]
    property variant keysym_o : [ "o", "O", "o", "o" ]
    property variant keysym_p : [ "p", "P", "p", "p" ]
    property variant keysym_q : [ "q", "Q", "q", "q" ]
    property variant keysym_r : [ "r", "R", "r", "r" ]
    property variant keysym_s : [ "s", "S", "s", "s" ]
    property variant keysym_t : [ "t", "T", "t", "t" ]
    property variant keysym_u : [ "u", "U", "u", "u" ]
    property variant keysym_v : [ "v", "V", "v", "v" ]
    property variant keysym_w : [ "w", "W", "w", "w" ]
    property variant keysym_x : [ "x", "X", "x", "x" ]
    property variant keysym_y : [ "y", "Y", "y", "y" ]
    property variant keysym_z : [ "z", "Z", "z", "z" ]

    property variant keysym_comma : [ ",", ",", ",", "," ]
    property variant keysym_dot : [ ".", ".", ".", "." ]

    property variant keysym_enter : [ "◄", "◄", "◄", "◄" ]
    property variant keysym_space : [ " ", " ", " ", " " ]
    property variant keysym_backspace : [ "◄", "◄", "◄", "◄" ]
    property variant keysym_shift : [ "▲", "▲", "▲", "▲" ]
    property variant keysym_ctrl : [ "", "", "", "" ]
    property variant keysym_alt : [ "", "", "", "" ]

    property int keyWidth
    property int keyHeight

    keyWidth : 800 / 10 * 0.975
    keyHeight : keyWidth

    property int mask_null : 0
    property int mask_shift : 1
    property int mask_ctrl : 2
    property int mask_alt : 3

    property int mask : 0

    function keyPress( keycode ) {
        if ( keycode == keycode_shift ) {
            if ( mask == mask_shift ) {
                mask = mask_null
                key_shift_l.isDown = false
                key_shift_r.isDown = false
            }
            else {
                mask = mask_shift
                key_shift_l.isDown = true
                key_shift_r.isDown = true
            }
        }
        /*console.log( "pressed" )*/
    }
    function keyRelease( keycode ) {
        /*console.log( "released" )*/
    }

    Column {
        anchors.fill : parent
        Row {
            Key { id : key_1 ; keycode : keycode_1 ; keysym : keysym_1 ; width : keyWidth ; height : keyHeight }
            Key { id : key_2 ; keycode : keycode_2 ; keysym : keysym_2 ; width : keyWidth ; height : keyHeight }
            Key { id : key_3 ; keycode : keycode_3 ; keysym : keysym_3 ; width : keyWidth ; height : keyHeight }
            Key { id : key_4 ; keycode : keycode_4 ; keysym : keysym_4 ; width : keyWidth ; height : keyHeight }
            Key { id : key_5 ; keycode : keycode_5 ; keysym : keysym_5 ; width : keyWidth ; height : keyHeight }
            Key { id : key_6 ; keycode : keycode_6 ; keysym : keysym_6 ; width : keyWidth ; height : keyHeight }
            Key { id : key_7 ; keycode : keycode_7 ; keysym : keysym_7 ; width : keyWidth ; height : keyHeight }
            Key { id : key_8 ; keycode : keycode_8 ; keysym : keysym_8 ; width : keyWidth ; height : keyHeight }
            Key { id : key_9 ; keycode : keycode_9 ; keysym : keysym_9 ; width : keyWidth ; height : keyHeight }
            Key { id : key_0 ; keycode : keycode_0 ; keysym : keysym_0 ; width : keyWidth ; height : keyHeight }
            Key { id : key_backspace ; keycode : keycode_backspace ; keysym : keysym_backspace ; width : keyWidth ; height : keyHeight ; mask : 0 }
        }
        Row {
            Rectangle { width : keyWidth * 0.2 ; height : keyHeight }
            Key { id : key_q ; keycode : keycode_q ; keysym : keysym_q ; width : keyWidth ; height : keyHeight }
            Key { id : key_w ; keycode : keycode_w ; keysym : keysym_w ; width : keyWidth ; height : keyHeight }
            Key { id : key_e ; keycode : keycode_e ; keysym : keysym_e ; width : keyWidth ; height : keyHeight }
            Key { id : key_r ; keycode : keycode_r ; keysym : keysym_r ; width : keyWidth ; height : keyHeight }
            Key { id : key_t ; keycode : keycode_t ; keysym : keysym_t ; width : keyWidth ; height : keyHeight }
            Key { id : key_y ; keycode : keycode_y ; keysym : keysym_y ; width : keyWidth ; height : keyHeight }
            Key { id : key_u ; keycode : keycode_u ; keysym : keysym_u ; width : keyWidth ; height : keyHeight }
            Key { id : key_i ; keycode : keycode_i ; keysym : keysym_i ; width : keyWidth ; height : keyHeight }
            Key { id : key_o ; keycode : keycode_o ; keysym : keysym_o ; width : keyWidth ; height : keyHeight }
            Key { id : key_p ; keycode : keycode_p ; keysym : keysym_p ; width : keyWidth ; height : keyHeight }
        }
        Row {
            Rectangle { width : keyWidth * 0.4 ; height : keyHeight }
            Key { id : key_a ; keycode : keycode_a ; keysym : keysym_a ; width : keyWidth ; height : keyHeight }
            Key { id : key_s ; keycode : keycode_s ; keysym : keysym_s ; width : keyWidth ; height : keyHeight }
            Key { id : key_d ; keycode : keycode_d ; keysym : keysym_d ; width : keyWidth ; height : keyHeight }
            Key { id : key_f ; keycode : keycode_f ; keysym : keysym_f ; width : keyWidth ; height : keyHeight }
            Key { id : key_g ; keycode : keycode_g ; keysym : keysym_g ; width : keyWidth ; height : keyHeight }
            Key { id : key_h ; keycode : keycode_h ; keysym : keysym_h ; width : keyWidth ; height : keyHeight }
            Key { id : key_j ; keycode : keycode_j ; keysym : keysym_j ; width : keyWidth ; height : keyHeight }
            Key { id : key_k ; keycode : keycode_k ; keysym : keysym_k ; width : keyWidth ; height : keyHeight }
            Key { id : key_l ; keycode : keycode_l ; keysym : keysym_l ; width : keyWidth ; height : keyHeight }
            Key { id : key_enter ; keycode : keycode_enter ; keysym : keysym_enter ; width : keyWidth * 2.0 ; height : keyHeight ; mask : 0 }
        }
        Row {
            Rectangle { width : keyWidth * 1.0 ; height : keyHeight }
            Key { id : key_z ; keycode : keycode_z ; keysym : keysym_z ; width : keyWidth ; height : keyHeight }
            Key { id : key_x ; keycode : keycode_x ; keysym : keysym_x ; width : keyWidth ; height : keyHeight }
            Key { id : key_c ; keycode : keycode_c ; keysym : keysym_c ; width : keyWidth ; height : keyHeight }
            Key { id : key_v ; keycode : keycode_v ; keysym : keysym_v ; width : keyWidth ; height : keyHeight }
            Key { id : key_b ; keycode : keycode_b ; keysym : keysym_b ; width : keyWidth ; height : keyHeight }
            Key { id : key_n ; keycode : keycode_n ; keysym : keysym_n ; width : keyWidth ; height : keyHeight }
            Key { id : key_m ; keycode : keycode_m ; keysym : keysym_m ; width : keyWidth ; height : keyHeight }
            Key { id : key_comma ; keycode : keycode_comma ; keysym : keysym_comma ; width : keyWidth ; height : keyHeight }
            Key { id : key_dot ; keycode : keycode_dot ; keysym : keysym_dot ; width : keyWidth ; height : keyHeight }
        }
        Row {
            Key { id : key_shift_l ; keycode : keycode_shift ; keysym : keysym_shift ; width : keyWidth * 2.0 ; height : keyHeight * 0.8 ; mask : 0 }
            Rectangle { width : keyWidth * 1.0 ; height : keyHeight * 0.8 }
            Key { id : key_space ; keycode : keycode_space ; keysym : keysym_space ; width : keyWidth * 4.0 ; height : keyHeight * 0.8 ; mask : 0 }
            Rectangle { width : keyWidth * 2.0 ; height : keyHeight * 0.8 }
            Key { id : key_shift_r ; keycode : keycode_shift ; keysym : keysym_shift ; width : keyWidth * 2.0 ; height : keyHeight * 0.8 ; mask : 0 }
        }
    }
}
