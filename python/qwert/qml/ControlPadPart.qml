import Qt 4.7

Item {
    id : part
    x : 0 ; y : 0
    clip : true
    property alias keyWidth : pad.keyWidth
    property alias keyHeight : pad.keyHeight
    property alias textview : pad.textview
    property alias mode : pad.mode
    property alias padX : pad.x
    property int stateFlag : 0
    property int textviewHeight

    FakeMouseArea {
        anchors.fill : parent
        onMouseReleased : stateFlag = 0
    }
    ControlPad {
        id : pad
        y : textviewHeight
    }

    states {
        State {
            name : "HIDE" ; when : stateFlag == 0
            PropertyChanges {
                target : part
                width : 0
                height : 0
            }
        } 
        State {
            name : "SHOW" ; when : stateFlag == 1
            PropertyChanges {
                target : part
                width : parent.width
                height : parent.width
            }
        } 
    }
}
