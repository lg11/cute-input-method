#gcc main.c -o main `pkg-config --libs --cflags glib-2.0` `pkg-config --libs --cflags gtk+-2.0` `pkg-config --libs --cflags gconf-2.0`

#ALL : main

GTK_VERSION = gtk+-2.0 gdk-2.0

ALL : libcuteinputmethod.so

libcuteinputmethod.so : module.o context.o message.o
	gcc module.o context.o message.o `pkg-config --libs glib-2.0 $(GTK_VERSION) dbus-glib-1` -Wall -shared -o libcuteinputmethod.so 

module.o : module.c context.h
	gcc -c module.c -o module.o `pkg-config --cflags glib-2.0 $(GTK_VERSION) dbus-glib-1` -Wall

context.o : context.c context.h message.h keymap.h
	gcc -c context.c -o context.o `pkg-config --cflags glib-2.0 $(GTK_VERSION) dbus-glib-1` -Wall

message.o : message.h message.c context.h
	gcc -c message.c -o message.o `pkg-config --cflags glib-2.0 $(GTK_VERSION) dbus-glib-1` -Wall

keymap.h : keymap
	./keymap > keymap.h

keymap : keymap.cpp
	g++ keymap.cpp -o keymap `pkg-config --cflags QtCore` -Wall

main : main.o context.o
	gcc main.o context.o `pkg-config --libs glib-2.0 $(GTK_VERSION) dbus-glib-1` -Wall -o main

main.o : main.c context.h
	gcc -c main.c -o main.o `pkg-config --cflags glib-2.0 $(GTK_VERSION) dbus-glib-1` -Wall

clean :
	rm *.o
	rm *.so
	rm main

