import Qt 4.7


Rectangle {
    width : 800
    height : 480
    color : "#00FF0000"

    property int keyWidth
    property int keyHeight

    keyWidth : 800 / 10 * 0.975
    keyHeight : keyWidth

    Column {
        anchors.fill : parent
        Row {
            Key { width : keyWidth ; height : keyHeight ; id : key_1 ; title: "1" }
            Key { width : keyWidth ; height : keyHeight ; id : key_2 ; title: "2" }
            Key { width : keyWidth ; height : keyHeight ; id : key_3 ; title: "3" }
            Key { width : keyWidth ; height : keyHeight ; id : key_4 ; title: "4" }
            Key { width : keyWidth ; height : keyHeight ; id : key_5 ; title: "5" }
            Key { width : keyWidth ; height : keyHeight ; id : key_6 ; title: "6" }
            Key { width : keyWidth ; height : keyHeight ; id : key_7 ; title: "7" }
            Key { width : keyWidth ; height : keyHeight ; id : key_8 ; title: "8" }
            Key { width : keyWidth ; height : keyHeight ; id : key_9 ; title: "9" }
            Key { width : keyWidth ; height : keyHeight ; id : key_0 ; title: "0" }
            Key { width : keyWidth ; height : keyHeight ; id : key_backspace ; title: "<" }
        }
        Row {
            Rectangle { width : keyWidth * 0.2 ; height : keyHeight }
            Key { width : keyWidth ; height : keyHeight ; id : key_q ; title: "q" }
            Key { width : keyWidth ; height : keyHeight ; id : key_w ; title: "w" }
            Key { width : keyWidth ; height : keyHeight ; id : key_e ; title: "e" }
            Key { width : keyWidth ; height : keyHeight ; id : key_r ; title: "r" }
            Key { width : keyWidth ; height : keyHeight ; id : key_t ; title: "t" }
            Key { width : keyWidth ; height : keyHeight ; id : key_y ; title: "y" }
            Key { width : keyWidth ; height : keyHeight ; id : key_u ; title: "u" }
            Key { width : keyWidth ; height : keyHeight ; id : key_i ; title: "i" }
            Key { width : keyWidth ; height : keyHeight ; id : key_o ; title: "o" }
            Key { width : keyWidth ; height : keyHeight ; id : key_p ; title: "p" }
        }
        Row {
            Rectangle { width : keyWidth * 0.4 ; height : keyHeight }
            Key { width : keyWidth ; height : keyHeight ; id : key_a ; title: "a" }
            Key { width : keyWidth ; height : keyHeight ; id : key_s ; title: "s" }
            Key { width : keyWidth ; height : keyHeight ; id : key_d ; title: "d" }
            Key { width : keyWidth ; height : keyHeight ; id : key_f ; title: "f" }
            Key { width : keyWidth ; height : keyHeight ; id : key_g ; title: "g" }
            Key { width : keyWidth ; height : keyHeight ; id : key_h ; title: "h" }
            Key { width : keyWidth ; height : keyHeight ; id : key_j ; title: "j" }
            Key { width : keyWidth ; height : keyHeight ; id : key_k ; title: "k" }
            Key { width : keyWidth ; height : keyHeight ; id : key_l ; title: "l" }
            Key { width : keyWidth * 2.0 ; height : keyHeight ; id : key_enter ; title: "Enter" }
        }
        Row {
            /*Key { width : keyWidth ; height : keyHeight ; id : key_l_shift ; title: "ift" }*/
            Rectangle { width : keyWidth * 1.0 ; height : keyHeight }
            Key { width : keyWidth ; height : keyHeight ; id : key_z ; title: "z" }
            Key { width : keyWidth ; height : keyHeight ; id : key_x ; title: "x" }
            Key { width : keyWidth ; height : keyHeight ; id : key_c ; title: "c" }
            Key { width : keyWidth ; height : keyHeight ; id : key_v ; title: "v" }
            Key { width : keyWidth ; height : keyHeight ; id : key_b ; title: "b" }
            Key { width : keyWidth ; height : keyHeight ; id : key_n ; title: "n" }
            Key { width : keyWidth ; height : keyHeight ; id : key_m ; title: "m" }
            Key { width : keyWidth ; height : keyHeight ; id : key_00 ; title: "," }
            Key { width : keyWidth ; height : keyHeight ; id : key_01 ; title: "." }
            /*Key { width : keyWidth ; height : keyHeight ; id : key_r_shift ; title: "Sh" }*/
        }
        Row {
            Key { width : keyWidth * 2.0 ; height : keyHeight ; id : key_l_shift ; title: "Shift" }
            Rectangle { width : keyWidth * 1.0 ; height : keyHeight }
            Key { width : keyWidth * 4.0 ; height : keyHeight ; id : key_space ; title: "" }
            Rectangle { width : keyWidth * 2.0 ; height : keyHeight }
            /*Key { width : keyWidth ; height : keyHeight ; id : key_00 ; title: "," }*/
            /*Key { width : keyWidth ; height : keyHeight ; id : key_01 ; title: "." }*/
            Key { width : keyWidth * 2.0 ; height : keyHeight ; id : key_r_shift ; title: "Shift" }
        }
    }
}
