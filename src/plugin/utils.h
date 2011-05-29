#ifndef PLUGIN_UTILS_H
#define PLUGIN_UTILS_H

#include <dbus/dbus-glib.h>
#include <glib.h>
#include <X11/Xlib.h>

//int dbus_call_pad_show( DBusGConnection* conn );
int dbus_call_pad_show( const gchar* str );
gboolean check_x11win_classhint( Window win );
#endif
