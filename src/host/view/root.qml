import Qt 4.7

Item {
    id : root
    width : view.displayWidth
    height : view.displayHeight


    Rectangle {
        id : canvas
        anchors.fill : parent 
        color: "#00FF0000"

        SelectPanel {
            id : id_selectPanel
            anchors.horizontalCenter : parent.horizontalCenter
            anchors.bottom : parent.bottom
            width : view.displayWidth
            height : view.displayHeight
            onSelect : handle.processKeyPress( Qt.Key_1 + index )
            onNextPage : handle.processKeyPress( Qt.Key_Equal )
            onPrevPage : handle.processKeyPress( Qt.Key_Minus )
            visible : false
        }

        PreeditPanel {
            id : id_preeditPanel
            x : 0
            y : ( view.displayHeight - height ) / 2
            /*x : view.cursorRect.x < 0 ? 0 : view.cursorRect.x + width > view.displayWidth ? view.displayWidth - width : view.cursorRect.x*/
            /*y : view.cursorRect.y < 0 ? 0 : view.cursorRect.y + view.cursorRect.height + height > view.displayHeight ? view.displayHeight - height : view.cursorRect.y + view.cursorRect.height*/
            onHeightChanged : {
                if ( height > 0 ) {
                    view.addInputRegion( Qt.rect( id_selectPanel.x, id_selectPanel.y, id_selectPanel.width, id_selectPanel.height ) )
                    id_selectPanel.visible = true
                }
                else {
                    view.clearInputRegion()
                    id_selectPanel.visible = false
                }
            }
        }
    }

    /*Connections {*/
        /*target : engine*/
        /*onPreeditStart : {*/
            /*view.addInputRegion( Qt.rect( id_selectPanel.x, id_selectPanel.y, id_selectPanel.width, id_selectPanel.height ) )*/
            /*id_selectPanel.visible = true*/
        /*}*/
        /*onPreeditEnd : {*/
            /*view.clearInputRegion()*/
            /*id_selectPanel.visible = false*/
        /*}*/
    /*}*/
    Connections {
        target : view
        onCandidateUpdate : {
            var flag = true
            flag = engine.updateCandidate( 0 )
            if ( engine.getCodeLength() > 0 ) {
                id_preeditPanel.preedit.selectedWord.text = engine.getSelectedWord()
                id_preeditPanel.preedit.preeditCode.text = engine.getPreeditCode()
                id_preeditPanel.preedit.invalidCode.text = engine.getInvalidCode()
            }
            else {
                id_preeditPanel.preedit.selectedWord.text = ""
                id_preeditPanel.preedit.preeditCode.text = ""
                id_preeditPanel.preedit.invalidCode.text = ""
            }
            if ( flag ) 
                id_preeditPanel.candidate.list[0].text = engine.getWord()
            else 
                id_preeditPanel.candidate.list[0].text = ""
            for ( var i = 1 ; i < 5 ; i++ ) {
                if ( flag )
                    flag = engine.updateCandidate( i ) 
                if ( flag )
                    id_preeditPanel.candidate.list[i].text = engine.getWord()
                else
                    id_preeditPanel.candidate.list[i].text = ""
            }
        }
    }
}
