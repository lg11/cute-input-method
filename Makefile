DIRS = data
QML_PLUGIN_DIRS = src/clipboard src/mousetrack

ALL : qml_plugin host context-qt4 context-gtk2
	set -e ; for d in $(DIRS) ; do $(MAKE) -C $$d ; done

host :
	qmake -makefile src/host/host.pro -o src/host/Makefile 
	$(MAKE) -C src/host

context-gtk2 :
	$(MAKE) -C src/context/gtk2

context-qt4 :
	qmake -makefile src/context/qt4/plugin.pro -o src/context/qt4/Makefile 
	$(MAKE) -C src/context/qt4

qml_plugin :
	set -e ; for d in $(QML_PLUGIN_DIRS) ; do qmake -makefile $$d/plugin.pro -o $$d/Makefile ; done
	set -e ; for d in $(QML_PLUGIN_DIRS) ; do $(MAKE) -C $$d ; done

clean :
	set -e ; for d in $(DIRS) ; do $(MAKE) -C $$d clean ; done
	set -e ; for d in $(QML_PLUGIN_DIRS) ; do $(MAKE) -C $$d clean ; done
	$(MAKE) -C src/context/qt4 clean
	$(MAKE) -C src/context/gtk2 clean
	$(MAKE) -C src/host clean

install :
	mkdir -p $(DESTDIR)/opt/cim
	mkdir -p $(DESTDIR)/opt/cim/host
	mkdir -p $(DESTDIR)/opt/cim/host/view
	mkdir -p $(DESTDIR)/opt/cim/host/extra
	mkdir -p $(DESTDIR)/opt/cim/plugin
	mkdir -p $(DESTDIR)/opt/cim/data
	mkdir -p $(DESTDIR)/usr/share/dbus-1/services
	mkdir -p $(DESTDIR)/usr/lib/qt4/plugins/inputmethods
	mkdir -p $(DESTDIR)/usr/lib/gtk-2.0/2.10.0/immodules
	cp src/host/main $(DESTDIR)/opt/cim/host
	cp src/host/view/*.qml $(DESTDIR)/opt/cim/host/view
	cp src/host/extra/*.qml $(DESTDIR)/opt/cim/host/extra
	cp src/host/extra/*.js $(DESTDIR)/opt/cim/host/extra
	cp src/host/extra/qmldir $(DESTDIR)/opt/cim/host/extra
	cp data/formated $(DESTDIR)/opt/cim/data
	cp data/prePhrase.py $(DESTDIR)/opt/cim/data
	cp mcip $(DESTDIR)/opt/cim/
	set -e ; for d in $(QML_PLUGIN_DIRS) ; do cp $$d/*.so $(DESTDIR)/opt/cim/host/extra ; done
	cp src/context/qt4/libcuteinputmethod.so $(DESTDIR)/usr/lib/qt4/plugins/inputmethods
	#cp src/context/gtk2/libcuteinputmethod.so $(DESTDIR)/usr/lib/gtk-2.0/2.10.0/immodules
	cp me.inputmethod.host.service $(DESTDIR)/usr/share/dbus-1/services/ 
	if test "$(DESTDIR)x" == "x"; then \
		echo export GTK_IM_MODULE=\"cuteinputmethod\" >> $(DESTDIR)/etc/profile ; \
		echo export QT_IM_MODULE=\"cuteinputmethod\" >> $(DESTDIR)/etc/profile ; \
	fi
		#gtk-query-immodules-2.0 > $(DESTDIR)/etc/gtk-2.0/gtk.immodules ; \

uninstall :
	rm -rf $(DESTDIR)/opt/cim
	rm $(DESTDIR)/usr/share/dbus-1/services/me.inputmethod.host.service
	#rm $(DESTDIR)/usr/lib/gtk-2.0/2.10.0/immodules/libcuteinputmethod.so
	rm $(DESTDIR)/usr/lib/qt4/plugins/inputmethods/libcuteinputmethod.so
	if test "$(DESTDIR)x" == "x"; then \
		cat $(DESTDIR)/etc/profile | grep -v cuteinputmethod > $(DESTDIR)/tmp/profile.tmp ; \
		cat $(DESTDIR)/tmp/profile.tmp > $(DESTDIR)/etc/profile ; \
	fi
		#gtk-query-immodules-2.0 > $(DESTDIR)/etc/gtk-2.0/gtk.immodules ; \
