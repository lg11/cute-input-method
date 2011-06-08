#include "context.h"
/*#include "signal.h"*/
#include "message.h"

static GType context_type = 0 ;



static gboolean filter_keypress( GtkIMContext* context, GdkEventKey* event ) {
    Context* c = CONTEXT(context) ;
    g_debug( "filter_keypress" ) ;
    /*return call_keyPress( &(c->connection), 65, 0 ) ;*/
    return gtk_im_context_filter_keypress( c->slave, event )  ;
}

static void focus_in( GtkIMContext* context ) {
    Context* c = CONTEXT(context) ;
    emit_focusIn( &(c->connection) ) ;
}

static void focus_out( GtkIMContext* context ) {
    Context* c = CONTEXT(context) ;
    emit_focusOut( &(c->connection) ) ;
}

static void set_cursor_location( GtkIMContext* context, const GdkRectangle* area ) {
    Context* c = CONTEXT(context) ;
    emit_cursorRectUpdate( &(c->connection), area->x, area->y, area->width, area->height ) ;
}


static void context_class_init( ContextClass* context_class ) {
    g_debug( "context_class_init" ) ;
    GtkIMContextClass* gtk_im_context_class = GTK_IM_CONTEXT_CLASS(context_class) ;

    gtk_im_context_class->filter_keypress = filter_keypress ;
    gtk_im_context_class->focus_in = focus_in ;
    gtk_im_context_class->focus_out = focus_out ;
    gtk_im_context_class->set_cursor_location = set_cursor_location ;
}

static void slave_commit( GtkIMContext* slave, const char* text, gpointer data ) {
    Context* c = CONTEXT(data) ;
    g_signal_emit_by_name( c, "commit", text ) ;
}

static void context_init( Context* context ) {
    g_debug( "context_init" ) ;
    context->slave = gtk_im_context_simple_new() ;
    g_signal_connect( G_OBJECT(context->slave), "commit", G_CALLBACK(slave_commit), context ) ;
    context->connection = NULL ;
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

/*Context* context_new( void ) {*/
    /*GObject* object ;*/
    /*object = g_object_new( CONTEXT_TYPE, NULL ) ;*/
    /*return (Context*)object ;*/
/*}*/

