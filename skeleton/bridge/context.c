#include "context.h"
#include "message.h"
#include "keymap.h"

#include <gtk/gtk.h>

static GType context_type = 0 ;

static void set_client_window( GtkIMContext* context, GdkWindow* window ) {
    Context* c = CONTEXT(context) ;
    c->window = window ;
}

static gboolean filter_keypress( GtkIMContext* context, GdkEventKey* event ) {
    /*g_debug( "filter_keypress" ) ;*/

    Context* c = CONTEXT(context) ;
    gboolean flag = FALSE ;
    int keycode = convert_keycode( event->keyval ) ;
    
    if ( keycode > 0 ) {
        int modifiers = convert_modifiers( event->state ) ;
    
        if ( event->type == GDK_KEY_PRESS )
            flag = call_keyPress( &(c->connection), keycode, modifiers ) ;
        else if ( event->type == GDK_KEY_RELEASE )
            flag = call_keyRelease( &(c->connection), keycode, modifiers ) ;
    }
    return flag ? flag : gtk_im_context_filter_keypress( c->slave, event )  ;
}

static void focus_in( GtkIMContext* context ) {
    Context* c = CONTEXT(context) ;
    c->focused = TRUE ;
    emit_focusIn( &(c->connection) ) ;
}

static void focus_out( GtkIMContext* context ) {
    Context* c = CONTEXT(context) ;
    c->focused = FALSE ;
    emit_focusOut( &(c->connection) ) ;
}

static void set_cursor_location( GtkIMContext* context, const GdkRectangle* area ) {
    Context* c = CONTEXT(context) ;
    if ( c->window ) {
        GdkRectangle rect ;
        rect.x = area->x ;
        rect.y = area->y ;
        rect.width = area->width ;
        rect.height = area->height ;
        
        int x ; int y ;
        /*gdk_window_get_root_origin( c->window, &x, &y ) ;*/
        gdk_window_get_origin( c->window, &x, &y ) ;

        rect.x += x ;
        rect.y += y ;
    
        emit_cursorRectUpdate( &(c->connection), rect.x, rect.y, rect.width, rect.height ) ;
    }
}

static void slave_commit( GtkIMContext* slave, const char* text, gpointer data ) {
    Context* c = CONTEXT(data) ;
    g_signal_emit_by_name( c, "commit", text ) ;
}

static void context_base_init( Context* context ) {
    g_debug( "context_base_init" ) ;
}

static void context_base_finalize( Context* context ) {
    g_debug( "context_base_finalize" ) ;
}

static void context_finalize( Context* context ) {
    g_debug( "context_finalize" ) ;
    if ( context->slave )
        g_object_unref( context->slave ) ;
    if ( context->connection )
        dbus_connection_unref( context->connection ) ;
}

static void context_init( Context* context ) {
    g_debug( "context_init" ) ;
    context->slave = gtk_im_context_simple_new() ;
    g_signal_connect( G_OBJECT(context->slave), "commit", G_CALLBACK(slave_commit), context ) ;
    context->connection = NULL ;
    context->window = NULL ;
    request_connect( &(context->connection), context ) ;
    context->focused = FALSE ;
}

static void context_class_init( ContextClass* context_class ) {
    g_debug( "context_class_init" ) ;
    GObjectClass* object_class = G_OBJECT_CLASS( context_class ) ;
    GtkIMContextClass* gtk_im_context_class = GTK_IM_CONTEXT_CLASS(context_class) ;

    object_class->finalize = context_finalize ;

    gtk_im_context_class->set_client_window = set_client_window ;
    gtk_im_context_class->filter_keypress = filter_keypress ;
    gtk_im_context_class->focus_in = focus_in ;
    gtk_im_context_class->focus_out = focus_out ;
    gtk_im_context_class->set_cursor_location = set_cursor_location ;
}


void context_register_type( GTypeModule* type_module ) {
    if ( !context_type ) {
        static const GTypeInfo context_info = {
            sizeof( ContextClass ),
            (GBaseInitFunc)context_base_init,
            (GBaseFinalizeFunc)context_base_finalize,
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

/*Context* context_new( void ) {*/
    /*GObject* object ;*/
    /*object = g_object_new( CONTEXT_TYPE, NULL ) ;*/
    /*return (Context*)object ;*/
/*}*/

