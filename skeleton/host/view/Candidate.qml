import Qt 4.7

Rectangle {
    color : "#FF444444"
    property alias list : row
    width : list.children[0].width + list.children[1].width + list.children[2].width + list.children[3].width + list.children[4].width
    height : list.children[0].height
    /*width : 1050*/
    /*height : 600*/

    Row {
        id : row
        anchors.centerIn : parent
        CandidateItem {}
        CandidateItem {}
        CandidateItem {}
        CandidateItem {}
        CandidateItem {}
    }
}

