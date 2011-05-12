var keycode_0 = 48 ;
var keycode_1 = 49 ;
var keycode_2 = 50 ;
var keycode_3 = 51 ;
var keycode_4 = 52 ;
var keycode_5 = 53 ;
var keycode_6 = 54 ;
var keycode_7 = 55 ;
var keycode_8 = 56 ;
var keycode_9 = 57 ;

var keycode_a = 97 ;
var keycode_b = 98 ;
var keycode_c = 99 ;
var keycode_d = 100 ;
var keycode_e = 101 ;
var keycode_f = 102 ;
var keycode_g = 103 ;
var keycode_h = 104 ;
var keycode_i = 105 ;
var keycode_j = 106 ;
var keycode_k = 107 ;
var keycode_l = 108 ;
var keycode_m = 109 ;
var keycode_n = 110 ;
var keycode_o = 111 ;
var keycode_p = 112 ;
var keycode_q = 113 ;
var keycode_r = 114 ;
var keycode_s = 115 ;
var keycode_t = 116 ;
var keycode_u = 117 ;
var keycode_v = 118 ;
var keycode_w = 119 ;
var keycode_x = 120 ;
var keycode_y = 121 ;
var keycode_z = 122 ;

var keycode_comma = 44 ;
var keycode_dot = 46 ;

var keycode_enter = 10 ;
var keycode_space = 32 ;
var keycode_backspace = 201 ;
var keycode_shift_l = 202 ;
var keycode_shift_r = 203 ;
var keycode_ctrl = 204 ;
var keycode_alt_l = 205 ;
var keycode_alt_r = 206 ;

var keymask_null = 0 ;
var keymask_shift = 1 ;
var keymask_alt = 2 ;
var keymask_space = 3 ;
//var keymask_ctrl = 3 ;

var keysym = Array( 256 ) ;

keysym[keycode_0] = [ "0", "0", "0", "0" ] ;
keysym[keycode_1] = [ "1", "1", "1", "1" ] ;
keysym[keycode_2] = [ "2", "2", "2", "2" ] ;
keysym[keycode_3] = [ "3", "3", "3", "3" ] ;
keysym[keycode_4] = [ "4", "4", "4", "4" ] ;
keysym[keycode_5] = [ "5", "5", "5", "5" ] ;
keysym[keycode_6] = [ "6", "6", "6", "6" ] ;
keysym[keycode_7] = [ "7", "7", "7", "7" ] ;
keysym[keycode_8] = [ "8", "8", "8", "8" ] ;
keysym[keycode_9] = [ "9", "9", "9", "9" ] ;

keysym[keycode_a] = [ "a", "A", "*", "a" ] ;
keysym[keycode_b] = [ "b", "B", "\\", "b" ] ;
keysym[keycode_c] = [ "c", "C", "€", "c" ] ;
keysym[keycode_d] = [ "d", "D", "#", "d" ] ;
keysym[keycode_e] = [ "e", "E", "[", "e" ] ;
keysym[keycode_f] = [ "f", "F", "-", "f" ] ;
keysym[keycode_g] = [ "g", "G", "_", "g" ] ;
keysym[keycode_h] = [ "h", "H", "(", "h" ] ;
keysym[keycode_i] = [ "i", "I", "%", "i" ] ;
keysym[keycode_j] = [ "j", "J", ")", "j" ] ;
keysym[keycode_k] = [ "k", "K", "&", "k" ] ;
keysym[keycode_l] = [ "l", "L", "!", "l" ] ;
keysym[keycode_m] = [ "m", "M", "'", "m" ] ;
keysym[keycode_n] = [ "n", "N", "\"", "n" ] ;
keysym[keycode_o] = [ "o", "O", "~", "o" ] ;
keysym[keycode_p] = [ "p", "P", "^", "p" ] ;
keysym[keycode_q] = [ "q", "Q", "<", "q" ] ;
keysym[keycode_r] = [ "r", "R", "]", "r" ] ;
keysym[keycode_s] = [ "s", "S", "+", "s" ] ;
keysym[keycode_t] = [ "t", "T", "{", "t" ] ;
keysym[keycode_u] = [ "u", "U", "|", "u" ] ;
keysym[keycode_v] = [ "v", "V", "/", "v" ] ;
keysym[keycode_w] = [ "w", "W", ">", "w" ] ;
keysym[keycode_x] = [ "x", "X", "$", "x" ] ;
keysym[keycode_y] = [ "y", "Y", "}", "y" ] ;
keysym[keycode_z] = [ "z", "Z", "£", "z" ] ;

keysym[keycode_comma] = [ ",", "?", "@", "," ] ;
keysym[keycode_dot] = [ ".", "!", "=", "." ] ;

keysym[keycode_enter] = [ "◄", "◄", "◄", "◄" ] ;
keysym[keycode_space] = [ " ", "", "", " " ] ;
keysym[keycode_backspace] = [ "◄", "◄", "◄", "◄" ] ;
keysym[keycode_shift_l] = [ "▲", "▲", "▲", "▲" ] ;
keysym[keycode_shift_r] = [ "▲", "▲", "▲", "▲" ] ;
keysym[keycode_ctrl] = [ "", "", "", "" ] ;
keysym[keycode_alt_l] = [ "@", "@", "@", "@" ] ;
keysym[keycode_alt_r] = [ "@", "@", "@", "@" ] ;

var candIndex = Array( 10 ) ;
candIndex[0] = 3
candIndex[1] = 4
candIndex[2] = 4
candIndex[3] = 1
candIndex[4] = 1
candIndex[5] = 0
candIndex[6] = 0
candIndex[7] = 2
candIndex[8] = 2
candIndex[9] = 3

