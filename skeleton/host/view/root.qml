import Qt 4.7

Item {
    id : root
    width : view.displayWidth
    height : view.displayHeight

    Rectangle {
        id : canvas
        anchors.fill : parent 
        color: "#00FF0000"
        Candidate {
            id : candidate
            x : view.cursorRect.x
            y : view.cursorRect.y
        }
    }

    Connections {
        target : view
        onCandidateUpdate : {
            var flag = true
            for ( var i = 0 ; i < 5 ; i++ ) {
                if ( flag )
                    flag = engine.updateCandidate( i ) 
                if ( flag )
                    candidate.list.children[i].text = engine.getWord()
                else
                    candidate.list.children[i].text = ""
            }
        }
    }
}
