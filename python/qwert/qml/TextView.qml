import Qt 4.7

FakeMouseArea {
    id : view
    property alias contentWidth : edit.paintedWidth
    property alias contentHeight : edit.paintedHeight
    property alias contentX : edit.x
    property alias contentY : edit.y

    Rectangle {
        anchors.fill : parent
        color : "#FFFFFFFF"
    }

    function ensureVisible( r ) {
        if ( !down ) {
            /*console.log( "start", contentY, r.y )*/
            if ( -contentX >= r.x )
                contentX = -r.x ;
            else if ( contentX + width <= r.x + r.width )
                contentX = -( r.x + r.width - width ) ;
            if ( -contentY >= r.y )
                contentY = -r.y ;
            else if ( contentY + height <= r.y + r.height )
                contentY = -( r.y + r.height - height ) ;
            if ( contentX > 0 )
                contentX = 0
            if ( contentY > 0 )
                contentY = 0
            /*console.log( "end", contentY, r.y )*/
        }
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

    TextEdit {
        id : edit
        width : view.width
        height : view.height
        /*focus : true*/
        focus : false
        readOnly : true
        cursorVisible : false
        font.pointSize: 24
        activeFocusOnPress : false
        wrapMode : TextEdit.Wrap
        /*selectByMouse : true*/
        /*selectionColor : palette.keyDownColor*/
        onCursorRectangleChanged : ensureVisible( cursorRectangle )
        Rectangle {
            id : course
            x : edit.cursorRectangle.x
            y : edit.cursorRectangle.y
            width : 4
            height : edit.cursorRectangle.height
            color : palette.textviewCursorColor
        }
    }
    property real startY
    property real startContentY
    onMousePressed : {
        startY = y
        startContentY = contentY
    }
    function mouseMove( x, y ) {
        var dy = y - startY
        contentY = startContentY + dy 
        var editPos = mapToItem( edit, x, y )
        var pos = edit.positionAt( editPos.x, editPos.y )
        edit.cursorPosition = pos
    }
    onMouseMoved : {
        mouseMove( x, y )
    }
    onMouseExited : {
        mouseMove( x, y )
        ensureVisible( edit.cursorRectangle )
    }
    onMouseReleased : {
        mouseMove( x, y )
        ensureVisible( edit.cursorRectangle )
    }
}
