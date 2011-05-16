#include "conn.h"

gboolean dbus_conn_request_commit( dbus_conn* obj, GString gstr ){
    g_debug( "dbus_conn_request_commit" );
    return obj->request_commit( obj->plugin, gstr );
}

gboolean dbus_conn_request_enter( dbus_conn* obj ){
    g_debug( "dbus_conn_request_enter" );
    return obj->request_enter( obj->plugin );
}

#include "bind.h"

static void dbus_conn_class_init( dbus_conn_class* klass );
static void dbus_conn_init( dbus_conn* obj );

GType dbus_conn_get_type( void ){
    static GType dbus_conn_type = 0;
    if ( !dbus_conn_type ) {
        static const GTypeInfo dbus_conn_info = {
            sizeof( dbus_conn_class ),
            NULL,
            NULL,
            (GClassInitFunc)dbus_conn_class_init,
            NULL,
            NULL,
            sizeof( dbus_conn ),
            0,
            (GInstanceInitFunc)dbus_conn_init
        };
        dbus_conn_type = g_type_register_static( G_TYPE_OBJECT, "dbus_conn", &dbus_conn_info, 0 );
    }
    return dbus_conn_type;
}

static void dbus_conn_class_init( dbus_conn_class* klass ){
    g_debug("dbus_conn_class_init");
    dbus_g_object_type_install_info( DBUS_CONN_TYPE, &dbus_glib_dbus_conn_object_info );
}
static void dbus_conn_init( dbus_conn* obj ){
    g_debug("dbus_conn_init");

    DBusGConnection* conn;
    DBusGProxy* proxy;
    GError *error = NULL;
    guint request_name_result;

    conn = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
    /*if (!conn)*/
        /*printf( "Couldn't connect to session bus %s\n", error->message );*/

    proxy = dbus_g_proxy_new_for_name( conn, "org.freedesktop.DBus", "/org/freedesktop/DBus", "org.freedesktop.DBus" );

    dbus_g_proxy_call ( proxy, "RequestName", &error, G_TYPE_STRING, "me.maemo.input.chinese.plugin.dbus_conn", G_TYPE_UINT, 0, G_TYPE_INVALID, G_TYPE_UINT, &request_name_result, G_TYPE_INVALID );
    /*if (!dbus_g_proxy_call ( proxy, "RequestName", &error, G_TYPE_STRING, "me.dbus_conn", G_TYPE_UINT, 0, G_TYPE_INVALID, G_TYPE_UINT, &request_name_result, G_TYPE_INVALID))*/
        /*printf( "Failed to acquire org.designfu.SampleService %s\n", error->message );*/

    dbus_g_connection_register_g_object ( conn, "/", G_OBJECT(obj) );
}

dbus_conn* dbus_conn_new(void){
    g_debug("dbus_conn_new");
    dbus_conn* obj;
    obj = g_object_new( DBUS_CONN_TYPE, NULL );
    /*printf("%d\n", obj->i);*/
   
    return obj;
}

void dbus_conn_set_commit_func( dbus_conn* conn, GObject* plugin, request_commit_func func ){
    conn->plugin = plugin;
    conn->request_commit = func;
}

void dbus_conn_set_enter_func( dbus_conn* conn, GObject* plugin, request_enter_func func ){
    conn->plugin = plugin;
    conn->request_enter = func;
}
