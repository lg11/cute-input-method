import Qt 4.7

Item {
    property int keyWidth
    property int keyHeight
    property int mode : 0
    property Item textview
    property string clipedString : ""
    width : keyWidth * 3
    height : keyHeight * 2

    function move( pos ) {
        if ( mode == 0 )
            textview.moveTo( pos )
        else if ( mode == 1 )
            textview.selectTo( pos )
    }

    Column {
        id : controlPad
        Row {
            BaseKey {
                id : key_select_copy ; text : "select" ; width : keyWidth ; height : keyHeight ; color : palette.controlPadKeyNormalColor ; textColor : palette.controlPadKeyTextColor
                onMouseReleased : {
                    if ( mode == 0 ) {
                        mode = 1
                        textview.selectStart()
                    }
                    else if ( mode == 1 ) {
                        clipedString = textview.getSelectedString()
                        /*console.log( clipedString )*/
                        mode = 0
                        textview.selectEnd()
                    }
                }
            }
            BaseAutoRepeatKey {
                id : key_up ; text : "▲" ; width : keyWidth ; height : keyHeight ; color : palette.controlPadKeyNormalColor ; textColor : palette.controlPadKeyTextColor
                onMouseReleased : {
                    move( textview.up() )
                }
                onRepeated : {
                    move( textview.up() )
                }
            }
            BaseKey {
                id : key_paste_cut ; text : "paste" ; width : keyWidth ; height : keyHeight ; color : palette.controlPadKeyNormalColor ; textColor : palette.controlPadKeyTextColor
                onMouseReleased : {
                    if ( mode == 0 ) {
                        textview.insert( clipedString )
                    }
                    else if ( mode == 1 ) {
                        clipedString = textview.getSelectedString()
                        /*console.log( clipedString )*/
                        textview.setSelectedString( "" )
                        mode = 0
                        textview.selectEnd()
                    }
                }
            }
        }
        Row {
            BaseAutoRepeatKey {
                id : key_left ; text : "◄" ; width : keyWidth ; height : keyHeight ; color : palette.controlPadKeyNormalColor ; textColor : palette.controlPadKeyTextColor
                onMouseReleased : {
                    move( textview.left() )
                }
                onRepeated : {
                    move( textview.left() )
                }
            }
            BaseAutoRepeatKey {
                id : key_down ; text : "▼" ; width : keyWidth ; height : keyHeight ; color : palette.controlPadKeyNormalColor ; textColor : palette.controlPadKeyTextColor
                onMouseReleased : {
                    move( textview.down() )
                }
                onRepeated : {
                    move( textview.down() )
                }
            }
            BaseAutoRepeatKey {
                id : key_right ; text : "►" ; width : keyWidth ; height : keyHeight ; color : palette.controlPadKeyNormalColor ; textColor : palette.controlPadKeyTextColor
                onMouseReleased : {
                    move( textview.right() )
                }
                onRepeated : {
                    move( textview.right() )
                }
            }
        }
    }
    states {
        State {
            name : "NORMALMODE" ; when : mode == 0
        } 
        State {
            name : "SELECTMODE" ; when : mode == 1
            PropertyChanges { target : key_select_copy ; text : "copy" }
            PropertyChanges { target : key_paste_cut ; text : "cut" }
        } 
    }

    /*Component.onCompleted : {*/
    /*}*/
}


