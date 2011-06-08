#ifndef MESSAGE_H
#define MESSAGE_H

#include <dbus/dbus-glib.h>
#include <dbus/dbus.h>

void emit_sendMessage( DBusConnection** connection, char* message ) ;

void emit_focusIn( DBusConnection** connection ) ;

void emit_focusOut( DBusConnection** connection ) ;

void emit_cursorRectUpdate( DBusConnection**, int x, int y, int width, int height ) ;

gboolean call_keyPress( DBusConnection** connection, int keycode , int modifiers ) ;

#endif
