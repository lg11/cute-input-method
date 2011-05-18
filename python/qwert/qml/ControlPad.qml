import Qt 4.7

RealMouseArea {
    width : 800 ; height : 400 ;
    property int keyWidth : 115
    property int keyHeight : 95
    property int mode : 0
    property Item textview : tView
    property string clipedString : ""
    Rectangle {
        anchors.fill : parent
        color : "#FFFFFFFF"
    }
    TextView {
        id : tView
        width : 600 ; height : 140 ;
    }

    Palette { id : palette }

    function move( pos ) {
        if ( mode == 0 )
            textview.moveTo( pos )
        else if ( mode == 1 )
            textview.selectTo( pos )
    }
    Column {
        id : controlPad
        y : 150
        Row {
            BaseAutoRepeatKey {
                id : key_left ; text : "l" ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor 
                onMouseReleased : {
                    move( textview.left() )
                }
                onRepeated : {
                    move( textview.left() )
                }
            }
            BaseAutoRepeatKey {
                id : key_up ; text : "u" ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor 
                onMouseReleased : {
                    move( textview.up() )
                }
                onRepeated : {
                    move( textview.up() )
                }
            }
            BaseAutoRepeatKey {
                id : key_right ; text : "r" ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor
                onMouseReleased : {
                    move( textview.right() )
                }
                onRepeated : {
                    move( textview.right() )
                }
            }
        }
        Row {
            BaseKey {
                id : key_select_copy ; text : "select" ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor 
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
                id : key_down ; text : "d" ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor
                onMouseReleased : {
                    move( textview.down() )
                }
                onRepeated : {
                    move( textview.down() )
                }
            }
            BaseKey {
                id : key_paste_cut ; text : "paste" ; width : keyWidth ; height : keyHeight ; color : palette.keyNormalColor 
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

    Component.onCompleted : {
        textview.set( "fhdjeuwzisjfdhsjgfjdk\n fhdjeuwzisjfdhsjgfjdk fhdjeuwzisjfdhsjgfjdk fhdje\nuwzisjfdhsjgfjdk fhdjeuwzisjfdhsjgfjdk fhdjeuwzisjfdhsjgfjdk fhdjeuwzisjfdhsjgfjdk\n fhdjeuwzisjfdhsjgfjdk fhdjeuwzisjfdhsjgfjdk fhdjeuwzisjfdhsjgfjdk fhdjeuwzisjfdhsjgfjdk fhdjeuwzisjfdhsjgfjdk " )
    }
}


