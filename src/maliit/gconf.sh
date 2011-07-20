gconftool-2 -s /meegotouch/inputmethods/onscreen/enabled --list-type=string -t list "["libcuteinputmethod.so",""]"
gconftool-2 -s /meegotouch/inputmethods/onscreen/active --list-type=string -t list "["libcuteinputmethod.so",""]"

#rm /usr/lib/meego-im-plugins/libcuteinputmethod.so
#cp libcuteinputmethod.so /usr/lib/meego-im-plugins

#gconftool-2 -s /meegotouch/inputmethods/onscreen/enabled --list-type=string -t list "["libmeego-keyboard.so","en_gb.xml"]"
#gconftool-2 -s /meegotouch/inputmethods/onscreen/active --list-type=string -t list "["libmeego-keyboard.so","en_gb.xml"]"




#gconftool-2 -s /meegotouch/inputmethods/plugins/hardware -t string "libmeego-keyboard.so"
#gconftool-2 -u /meegotouch/inputmethods/plugins/onscreen

gconftool-2 -R /meegotouch/inputmethods

 #accessoryenabled = false
 #/meegotouch/inputmethods/virtualkeyboard:
  #layouts = [en_gb.xml]
  #correctwithspace = false
  #fuzzyselected = false
  #wordpredictionenabled = true
  #correctionenabled = true
  #/meegotouch/inputmethods/virtualkeyboard/layouts:
   #default = en_gb.xml
 #/meegotouch/inputmethods/multitouch:
  #enabled = false
 #/meegotouch/inputmethods/onscreen:
  #active = [libmeego-keyboard.so,en_gb.xml]
  #enabled = [libmeego-keyboard.so,en_gb.xml]
 #/meegotouch/inputmethods/plugins:
  #hardware = libmeego-keyboard.so
