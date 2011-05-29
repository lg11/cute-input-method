#include "utils.h"
#include <X11/Xatom.h>
#include <gdk/gdkx.h>

/*int dbus_call_pad_show( DBusGConnection* conn ){*/
int dbus_call_pad_show( const gchar* str ){
    GError* error = NULL;
    static DBusGConnection* conn = NULL;
    static DBusGProxy* proxy = NULL;

    if (!conn)
        conn = dbus_g_bus_get (DBUS_BUS_SESSION, &error);

    if (!proxy )
        proxy = dbus_g_proxy_new_for_name( conn, "me.maemo.input.chinese", "/inputpad", "me.maemo.input.chinese.inputpad" );

    if ( !dbus_g_proxy_call( proxy, "show", &error, G_TYPE_STRING, str, G_TYPE_INVALID, G_TYPE_INVALID ) ) {
        g_debug( "failed to call: %s", error->message );
        g_error_free(error);
        return 1;
    }
    return 0;
}


void get_x11win_prop_old( Window win ){
    Display* dpy;
    Atom actual_type;
    int actual_format;
    unsigned long num_items = 0, bytes_left;
    Atom *data_ptr;
    char **names;
    Atom wm_state;
    int i;

    g_debug("x start ");
    dpy = GDK_DISPLAY();
    /*wm_state = XInternAtom(dpy, "_NET_WM_STATE", False);*/
    /*wm_state = XA_FULL_NAME;*/
    /*if (XGetWindowProperty(dpy, win, wm_state, 0, 0xFFFFFFFF, False, XA_ATOM, &actual_type, &actual_format, &num_items, &bytes_left, (unsigned char **) &data_ptr) == Success) {*/
    if (XGetWindowProperty(dpy, win, wm_state, 0, 0xFFFFFFFF, False, XA_ATOM, &actual_type, &actual_format, &num_items, &bytes_left, (unsigned char **) &data_ptr) == Success) {
        g_debug("actual_format: %d\nnum_items: %d\nbytes_left: %d\n", actual_format, num_items, bytes_left);

        /* get the names of the returned states */
        /*if (XGetAtomNames(dpy, data_ptr, num_items, names)) {*/
            /*g_debug("XGetAtomNames zero.\n");*/
            /*for (i = 0; i < num_items; i++)*/
                /*g_debug("%d: %s\n", i+1, names[i]);*/
            /*}*/
        /*else*/
            /*g_debug("XGetAtomNames error.\n");*/

        /*XFree(data_ptr);*/
        /*XFree(names);*/
    }
    else
        g_debug("Fail\n");
}


gboolean check_x11win_classhint( Window win ){
    //检查client window的属性，如果是未定义的窗口（多半是浏览器里的文本输入框），则返回FALSE
    Display* dpy;
    Atom* prop_list;
    int prop_count = 0;
    Window root;
    Window parent;
    Window* child_list;
    int child_count;

    gboolean return_flag = TRUE;

    //首先，不断查询当前window的parent，直到获取一个有prop，可以获得信息的window id
    g_debug("check_x11win_classhint start win id = %x", win);
    dpy = GDK_DISPLAY();
    XQueryTree( dpy, win, &root, &parent, &child_list, &child_count );
    XFree(child_list);
    g_debug("check_x11win_classhint query root = %x, parent = %x", root, parent );
    prop_list = XListProperties( dpy, win, &prop_count );
    g_debug("check_x11win_classhint get prop_count =  %d", prop_count );

    if ( ( root == parent ) && ( prop_count <= 0 ) ) {
        //输入窗口就是自己根窗口的变态，我也只想得出n900系统浏览器这一个了……
        //and all qt program orz...
        //so check prop_count <= 0
        g_debug("check_x11win_classhint find bt mircoB");
        XFree(prop_list);
        return_flag = FALSE;
        return return_flag;
    }

    while( prop_count == 0 && root != parent ){
        XFree(prop_list);
        win = parent;
        XQueryTree( dpy, win, &root, &parent, &child_list, &child_count );
        XFree(child_list);
        g_debug("check_x11win_classhint query root = %x, parent = %x", root, parent );
        prop_list = XListProperties( dpy, win, &prop_count );
        g_debug("check_x11win_classhint get prop_count =  %d", prop_count );
    }
    XFree(prop_list);

    //检查classhint
    XClassHint classhint;
    XGetClassHint( dpy, win, &classhint );
    if ( classhint.res_name == NULL && classhint.res_class == NULL ){
        g_debug( "check_x11win_classhint get undefined win" );
        return_flag = FALSE;
    }
    else
        g_debug( "check_x11win_classhint res_name = %s, res_class = %s", classhint.res_name, classhint.res_class );
    if ( g_strcmp0( classhint.res_class, "Firefox" ) == 0 ){
        g_debug("check_x11win_classhint find firefox");
        return_flag = FALSE;
        /*return_flag = TRUE;*/
    }
    XFree( classhint.res_name );
    XFree( classhint.res_class );

    g_debug("check_x11win_classhint end");

    return return_flag;
}
