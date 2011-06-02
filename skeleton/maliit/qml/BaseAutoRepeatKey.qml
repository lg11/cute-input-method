import Qt 4.7

BaseKey {
    id : key
    signal repeated
    property bool paused : false
    Timer {
        id : startTimer
        interval : 320
        repeat : false
        onTriggered : { paused = false ; repeated() ; repeatTimer.restart() }
    }
    Timer {
        id : repeatTimer
        interval : 40
        repeat : true
        onTriggered : { repeated() }
    }
    function pauseAutoRepeat() {
        paused = true
        repeatTimer.stop()
        startTimer.restart()
    }
    onMousePressed : { paused = false ; startTimer.restart() ; repeatTimer.stop() }
    onMouseReleased : { startTimer.stop() ; repeatTimer.stop() }
    onMouseExited : { startTimer.stop() ; repeatTimer.stop() }
}
