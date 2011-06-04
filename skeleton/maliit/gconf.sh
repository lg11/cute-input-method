#gconftool-2 -s /meegotouch/inputmethods/onscreen/enabled --list-type=string -t list "["libmcip.so",""]"
#gconftool-2 -s /meegotouch/inputmethods/onscreen/active --list-type=string -t list "["libmcip.so",""]"
#gconftool-2 -s /meegotouch/inputmethods/onscreen/enabled --list-type=string -t list "["libmeego-keyboard-quick.so",""]"
#gconftool-2 -s /meegotouch/inputmethods/onscreen/active --list-type=string -t list "["libmeego-keyboard-quick.so",""]"



gconftool-2 -s /meegotouch/inputmethods/plugins/hardware -t string "libmeego-keyboard.so"
gconftool-2 -u /meegotouch/inputmethods/plugins/onscreen

gconftool-2 -R /meegotouch/inputmethods
