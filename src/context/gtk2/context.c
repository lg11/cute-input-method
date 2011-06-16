#ifndef __i386__

#include "context.h"
#include "message.h"
#include "keymap.h"

#include <gtk/gtk.h>
#include <glib.h>

static GType context_type = 0 ;

/*static gboolean send_focus_in( void* data ) {*/
    /*Context* c = CONTEXT(data) ;*/
    /*emit_focusIn( &(c->connection) ) ;*/
    /*return FALSE ;*/
/*}*/

#ifdef MAEMO_CHANGES
#include <X11/Xlib.h>
#include <X11/extensions/shape.h>
#include <gdk/gdkx.h>

static gboolean check_x11win_classhint( Window win ){
    //检查client window的属性，如果是未定义的窗口（多半是浏览器里的文本输入框），则返回FALSE
    Display* dpy ;
    Atom* prop_list ;
    int prop_count = 0 ;
    Window root ;
    Window parent ;
    Window* child_list ;
    unsigned int child_count ;

    gboolean return_flag = TRUE ;

    //首先，不断查询当前window的parent，直到获取一个有prop，可以获得信息的window id
    g_debug("check_x11win_classhint start win id = %d", (int)win) ;
    dpy = GDK_DISPLAY() ;
    XQueryTree( dpy, win, &root, &parent, &child_list, &child_count ) ;
    XFree( child_list ) ;
    g_debug( "check_x11win_classhint query root = %d, parent = %d", (int)root, (int)parent ) ;
    prop_list = XListProperties( dpy, win, &prop_count ) ;
    g_debug( "check_x11win_classhint get prop_count =  %d", prop_count ) ;

    if ( ( root == parent ) && ( prop_count <= 0 ) ) {
        //输入窗口就是自己根窗口的变态，我也只想得出n900系统浏览器microB这一个了……
        //and all qt program orz...
        //so check prop_count <= 0
        g_debug( "check_x11win_classhint find bt mircoB" ) ;
        XFree( prop_list ) ;
        return_flag = FALSE ;
        return return_flag ;
    }

    while( prop_count == 0 && root != parent ){
        XFree( prop_list ) ;
        win = parent ;
        XQueryTree( dpy, win, &root, &parent, &child_list, &child_count ) ;
        XFree( child_list ) ;
        g_debug( "check_x11win_classhint query root = %d, parent = %d", (int)root, (int)parent ) ;
        prop_list = XListProperties( dpy, win, &prop_count ) ;
        g_debug( "check_x11win_classhint get prop_count =  %d", prop_count ) ;
    }
    XFree(prop_list) ;

    //检查classhint
    XClassHint classhint ;
    XGetClassHint( dpy, win, &classhint ) ;
    if ( classhint.res_name == NULL && classhint.res_class == NULL ){
        g_debug( "check_x11win_classhint get undefined win" );
        return_flag = FALSE ;
    }
    else
        g_debug( "check_x11win_classhint res_name = %s, res_class = %s", classhint.res_name, classhint.res_class ) ;
    if ( g_strcmp0( classhint.res_class, "Firefox" ) == 0 ){
        g_debug( "check_x11win_classhint find firefox" ) ;
        return_flag = FALSE ;
        /*return_flag = TRUE;*/
    }
    XFree( classhint.res_name ) ;
    XFree( classhint.res_class ) ;

    g_debug( "check_x11win_classhint end" ) ;

    return return_flag ;
}

static gboolean is_fucked_microb( GdkWindow* window ) {
    return !check_x11win_classhint( GDK_WINDOW_XID(window) ) ;
}


/*static void show( GtkIMContext* context ) {*/
    /*Context* c = CONTEXT(context) ;*/
    /*c->focused = TRUE ;*/
    /*emit_focusIn( &(c->connection) ) ;*/
/*}*/

/*static void hide( GtkIMContext* context ) {*/
    /*g_debug( "hide" ) ;*/
    /*Context* c = CONTEXT(context) ;*/
    /*c->focused = FALSE ;*/
    /*emit_focusOut( &(c->connection) ) ;*/
/*}*/

gboolean filter_event( GtkIMContext* context, GdkEvent* event ) {
    Context* c = CONTEXT(context) ;

    GdkEventButton* button_event = (GdkEventButton*)event ;
    if ( button_event->type == GDK_BUTTON_PRESS )
        g_get_current_time( &(c->press_time) ) ;
    else if ( button_event->type == GDK_BUTTON_RELEASE ) {
        GTimeVal current_time ;
        g_get_current_time( &current_time ) ;
        glong d = ( current_time.tv_sec - c->press_time.tv_sec ) * 1000000 + current_time.tv_usec - c->press_time.tv_usec ;
        /*g_debug( "timestamp %ld.%ld, %ld.%ld, %ld", c->press_time.tv_sec, c->press_time.tv_usec, current_time.tv_sec, current_time.tv_usec, d ) ;*/
        if ( d > 0 && d < 200000 )
            emit_requestSoftwareInputPanel( &(c->connection) ) ;
    }

    return FALSE ;
}
#endif

