#include "context.h"
#include "dbus/dbus-glib.h"
#include "dbus/dbus.h"

DBusHandlerResult callback( DBusConnection* connection, DBusMessage* message, void* user_data ) {
    /*g_debug( "callback" ) ;*/

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED ;
}

int main( int argc, char** argv ) {
    gtk_init( &argc, &argv ) ;
    /*g_debug( "new start" ) ;*/
    Context* context = context_new() ;
    /*g_debug( "new done" ) ;*/
    GMainLoop* loop = g_main_loop_new( NULL , FALSE ) ;

    DBusError error ;
    DBusConnection *connection ;
    dbus_error_init( &error ) ;
    connection = dbus_bus_get( DBUS_BUS_SESSION, &error ) ;
    dbus_connection_setup_with_g_main( connection, NULL ) ;

    dbus_bus_add_match( connection, "type='signal',interface='inputmethod.context',member='',path='/context'", NULL ) ;
    dbus_connection_add_filter( connection, callback, loop, NULL ) ;

    g_main_loop_run( loop ) ;
    return 0 ;
}

