import Qt 4.7

Key {
    id : key
    signal repeated
    Timer {
        id : startTimer
        interval : 350
        repeat : false
        onTriggered : { repeated() ; repeatTimer.restart() }
    }
    Timer {
        id : repeatTimer
        interval : 50
        repeat : true
        onTriggered : { repeated() }
    }
    onMousePressed : { startTimer.restart() }
    onMouseReleased : { startTimer.stop() ; repeatTimer.stop() }
    onMouseExited : { startTimer.stop() ; repeatTimer.stop() }
    /*onRepeated : { console.log("r") }*/
}