static void set_client_window( GtkIMContext* context, GdkWindow* window ) {
    /*g_debug( "set_client_window" ) ;*/
    Context* c = CONTEXT(context) ;
    c->window = window ;
}

static gboolean filter_keypress( GtkIMContext* context, GdkEventKey* event ) {
    /*g_debug( "filter_keypress" ) ;*/
    Context* c = CONTEXT(context) ;
    gboolean flag = FALSE ;
    int keycode = convert_keycode( event->keyval ) ;
    
    /*g_debug( "prepare_send_keypress %d %d", keycode, event->type ) ;*/
    if ( keycode > 0 ) {
        int modifiers = convert_modifiers( event->state ) ;
    
        if ( event->type == GDK_KEY_PRESS ) {
            /*g_debug( "send_keypress %d %d", keycode, modifiers ) ;*/
            flag = call_keyPress( &(c->connection), keycode, modifiers ) ;
        }
        else if ( event->type == GDK_KEY_RELEASE ) {
            /*g_debug( "send_keyrelease %d %d", keycode, modifiers ) ;*/
            flag = call_keyRelease( &(c->connection), keycode, modifiers ) ;
        }
    }
    return flag ? flag : gtk_im_context_filter_keypress( c->slave, event )  ;
}

static void focus_in( GtkIMContext* context ) {
    Context* c = CONTEXT(context) ;
    c->focused = TRUE ;
    emit_focusIn( &(c->connection) ) ;
#ifdef MAEMO_CHANGES
    /*if ( c->window ) {*/
        /*if ( is_fucked_microb( c->window ) )*/
            /*emit_requestSoftwareInputPanel( &(c->connection) ) ;*/
    /*}*/
#endif
}

static void focus_out( GtkIMContext* context ) {
    Context* c = CONTEXT(context) ;
    c->focused = FALSE ;
    emit_focusOut( &(c->connection) ) ;
}

static void set_cursor_location( GtkIMContext* context, const GdkRectangle* area ) {
    g_debug( "set_cursor_location" ) ;
    Context* c = CONTEXT(context) ;
    if ( c->window ) {
        c->cursorRect.x = area->x ;
        c->cursorRect.y = area->y ;
        c->cursorRect.width = area->width ;
        c->cursorRect.height = area->height ;
        
        int x ; int y ;
        /*gdk_window_get_root_origin( c->window, &x, &y ) ;*/
        gdk_window_get_origin( c->window, &x, &y ) ;

        c->cursorRect.x += x ;
        c->cursorRect.y += y ;
    }
}

static void slave_commit( GtkIMContext* slave, const char* text, gpointer data ) {
    Context* c = CONTEXT(data) ;
    g_signal_emit_by_name( c, "commit", text ) ;
}

static void context_base_init( Context* context ) {
    /*g_debug( "context_base_init" ) ;*/
}

static void context_base_finalize( Context* context ) {
    /*g_debug( "context_base_finalize" ) ;*/
}

static void context_finalize( Context* context ) {
    /*g_debug( "context_finalize" ) ;*/
    if ( context->slave )
        g_object_unref( context->slave ) ;
    if ( context->connection )
        dbus_connection_unref( context->connection ) ;
}

static void context_init( Context* context ) {
    /*g_debug( "context_init" ) ;*/
    context->slave = gtk_im_context_simple_new() ;
    g_signal_connect( G_OBJECT(context->slave), "commit", G_CALLBACK(slave_commit), context ) ;
    context->connection = NULL ;
    context->window = NULL ;
    request_connect( &(context->connection), G_OBJECT(context) ) ;
    context->focused = FALSE ;
    context->surrounding = NULL ;
    context->surrounding_cursor_offset = 0 ;
    context->surrounding_length = 0 ;
    g_get_current_time( &(context->press_time) ) ;
}

static void context_class_init( ContextClass* context_class ) {
    /*g_debug( "context_class_init" ) ;*/
    GObjectClass* object_class = G_OBJECT_CLASS( context_class ) ;
    GtkIMContextClass* gtk_im_context_class = GTK_IM_CONTEXT_CLASS(context_class) ;

    object_class->finalize = context_finalize ;

#ifdef MAEMO_CHANGES
    /*gtk_im_context_class->show = show ;*/
    /*gtk_im_context_class->show = show ;*/
    gtk_im_context_class->filter_event = filter_event ;
#endif
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

#endif
