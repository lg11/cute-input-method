import Qt 4.7 

Item {
    property alias list : id_row
    property alias selectedWord : id_selectedWord
    property alias preeditCode : id_preeditCode
    property alias invalidCode : id_invalidCode
    property alias verticalMargin : id_selectedWord.verticalMargin
    property alias horizontalMargin : id_selectedWord.horizontalMargin
    property alias offset : id_row.x
    width : list.children[0].width + list.children[1].width + list.children[2].width > 0 ? list.children[0].width + list.children[1].width + list.children[2].width + offset * 2 : 0
    height : list.children[0].height > list.children[1].height ? list.children[0].height > list.children[2].height ? list.children[0].height : list.children[2].height : list.children[1].height > list.children[2].height ? list.children[1].height : list.children[2].height 

    Row {
        id : id_row
        anchors.verticalCenter : parent.verticalCenter
        CandidateItem { id : id_selectedWord ; font.pointSize : 20 ; color : "#FFFFFFFF" ; horizontalMargin : verticalMargin }
        CandidateItem { id : id_preeditCode ; font.pointSize : 20 ; color : "#FFFFFFFF" ; horizontalMargin : verticalMargin }
        CandidateItem { id : id_invalidCode ; font.pointSize : 20 ; color : "#FFFF0000" ; horizontalMargin : verticalMargin }
    }
}
