import Qt 4.7

Rectangle {
    color : "#CC444444"
    property alias preedit : id_preedit
    property alias candidate : id_candidate
    width : preedit.width > candidate.width ? preedit.width > 0 ? preedit.width + candidate.verticalMargin : 0 : candidate.width > 0 ? candidate.width + candidate.verticalMargin : 0
    /*width : view.displayWidth*/
    height : preedit.height + candidate.height > 0 ? preedit.height + candidate.height + candidate.verticalMargin : 0
    radius : 8

    Column {
        anchors.centerIn : parent
        Preedit { id : id_preedit ; offset : ( id_candidate.horizontalMargin - id_preedit.horizontalMargin ) / 2 }
        /*Preedit { id : id_preedit ; offset : 0*/
            /*anchors.horizontalCenter : parent.horizontalCenter*/
        /*}*/
        Candidate { id : id_candidate }
    }

    Gradient {
        id : id_gradient
        GradientStop  { position: 0.00 ; color : "#AAFFFFFF" }
        GradientStop  { position: 0.40 ; color : "#44FFFFFF" }
        GradientStop  { position: 1.00 ; color : "#00FFFFFF" }
    }
    Rectangle {
        x : id_candidate.itemOffset / 5 * 3
        y : id_preedit.height + id_candidate.verticalMargin / 2 - 1
        width : id_preedit.height > 0 && id_candidate.height > 0 ? 2 : 0 
        height : x - candidate.verticalMargin
        gradient : id_gradient
        transformOrigin : Item.Top
        rotation : 90
    }
    Rectangle {
        x : id_candidate.itemOffset / 5 * 3
        y : id_preedit.height + id_candidate.verticalMargin / 2 - 1
        width : id_preedit.height > 0 && id_candidate.height > 0 ? 2 : 0 
        height : parent.width - x - candidate.verticalMargin
        gradient : id_gradient
        transformOrigin : Item.Top
        rotation : 270
    }
}
