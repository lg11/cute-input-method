import Qt 4.7

Flickable {
    id : view

    width : 300
    height : 200
    contentWidth : edit.paintedWidth
    contentHeight : edit.paintedHeight
    clip : true
    boundsBehavior : Flickable.StopAtBounds
    /*property string text*/

    function ensureVisible( r ) {
        if ( contentX >= r.x )
            contentX = r.x ;
        else if ( contentX+width <= r.x + r.width )
            contentX = r.x + r.width - width ;
        if ( contentY >= r.y )
            contentY = r.y ;
        else if ( contentY+height <= r.y + r.height )
            contentY = r.y + r.height - height ;
    }
    function insert( s ) {
        var head = edit.text.slice( 0, edit.cursorPosition )
        var tail = edit.text.slice( edit.cursorPosition )
        var pos = edit.cursorPosition
        edit.text = head.concat( s, tail )
        edit.cursorPosition = pos + s.length
    }

    TextEdit {
        id : edit
        width : view.width
        height : view.height
        focus : true
        activeFocusOnPress : false
        wrapMode : TextEdit.Wrap
        onCursorRectangleChanged : ensureVisible(cursorRectangle)
    }
}
