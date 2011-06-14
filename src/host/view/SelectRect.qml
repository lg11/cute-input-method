import Qt 4.7

Item {
    property color stopColor
    property color startColor
    signal press
    MouseArea {
        anchors.fill : parent
        onPressed : press()
    }
    Rectangle {
        id : id_plat
        anchors.fill : parent
        gradient : id_gradient
    }
    Gradient {
        id : id_gradient
        GradientStop  { position: 0.00 ; color : startColor }
        GradientStop  { position: 1.00 ; color : stopColor }
    }
}

