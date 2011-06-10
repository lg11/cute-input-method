#ifndef CONTEXT_H
#define CONTEXT_H

#include <glib-object.h>
#include <gtk/gtkimmodule.h>

#include <dbus/dbus.h>

#define CONTEXT_TYPE \
    (context_get_type())
#define CONTEXT(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST( (obj), CONTEXT_TYPE, Context ))
#define CONTEXT_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST( (klass), CONTEXT_TYPE, ContextClass))
#define IS_CONTEXT(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), CONTEXT_TYPE))
#define IS_CONTEXT_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), CONTEXT_TYPE))
#define CONTEXT_GET_CLASS(obj) \
    (G_TYPE_CHECK_GET_CLASS ((obj), CONTEXT_TYPE, ContextClass))

G_BEGIN_DECLS

typedef struct {
    GtkIMContext parent ;
    GtkIMContext* slave ;
    DBusConnection* connection ;
    GdkRectangle cursorRect ;
    GdkWindow* window ;
    gboolean focused ;
    gboolean prepare_send_surrounding ;
    char* surrounding ;
} Context ;

typedef struct {
    GtkIMContextClass parent_class ;
} ContextClass ;

void context_register_type( GTypeModule* type_module ) ;
GType context_get_type( void ) ;

//Context* context_new( void ) ;

//void gtk_im_context_set_client_window(GtkIMContext *context, GdkWindow *window);
//void gtk_im_context_get_preedit_string(GtkIMContext *context, gchar **str, PangoAttrList **attrs, gint *cursor_pos);
//gboolean gtk_im_context_filter_keypress(GtkIMContext *context, GdkEventKey *event);
//void gtk_im_context_focus_in(GtkIMContext *context);
//void gtk_im_context_focus_out(GtkIMContext *context);
//void gtk_im_context_reset(GtkIMContext *context);
//void gtk_im_context_set_cursor_location(GtkIMContext *context, const GdkRectangle *area);
//void gtk_im_context_set_use_preedit(GtkIMContext *context,
//gboolean use_preedit);
//void gtk_im_context_set_surrounding(GtkIMContext *context, const gchar *text, gint len, gint cursor_index);
//gboolean gtk_im_context_get_surrounding(GtkIMContext *context, gchar **text, gint *cursor_index);
//gboolean gtk_im_context_delete_surrounding(GtkIMContext *context, gint offset, gint n_chars);

G_END_DECLS

#endif
