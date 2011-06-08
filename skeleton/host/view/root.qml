import Qt 4.7

Item {
    id : root
    width : view.displayWidth
    height : view.displayHeight

    Rectangle {
        id : canvas
        anchors.fill : parent 
        color: "#06FF0000"
        PreeditPanel {
            id : preeditPanel
            x : view.cursorRect.x < 0 ? 0 : view.cursorRect.x + width > view.displayWidth ? view.displayWidth - width : view.cursorRect.x
            y : view.cursorRect.y + view.cursorRect.height + 6
        }
    }

    Connections {
        target : view
        onCandidateUpdate : {
            var flag = true
            flag = engine.updateCandidate( 0 )
            if ( engine.getCodeLength() > 0 ) {
                preeditPanel.preedit.selectedWord.text = engine.getSelectedWord()
                preeditPanel.preedit.preeditCode.text = engine.getPreeditCode()
                preeditPanel.preedit.invalidCode.text = engine.getInvalidCode()
            }
            else {
                preeditPanel.preedit.selectedWord.text = ""
                preeditPanel.preedit.preeditCode.text = ""
                preeditPanel.preedit.invalidCode.text = ""
            }
            if ( flag ) 
                preeditPanel.candidate.list[0].text = engine.getWord()
            else 
                preeditPanel.candidate.list[0].text = ""
            for ( var i = 1 ; i < 5 ; i++ ) {
                if ( flag )
                    flag = engine.updateCandidate( i ) 
                if ( flag )
                    preeditPanel.candidate.list[i].text = engine.getWord()
                else
                    preeditPanel.candidate.list[i].text = ""
            }
        }
    }
}
