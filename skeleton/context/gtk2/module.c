#include <gtk/gtk.h>
#include <gtk/gtkimmodule.h>

#include "context.h"

static const GtkIMContextInfo context_info = { 
    "cuteinputmethod",
    "", 
    "",
    "", 
    "en:zh:*"
} ;

static const GtkIMContextInfo* info_list[] = { &context_info } ;

G_MODULE_EXPORT const gchar* g_module_check_init( GModule* module ) {
    return glib_check_version( GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, 0 ) ;
}

G_MODULE_EXPORT void im_module_init( GTypeModule *type_module ) {
    g_type_module_use( type_module ) ;
    context_register_type( type_module ) ;
}

G_MODULE_EXPORT void im_module_exit( void ) {
}

G_MODULE_EXPORT GtkIMContext* im_module_create ( const gchar* context_id ) {
    if ( g_strcmp0( context_id, "cuteinputmethod" ) == 0 ) {
        GObject* object ;
        object = g_object_new( CONTEXT_TYPE, NULL ) ;
        /*Context* object ;*/
        /*object = context_new() ;*/
        return (GtkIMContext*)object ;
    }
    return NULL ;
}

G_MODULE_EXPORT void im_module_list( const GtkIMContextInfo*** contexts, gint* n_contexts ) {
    *contexts = info_list ;
    *n_contexts = G_N_ELEMENTS( info_list ) ;
}

