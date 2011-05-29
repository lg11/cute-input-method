#gcc main.c -o main `pkg-config --libs --cflags glib-2.0` `pkg-config --libs --cflags gtk+-2.0` `pkg-config --libs --cflags gconf-2.0`

ALL : inputpad_plugin.so

bind.h : bind.xml
	dbus-binding-tool --mode=glib-server --prefix=dbus_conn bind.xml > bind.h

utils.o : utils.c utils.h
	gcc -c utils.c -o utils.o `pkg-config --cflags glib-2.0 gtk+-2.0 gconf-2.0`

conn.o : conn.c conn.h bind.h
	gcc -c conn.c -o conn.o `pkg-config --libs --cflags glib-2.0 gtk+-2.0 gconf-2.0`

plugin.o : plugin.c
	gcc -c plugin.c -o plugin.o `pkg-config --cflags hildon-input-method-framework-3.0 hildon-input-method-ui-3.0 glib-2.0 gtk+-2.0 gconf-2.0`

inputpad_plugin.so : utils.o plugin.o conn.o
	gcc utils.o plugin.o conn.o -shared -o inputpad_plugin.so `pkg-config --libs hildon-input-method-framework-3.0 hildon-input-method-ui-3.0 glib-2.0 gtk+-2.0 gconf-2.0`

clean :
	rm *.o
	rm bind.h
	rm *.so

