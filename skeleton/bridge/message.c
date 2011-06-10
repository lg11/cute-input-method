#include "message.h"
#include "context.h"

/*static int count_utf8_characters( char* s ) {*/
    /*int i = 0, j = 0 ;*/
    /*while ( s[i] ) {*/
        /*if ( ( s[i] & 0xc0 ) != 0x80 )*/
            /*j++ ;*/
        /*i++ ;*/
    /*}*/
    /*return j ;*/
/*}*/

static gboolean send_surrounding( void* data ) {
    Context* c = CONTEXT(data) ;
    if ( c->surrounding )
        emit_sendSurrounding( &(c->connection), c->surrounding ) ;
    else
        emit_sendSurrounding( &(c->connection), "" ) ;
    return FALSE ;
}

static gboolean query_surrounding( Context* c ) {
    int pos ;
    gboolean r ;

    if ( c->surrounding )
        g_free( c->surrounding ) ;
    r = gtk_im_context_get_surrounding( GTK_IM_CONTEXT(c), &(c->surrounding), &pos ) ;
    
    if ( r ) {
        int len = g_utf8_strlen( c->surrounding, -1 ) ; 
        if ( len > 0 ) {
            char* str = &(c->surrounding[pos]) ;
            char* start = c->surrounding ;
            char* end = str ;
            for ( ; end[0] != '\0' ; end++ ) ;

            int offset_start ;
            int offset_end ;
            if ( end - start >= 0 ) {
                offset_start = str - start ;
                offset_end = end - start ;
            }
            
            gtk_im_context_delete_surrounding( GTK_IM_CONTEXT(c), -offset_start, offset_end ) ;

            c->prepare_send_surrounding = TRUE ;
        }
        else
            r = FALSE ;
    }
    return r ;
}

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

void emit_sendSurrounding( DBusConnection** connection, char* surrounding ) {
    check_connect( connection ) ;

    DBusMessage* signal = dbus_message_new_signal( "/context", "inputmethod.context", "sendSurrounding" ) ;
    dbus_message_append_args( signal, DBUS_TYPE_STRING, &surrounding, DBUS_TYPE_INVALID ) ;
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
    if ( flag ) {
        dbus_error_init( &error ) ;
        dbus_message_get_args( reply, &error, DBUS_TYPE_BOOLEAN, &flag, DBUS_TYPE_INVALID ) ;
        dbus_message_unref( reply ) ;
    }
    
    dbus_message_unref( method ) ;

    return flag ;
}

gboolean call_keyRelease( DBusConnection** connection, int keycode , int modifiers ) {
    check_connect( connection ) ;

    DBusMessage* method = dbus_message_new_method_call( "me.inputmethod.host", "/host", "inputmethod.host", "keyRelease" ) ;
    dbus_message_append_args( method, DBUS_TYPE_INT32, &keycode, DBUS_TYPE_INT32, &modifiers, DBUS_TYPE_INVALID ) ;


    DBusError error ;
    dbus_error_init( &error ) ;
    
    DBusMessage* reply = dbus_connection_send_with_reply_and_block( *connection, method, -1, &error ) ;

    gboolean flag = ( reply != NULL ) ;
    if ( flag ) {
        dbus_error_init( &error ) ;
        dbus_message_get_args( reply, &error, DBUS_TYPE_BOOLEAN, &flag, DBUS_TYPE_INVALID ) ;
        dbus_message_unref( reply ) ;
    }
    
    dbus_message_unref( method ) ;

    return flag ;
}

DBusHandlerResult filter( DBusConnection* connection, DBusMessage* message, void* data ) {
    /*g_debug( "filter %s", dbus_message_get_member( message ) ) ;*/
    Context* c = CONTEXT(data) ;
    if ( c->focused ) {
        if ( dbus_message_is_signal( message, "inputmethod.host", "sendCommit" ) ) {
            char* s ;
            DBusError error ;
            dbus_error_init( &error ) ;
            dbus_message_get_args( message, &error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID ) ;
            g_signal_emit_by_name( c, "commit", s ) ;
            /*dbus_free( s ) ;*/
            return DBUS_HANDLER_RESULT_HANDLED ;
        }
        else if ( dbus_message_is_signal( message, "inputmethod.host", "sendMessage" ) ) {
            char* s ;
            DBusError error ;
            dbus_error_init( &error ) ;
            dbus_message_get_args( message, &error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID ) ;
            g_debug( "received %s", s ) ;
            /*dbus_free( s ) ;*/
            return DBUS_HANDLER_RESULT_HANDLED ;
        }
        else if ( dbus_message_is_signal( message, "inputmethod.host", "queryCursorRect" ) ) {
            emit_cursorRectUpdate( &(c->connection), c->cursorRect.x, c->cursorRect.y, c->cursorRect.width, c->cursorRect.height ) ;
            return DBUS_HANDLER_RESULT_HANDLED ;
        }
        else if ( dbus_message_is_signal( message, "inputmethod.host", "querySurrounding" ) ) {
            gboolean r = query_surrounding( c ) ;
            if ( !r ) 
                gtk_idle_add( send_surrounding, c ) ;
            return DBUS_HANDLER_RESULT_HANDLED ;
        }
        else if ( dbus_message_is_signal( message, "inputmethod.host", "replaceSurrounding" ) ) {
            g_debug( "replaceSurrounding" ) ;
            char* s ;
            DBusError error ;
            dbus_error_init( &error ) ;
            dbus_message_get_args( message, &error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID ) ;
            g_signal_emit_by_name( c, "commit", s ) ;
            return DBUS_HANDLER_RESULT_HANDLED ;
        }
    }

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED ;
}

void request_connect( DBusConnection** connection, GObject* object ) {
    check_connect( connection ) ;
    dbus_connection_setup_with_g_main( *connection, NULL ) ;
    dbus_bus_add_match( *connection, "type='signal',interface='inputmethod.host',member='sendCommit',path='/host'", NULL ) ;
    dbus_bus_add_match( *connection, "type='signal',interface='inputmethod.host',member='sendKeyEvent',path='/host'", NULL ) ;
    dbus_bus_add_match( *connection, "type='signal',interface='inputmethod.host',member='sendMessage',path='/host'", NULL ) ;
    dbus_bus_add_match( *connection, "type='signal',interface='inputmethod.host',member='queryCursorRect',path='/host'", NULL ) ;
    dbus_bus_add_match( *connection, "type='signal',interface='inputmethod.host',member='querySurrounding',path='/host'", NULL ) ;
    dbus_bus_add_match( *connection, "type='signal',interface='inputmethod.host',member='replaceSurrounding',path='/host'", NULL ) ;
    dbus_connection_add_filter( *connection, filter, object, NULL ) ;
}
