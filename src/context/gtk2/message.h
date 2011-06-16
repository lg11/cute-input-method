#ifndef MESSAGE_H
#define MESSAGE_H

#include <dbus/dbus-glib.h>
#include <dbus/dbus.h>

//gboolean send_surrounding( void* data ) {

void emit_sendMessage( DBusConnection** connection, char* message ) ;

void emit_sendSurrounding( DBusConnection** connection, char* surrounding ) ;

void emit_focusIn( DBusConnection** connection ) ;

void emit_focusOut( DBusConnection** connection ) ;

void emit_requestSoftwareInputPanel( DBusConnection** connection ) ;

void emit_cursorRectUpdate( DBusConnection**, int x, int y, int width, int height ) ;

gboolean call_keyPress( DBusConnection** connection, int keycode , int modifiers ) ;

gboolean call_keyRelease( DBusConnection** connection, int keycode , int modifiers ) ;

void request_connect( DBusConnection** connection ) ;

void set_focused_context( GObject* object ) ;

#endif
