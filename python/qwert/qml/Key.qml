import Qt 4.7
/*import Qt.labs.gestures 1.0*/
import "utils.js" as Utils

BaseKey {
    id : key
    property int keycode : 0
    text : Utils.keysym[keyboard.mode][keycode][keyboard.mask]

    onMousePressed : { keyboard.keyPress( key ) }
    onMouseReleased : { keyboard.keyRelease( key ) }
    onMouseEntered : { keyboard.keyEnter( key ) }
    onMouseExited : { keyboard.keyExit( key ) }
}
