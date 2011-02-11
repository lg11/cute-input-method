#-!- coding=utf-8 -!-
import dbus
import sys

if __name__ == "__main__" :
    print "connect"
    bus = dbus.SessionBus()
    service = bus.get_object('me.maemo.input.chinese', '/inputpad')
    print "connected"
    method = service.get_dbus_method( 'show', 'me.maemo.input.chinese.inputpad' )
    method( sys.argv[1] )

