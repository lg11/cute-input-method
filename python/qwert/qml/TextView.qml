import Qt 4.7

Item {
    id : view
    clip : true
    property alias contentWidth : edit.paintedWidth
    property alias contentHeight : edit.paintedHeight
    property alias contentX : edit.x
    property alias contentY : edit.y
    property int selectionEndPos
    property int selectionBeginPos

    function ensureVisible( r ) {
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
    }
    function insert( s ) {
        if ( s.length > 0 ) {
            var head = edit.text.slice( 0, edit.cursorPosition )
            var tail = edit.text.slice( edit.cursorPosition )
            var pos = edit.cursorPosition
            edit.text = head.concat( s, tail )
            edit.cursorPosition = pos + s.length
        }
    }
    function remove( start, end ) {
        if ( start != end ) {
            var head = edit.text.slice( 0, start )
            var tail = edit.text.slice( end )
            edit.text = head.concat( tail )
            edit.cursorPosition = start
        }
    }
    function backspace() {
        if ( edit.text.length > 0 ) { 
            if ( edit.cursorPosition > 0 )
                remove( edit.cursorPosition - 1, edit.cursorPosition )
            else if ( edit.cursorPosition < edit.text.length )
                remove( edit.cursorPosition, edit.cursorPosition + 1 )
        }
    }
    function up() {
        var y = edit.cursorRectangle.y - edit.cursorRectangle.height / 2
        var pos = edit.positionAt( edit.cursorRectangle.x, y )
        return pos
    }
    function down() {
        var y = edit.cursorRectangle.y + edit.cursorRectangle.height + edit.cursorRectangle.height / 2
        var pos = edit.positionAt( edit.cursorRectangle.x, y )
        return pos
    }
    function left() {
        var pos = 0
        if ( edit.cursorPosition > 0 )
            pos = edit.cursorPosition - 1
        return pos
    }
    function right() {
        var pos = edit.text.length
        if ( edit.cursorPosition < pos )
            pos = edit.cursorPosition + 1
        return pos
    }
    function moveTo( pos ) {
        edit.cursorPosition = pos
    }
    function setSelectionBlock() {
        var upRect
        var downRect
        if ( selectionBeginPos == selectionEndPos ) {
            selectionBeginBlock.visible = false
            selectionMainBlock.visible = false
            selectionEndBlock.visible = false
            cursor.visible = true
        }
        else {
            cursor.visible = false
            if ( selectionBeginPos < selectionEndPos ) {
                upRect = edit.positionToRectangle( selectionBeginPos )
                downRect = edit.positionToRectangle( selectionEndPos )
            }
            else {
                upRect = edit.positionToRectangle( selectionEndPos )
                downRect = edit.positionToRectangle( selectionBeginPos )
            }
            if ( upRect.y == downRect.y ) {
                selectionBeginBlock.visible = false
                selectionMainBlock.visible = true
                selectionEndBlock.visible = false
                selectionMainBlock.x = upRect.x
                selectionMainBlock.y = upRect.y + contentY
                selectionMainBlock.width = downRect.x - upRect.x
                selectionMainBlock.height = upRect.height
            }
            else {
                selectionBeginBlock.visible = true
                selectionMainBlock.visible = true
                selectionEndBlock.visible = true
                selectionBeginBlock.x = upRect.x
                selectionBeginBlock.y = upRect.y + contentY
                selectionBeginBlock.width = view.width - upRect.x
                selectionBeginBlock.height = upRect.height
                selectionEndBlock.x = 0
                selectionEndBlock.y = downRect.y + contentY
                selectionEndBlock.width = downRect.x + downRect.width
                selectionEndBlock.height = upRect.height
                selectionMainBlock.x = 0
                selectionMainBlock.y = upRect.y + upRect.height + contentY
                selectionMainBlock.width = view.width
                selectionMainBlock.height = downRect.y - upRect.y - upRect.height
            }
        }
    }
    function getSelectedString() {
        var startIndex
        var endIndex
        if ( selectionBeginPos <= selectionEndPos ) {
            startIndex = selectionBeginPos
            endIndex = selectionEndPos
        }
        else {
            startIndex = selectionEndPos
            endIndex = selectionBeginPos
        }
        return edit.text.slice( startIndex, endIndex )
    }
    function setSelectedString( s ) {
        var start
        var end
        if ( selectionBeginPos <= selectionEndPos ) {
            start = selectionBeginPos
            end = selectionEndPos
        }
        else {
            start = selectionEndPos
            end = selectionBeginPos
        }
        remove( start, end )
        insert( s )
    }
    function selectStart() {
        selectionBeginPos = edit.cursorPosition
        selectionEndPos = edit.cursorPosition
        setSelectionBlock()
    }
    function selectEnd() {
        edit.cursorPosition = selectionEndPos 
        selectionBeginPos = edit.cursorPosition
        selectionEndPos = edit.cursorPosition
        setSelectionBlock()
    }
    function selectTo( pos ) {
        selectionEndPos = pos
        edit.cursorPosition = selectionEndPos 
        setSelectionBlock()
    }
    function set( text ) {
        edit.text = text
        edit.cursorPosition = text.length
    }
    function get() {
        return edit.text
    }

    Rectangle {
        id : selectionBeginBlock
        color : palette.textviewSelectionColor
        visible : false
    }
    Rectangle {
        id : selectionMainBlock
        color : palette.textviewSelectionColor
        visible : false
    }
    Rectangle {
        id : selectionEndBlock
        color : palette.textviewSelectionColor
        visible : false
    }
    Rectangle {
        id : cursor
        x : edit.cursorRectangle.x
        y : edit.cursorRectangle.y + contentY
        width : 4
        height : edit.cursorRectangle.height
        color : palette.textviewCursorColor
    }
    TextEdit {
        id : edit
        width : view.width
        height : view.height
        focus : false
        readOnly : true
        cursorVisible : false
        font.pointSize: 22
        activeFocusOnPress : false
        wrapMode : TextEdit.Wrap
        selectedTextColor : "#FFFFFFFF"
        selectionColor : palette.textviewSelectionColor
        onCursorRectangleChanged : ensureVisible( cursorRectangle )
    }
}
