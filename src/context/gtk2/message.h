#ifndef MESSAGE_H
#define MESSAGE_H

#include <dbus/dbus-glib.h>
#include <dbus/dbus.h>

//gboolean send_surrounding( void* data ) {

void emit_sendMessage( char* message ) ;

void emit_sendSurrounding( char* surrounding ) ;

void emit_focusIn() ;

void emit_focusOut() ;

void emit_requestSoftwareInputPanel() ;

void emit_cursorRectUpdate( int x, int y, int width, int height ) ;

gboolean call_keyPress( int keycode , int modifiers ) ;

gboolean call_keyRelease( int keycode , int modifiers ) ;

void request_connect() ;

void set_focused_context( GObject* object ) ;

#endif
