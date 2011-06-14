import Qt 4.7

Item {
    signal select(int index)
    signal prevPage
    signal nextPage
    Row {
        anchors.horizontalCenter : parent.horizontalCenter
        x : 0
        y : 0
        width : parent.width
        height : parent.height / 3 * 2
        SelectRect {
            stopColor : "#00FF0000"
            startColor : "#00FFFFFF"
            width : parent.width / 2
            height : parent.height
            onPress : { prevPage() }
        }
        SelectRect {
            stopColor : "#00FF0000"
            startColor : "#00FFFFFF"
            width : parent.width / 2
            height : parent.height
            onPress : { nextPage() }
        }
    }
    Row {
        anchors.horizontalCenter : parent.horizontalCenter
        x : 0
        y : parent.height / 3 * 2
        width : parent.width
        height : parent.height / 3 
        SelectRect {
            stopColor : "#BB2299FF"
            startColor : "#002299FF"
            width : parent.width / 5
            height : parent.height
            onPress : { select(0) }
        }
        SelectRect {
            stopColor : "#00FFFFFF"
            startColor : "#00FFFFFF"
            width : parent.width / 5
            height : parent.height
            onPress : { select(1) }
        }
        SelectRect {
            stopColor : "#66444444"
            startColor : "#00444444"
            width : parent.width / 5
            height : parent.height
            onPress : { select(2) }
        }
        SelectRect {
            stopColor : "#00FFFFFF"
            startColor : "#00FFFFFF"
            width : parent.width / 5
            height : parent.height
            onPress : { select(3) }
        }
        SelectRect {
            stopColor : "#66444444"
            startColor : "#00444444"
            width : parent.width / 5
            height : parent.height
            onPress : { select(4) }
        }
    }
}
