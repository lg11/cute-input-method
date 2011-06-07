import Qt 4.7

Item {
    property alias list : row.children
    property alias verticalMargin : id_candidateItem_0.verticalMargin
    property alias horizontalMargin : id_candidateItem_0.horizontalMargin
    property alias itemOffset : id_candidateItem_0.width
    width : list[0].width + list[1].width + list[2].width + list[3].width + list[4].width
    height : list[0].height
    clip : true
    /*width : 1050*/
    /*height : 600*/

    Row {
        id : row
        anchors.centerIn : parent
        CandidateItem { id : id_candidateItem_0 ; font.pointSize : 20 ; color : "#FF2299FF" }
        CandidateItem { id : id_candidateItem_1 ; font.pointSize : 20 ; color : "#FFFFFFFF" }
        CandidateItem { id : id_candidateItem_2 ; font.pointSize : 20 ; color : "#FFFFFFFF" }
        CandidateItem { id : id_candidateItem_3 ; font.pointSize : 20 ; color : "#FFFFFFFF" }
        CandidateItem { id : id_candidateItem_4 ; font.pointSize : 20 ; color : "#FFFFFFFF" }
    }

    Gradient {
        id : id_gradient
        GradientStop  { position: 0.00 ; color : "#00FFFFFF" }
        GradientStop  { position: 0.20 ; color : "#44FFFFFF" }
        GradientStop  { position: 0.50 ; color : "#AAFFFFFF" }
        GradientStop  { position: 0.80 ; color : "#44FFFFFF" }
        GradientStop  { position: 1.00 ; color : "#00FFFFFF" }
    }

    Rectangle {
        /*anchors.verticalCenter : parent.verticalCenter*/
        x : id_candidateItem_0.x + id_candidateItem_0.width - 1
        y : -( parent.height * 3 )
        width : list[0].width > 0 && list[1].width > 0  ? 2 : 0
        height : parent.height * 4
        gradient : id_gradient
    }
    Rectangle {
        /*anchors.verticalCenter : parent.verticalCenter*/
        x : id_candidateItem_1.x + id_candidateItem_1.width - 1
        y : -( parent.height * 3 )
        width : list[1].width > 0 && list[2].width > 0  ? 2 : 0
        height : parent.height * 4
        gradient : id_gradient
    }
    Rectangle {
        /*anchors.verticalCenter : parent.verticalCenter*/
        x : id_candidateItem_2.x + id_candidateItem_2.width - 1
        y : -( parent.height * 3 )
        width : list[2].width > 0 && list[3].width > 0  ? 2 : 0
        height : parent.height * 4
        gradient : id_gradient
    }
    Rectangle {
        /*anchors.verticalCenter : parent.verticalCenter*/
        x : id_candidateItem_3.x + id_candidateItem_3.width - 1
        y : -( parent.height * 3 )
        width : list[3].width > 0 && list[4].width > 0  ? 2 : 0
        height : parent.height * 4
        gradient : id_gradient
    }

}

