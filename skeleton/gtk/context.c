#include "context.h"

/*#include <dbus/dbus-glib.h>*/
/*#include <dbus/dbus.h>*/

/*static void dbus_call() {*/
    /*DBusMessage* message ;*/
    /*DBusConnection* connection ;*/
    /*DBusError error ;*/
    /*dbus_error_init( &error ) ;*/
    /*connection = dbus_bus_get( DBUS_BUS_SESSION, &error ) ;*/
    
    /*message = dbus_message_new_signal( "/context", "inputmethod.context", "sendMessage" ) ;*/
    /*char* s = "ssss" ;*/
    /*dbus_message_append_args( message, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID ) ;*/
    /*dbus_connection_send( connection, message, NULL ) ;*/

    /*dbus_message_unref( message ) ;*/
/*}*/

static GType context_type = 0 ;

/*void set_client_window( GtkIMContext *context, GdkWindow *window ) ;*/
/*void get_preedit_string( GtkIMContext *context, gchar **str, PangoAttrList **attrs, gint *cursor_pos) ;*/
static gboolean filter_keypress( GtkIMContext *context, GdkEventKey *event ) {
    g_debug( "filter_keypress" ) ;
}

static void focus_in( GtkIMContext *context ) {
    g_debug( "focus_in" ) ;
}

static void focus_out( GtkIMContext *context ) {
    g_debug( "focus_out" ) ;
}

static void context_class_init( ContextClass* context_class ) {
    g_debug( "context_class_init" ) ;
    GtkIMContextClass* gtk_im_context_class = GTK_IM_CONTEXT_CLASS(context_class) ;

    gtk_im_context_class->filter_keypress = filter_keypress ;
    gtk_im_context_class->focus_in = focus_in ;
    gtk_im_context_class->focus_out = focus_out ;

    ;
}

static void context_init( Context* context ) {
    g_debug( "context_init" ) ;
    ;
}

void context_register_type( GTypeModule* type_module ) {
    if ( !context_type ) {
        static const GTypeInfo context_info = {
            sizeof( ContextClass ),
            NULL,
            NULL,
            (GClassInitFunc)context_class_init,
            NULL,
            NULL,
            sizeof( Context ),
            0,
            (GInstanceInitFunc)context_init
        } ;
        if ( type_module ) 
            context_type = g_type_module_register_type( type_module, GTK_TYPE_IM_CONTEXT, "context", &context_info, 0 ) ;
        else 
            context_type = g_type_register_static( GTK_TYPE_IM_CONTEXT, "context", &context_info, 0 ) ;
    }
}

GType context_get_type( void ) {
    context_register_type( NULL ) ;
    return context_type ;
}

Context* context_new( void ) {
    GObject* object ;
    object = g_object_new( CONTEXT_TYPE, NULL ) ;
    return (Context*)object ;
}

