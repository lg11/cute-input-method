import Qt 4.7

Key {
    id : key
    property alias candString : candText.text
    property bool isActive : false

    Text {
        id : candText
        anchors.centerIn : parent
        color : "#FFFFFFFF"
        font.pointSize: 24; font.bold: false
    }

    states {
        State {
            name : "CAND" ; when : candString != ""
            PropertyChanges { target : key ; titleVisible : false }
        } 
    }
}
