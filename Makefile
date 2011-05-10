DIRS = plugin python data

ALL : runtime
	#qmake -makefile src/backend.pro -o src/Makefile
	set -e ; for d in $(DIRS) ; do $(MAKE) -C $$d ; done

runtime :
	sh runtime.sh

clean :
	set -e ; for d in $(DIRS) ; do $(MAKE) -C $$d clean ; done

install :
	mkdir -p $(DESTDIR)/opt/cim
	mkdir -p $(DESTDIR)/opt/cim/python
	mkdir -p $(DESTDIR)/opt/cim/plugin
	mkdir -p $(DESTDIR)/opt/cim/data
	cp src/libbackend.so $(DESTDIR)/opt/cim/ui/backend.so
	cp plugin/gconf.sh $(DESTDIR)/opt/cim/plugin 
	cp plugin/recover.sh $(DESTDIR)/opt/cim/plugin 
	cp plugin/inputpad_plugin.so $(DESTDIR)/usr/lib/hildon-input-method/ 
	cp plugin/me.maemo.chinese.inputpad.service $(DESTDIR)/usr/share/dbus-1/services/ 
	cp data/formated $(DESTDIR)/opt/cim/data
	cp -r python/* $(DESTDIR)/opt/cim/python
	cp -r bin $(DESTDIR)/opt/cim/
	cp run.sh $(DESTDIR)/opt/cim
	if test "$(DESTDIR)x" == "x"; then \
		hildon-im-recache; \
		su user -c "sh /opt/cim/plugin/gconf.sh"; \
	fi

uninstall :
	su user -c "sh /opt/cim/plugin/recover.sh"
	rm /usr/lib/hildon-input-method/inputpad_plugin.so
	rm /usr/share/dbus-1/services/me.maemo.chinese.inputpad.service
	rm -rf /opt/cim
