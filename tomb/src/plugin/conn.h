#ifndef ME_DBUS_CONN_H
#define ME_DBUS_CONN_H

#include <glib-object.h>

#define DBUS_CONN_TYPE (dbus_conn_get_type())
#define DBUS_CONN(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), DBUS_CONN, dbus_conn))

typedef gboolean (*request_commit_func)( GObject* obj, GString gstr );
typedef gboolean (*request_enter_func)( GObject* obj );

typedef struct{
    GObject parent;
    //DBusGConnection* conn;
    request_commit_func request_commit;
    request_enter_func request_enter;
    GObject* plugin;
}dbus_conn;

typedef struct{
    GObjectClass parent_class;
}dbus_conn_class;

GType dbus_conn_get_type(void);
dbus_conn* dbus_conn_new(void);
void dbus_conn_set_commit_func( dbus_conn* conn, GObject* plugin, request_commit_func func );
void dbus_conn_set_enter_func( dbus_conn* conn, GObject* plugin, request_enter_func func );

#endif
