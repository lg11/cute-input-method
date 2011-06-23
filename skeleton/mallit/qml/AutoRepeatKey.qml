import Qt 4.7

Key {
    id : key
    signal repeated
    property bool paused : false
    Timer {
        id : startTimer
        interval : 550
        repeat : false
        onTriggered : { paused = false ; repeated() ; repeatTimer.restart() }
    }
    Timer {
        id : repeatTimer
        interval : 50
        repeat : true
        onTriggered : { repeated() }
    }
    /*Timer {*/
        /*id : pauseTimer*/
        /*interval : 550*/
        /*repeat : false*/
        /*onTriggered : { repeated() ; repeatTimer.restart() ; paused = false }*/
    /*}*/
    function pauseAutoRepeat() {
        paused = true
        repeatTimer.stop()
        startTimer.restart()
    }
    onMousePressed : { paused = false ; startTimer.restart() ; repeatTimer.stop() }
    onMouseReleased : { startTimer.stop() ; repeatTimer.stop() }
    onMouseExited : { startTimer.stop() ; repeatTimer.stop() }
    /*onRepeated : { console.log("r") }*/
}
