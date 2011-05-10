#-!- coding=utf-8 -!-

import dbus
import dbus.service

class Interface( dbus.service.Object ):
    def __init__( self, session_bus, widget = None ):
        dbus.service.Object.__init__( self, session_bus, "/inputpad" )
        self.session_bus = session_bus
        self.widget = widget
    def commit( self, text ) :
        #text = str( text.toUtf8() )
        text = str( text.encode( "utf-8" ) )
        #print type( text )
        #print "commit", text
        #bus = dbus.SessionBus()
        bus = self.session_bus
        plugin = bus.get_object('me.maemo.input.chinese.plugin.dbus_conn', '/')
        method = plugin.get_dbus_method( 'request_commit', 'me.maemo.input.chinese.plugin.dbus_conn' )
        method( text )
    @dbus.service.method( "me.maemo.input.chinese.inputpad", in_signature='s', out_signature='' )
    def show( self, text ):
        if self.widget :
            #self.widget.callback_show( text )
            self.active( text )
        else :
            print "show"

if __name__ == "__main__" :
    import sys
    from dbus.mainloop.qt import DBusQtMainLoop
    from PyQt4 import QtCore, QtGui

    QtCore.Signal = QtCore.pyqtSignal
    QtCore.Slot = QtCore.pyqtSlot

    app = QtGui.QApplication( sys.argv )

    DBusQtMainLoop( set_as_default=True )
    session_bus = dbus.SessionBus()
    name = dbus.service.BusName( "me.maemo.input.chinese", session_bus )
    o = Interface( session_bus )

    sys.exit( app.exec_() )
