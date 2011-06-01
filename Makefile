DIRS = src/plugin python data
QML_PLUGIN_DIRS = src/clipboard src/engine src/mousetrack

ALL : qml_plugin runtime
	#qmake -makefile src/backend.pro -o src/Makefile
	set -e ; for d in $(DIRS) ; do $(MAKE) -C $$d ; done

qml_plugin :
	set -e ; for d in $(QML_PLUGIN_DIRS) ; do qmake -makefile $$d/plugin.pro -o $$d/Makefile ; done
	set -e ; for d in $(QML_PLUGIN_DIRS) ; do $(MAKE) -C $$d ; done

runtime :
	sh runtime.sh

clean :
	set -e ; for d in $(DIRS) ; do $(MAKE) -C $$d clean ; done
	set -e ; for d in $(QML_PLUGIN_DIRS) ; do $(MAKE) -C $$d clean ; done

install :
	mkdir -p $(DESTDIR)/opt/cim
	mkdir -p $(DESTDIR)/opt/cim/python
	mkdir -p $(DESTDIR)/opt/cim/plugin
	mkdir -p $(DESTDIR)/opt/cim/data
	cp src/plugin/gconf.sh $(DESTDIR)/opt/cim/plugin 
	cp src/plugin/recover.sh $(DESTDIR)/opt/cim/plugin 
	cp src/plugin/inputpad_plugin.so $(DESTDIR)/usr/lib/hildon-input-method/ 
	cp src/plugin/me.maemo.chinese.inputpad.service $(DESTDIR)/usr/share/dbus-1/services/ 
	cp data/formated $(DESTDIR)/opt/cim/data
	cp -r python/qwert $(DESTDIR)/opt/cim/python
	cp -r python/ui $(DESTDIR)/opt/cim/python
	cp -r bin $(DESTDIR)/opt/cim/
	cp mcip $(DESTDIR)/opt/cim/
	rm $(DESTDIR)/opt/cim/bin/qml/*.so
	set -e ; for d in $(QML_PLUGIN_DIRS) ; do cp $$d/*.so $(DESTDIR)/opt/cim/bin/qml ; done
	if test "$(DESTDIR)x" == "x"; then \
		hildon-im-recache; \
		su user -c "sh /opt/cim/plugin/gconf.sh"; \
	fi

uninstall :
	su user -c "sh /opt/cim/plugin/recover.sh"
	rm /usr/lib/hildon-input-method/inputpad_plugin.so
	rm /usr/share/dbus-1/services/me.maemo.chinese.inputpad.service
	rm -rf /opt/cim
