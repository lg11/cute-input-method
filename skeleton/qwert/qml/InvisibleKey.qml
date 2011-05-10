import Qt 4.7

MouseArea {
    /*id : key*/
    width : 80
    height : 80

    signal press
    signal release

    focus : false
    hoverEnabled : false
    onPressed : { press() }
    onReleased : { release() }
}
