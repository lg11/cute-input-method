import Qt 4.7

Flickable {
    id : view

    width : 300
    height : 200
    contentWidth : edit.paintedWidth
    contentHeight : edit.paintedHeight
    clip : true
    boundsBehavior : Flickable.StopAtBounds
    property real keepLines : 0

    /*property alias text : edit.text*/

    function ensureVisible( r ) {
        /*console.log( "start", contentX, contentY, r.x, r.y )*/
        if ( contentX >= r.x )
            contentX = r.x ;
        else if ( contentX + width <= r.x + r.width )
            contentX = r.x + r.width - width ;
        if ( contentY >= r.y )
            contentY = r.y ;
        /*else if ( contentY + height - r.height * keepLines <= r.y + r.height )*/
            /*contentY = r.y + r.height - height + r.height * keepLines ;*/
        else if ( contentY + height <= r.y + r.height )
            contentY = r.y + r.height - height ;
        /*console.log( "end", contentX, contentY, r.x, r.y )*/
    }
    function ensureCenter( r ) {
        /*console.log( "start", contentX, contentY, r.x, r.y )*/
        if ( contentX >= r.x )
            contentX = r.x ;
        else if ( contentX + width <= r.x + r.width )
            contentX = r.x + r.width - width ;
        contentY = r.y + r.height - height + height * 0.5 - r.height * 0.5 ;
        /*console.log( "end", contentX, contentY, r.x, r.y )*/
    }
    function insert( s ) {
        var head = edit.text.slice( 0, edit.cursorPosition )
        var tail = edit.text.slice( edit.cursorPosition )
        var pos = edit.cursorPosition
        edit.text = head.concat( s, tail )
        edit.cursorPosition = pos + s.length
    }
    function backspace() {
        if ( edit.text.length > 0 ) { 
            var head = edit.text.slice( 0, edit.cursorPosition )
            var tail = edit.text.slice( edit.cursorPosition )
            var pos = edit.cursorPosition
            if ( head.length > 0 ) {
                head = head.slice( 0, head.length - 1 )
                pos--
            }
            else {
                tail = tail.slice( 1, tail.length )
            }
            edit.text = head.concat( tail )
            edit.cursorPosition = pos
        }
    }
    function set( text ) {
        edit.text = text
        edit.cursorPosition = text.length
    }
    function get() {
        return edit.text
    }

    Rectangle {
        id : course
        x : edit.cursorRectangle.x
        y : edit.cursorRectangle.y
        width : 4
        height : edit.cursorRectangle.height
        color : palette.textviewCursorColor
    }

    TextEdit {
        id : edit
        width : view.width
        height : view.height
        /*focus : true*/
        readOnly : true
        font.pointSize: 22
        activeFocusOnPress : false
        wrapMode : TextEdit.Wrap
        /*selectByMouse : true*/
        /*selectionColor : palette.keyDownColor*/
        onCursorRectangleChanged : ensureVisible( cursorRectangle )
        /*onCursorPositionChanged : ensureVisible( cursorRectangle )*/
        /*onCursorRectangleChanged : ensureCenter( cursorRectangle )*/
        /*onCursorPositionChanged : ensureCenter( cursorRectangle )*/
    }
    /*onMovementEnded : ensureVisible( edit.cursorRectangle )*/
}
