#include "message.h"

static void check_connect( DBusConnection** connection ) {
    if ( !(*connection) ) {
        DBusError error ;
        dbus_error_init( &error ) ;
        *connection = dbus_bus_get( DBUS_BUS_SESSION, &error ) ;
    }
}

void emit_sendMessage( DBusConnection** connection, char* message ) {
    check_connect( connection ) ;

    DBusMessage* signal = dbus_message_new_signal( "/context", "inputmethod.context", "sendMessage" ) ;
    dbus_message_append_args( signal, DBUS_TYPE_STRING, &message, DBUS_TYPE_INVALID ) ;
    dbus_connection_send( *connection, signal, 0 ) ;
    
    dbus_message_unref( signal ) ;
}

void emit_focusIn( DBusConnection** connection ) {
    check_connect( connection ) ;

    DBusMessage* signal = dbus_message_new_signal( "/context", "inputmethod.context", "focusIn" ) ;
    dbus_connection_send( *connection, signal, 0 ) ;
    
    dbus_message_unref( signal ) ;
}

void emit_focusOut( DBusConnection** connection ) {
    check_connect( connection ) ;

    DBusMessage* signal = dbus_message_new_signal( "/context", "inputmethod.context", "focusOut" ) ;
    dbus_connection_send( *connection, signal, 0 ) ;
    
    dbus_message_unref( signal ) ;
}

void emit_cursorRectUpdate( DBusConnection** connection, int x, int y, int width, int height ) {
    check_connect( connection ) ;

    DBusMessage* signal = dbus_message_new_signal( "/context", "inputmethod.context", "cursorRectUpdate" ) ;
    dbus_message_append_args( signal, DBUS_TYPE_INT32, &x, DBUS_TYPE_INT32, &y, DBUS_TYPE_INT32, &width, DBUS_TYPE_INT32, &height, DBUS_TYPE_INVALID ) ;
    dbus_connection_send( *connection, signal, 0 ) ;
    
    dbus_message_unref( signal ) ;
}

gboolean call_keyPress( DBusConnection** connection, int keycode , int modifiers ) {
    check_connect( connection ) ;

    DBusMessage* method = dbus_message_new_method_call( "me.inputmethod.host", "/host", "inputmethod.host", "keyPress" ) ;
    dbus_message_append_args( method, DBUS_TYPE_INT32, &keycode, DBUS_TYPE_INT32, &modifiers, DBUS_TYPE_INVALID ) ;


    DBusError error ;
    dbus_error_init( &error ) ;
    
    DBusMessage* reply = dbus_connection_send_with_reply_and_block( *connection, method, -1, &error ) ;

    gboolean flag = ( reply != NULL ) ;
    g_debug( "%d", flag ) ;
    if ( flag ) {
        g_debug( "%d", flag ) ;
        dbus_error_init( &error ) ;
        dbus_message_get_args( reply, &error, DBUS_TYPE_BOOLEAN, &flag, DBUS_TYPE_INVALID ) ;
        dbus_message_unref( reply ) ;
    }
    
    dbus_message_unref( method ) ;

    return flag ;
}
