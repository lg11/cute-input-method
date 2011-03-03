DIRS = plugin ui src data

ALL :
	set -e ; for d in $(DIRS) ; do $(MAKE) -C $$d ; done

clean :
	set -e ; for d in $(DIRS) ; do $(MAKE) -C $$d clean ; done

install :
	mkdir -p /opt/cim
	mkdir -p /opt/cim/ui
	mkdir -p /opt/cim/plugin
	mkdir -p /opt/cim/data
	cp src/libbackend.so /opt/cim/ui/backend.so
	cp plugin/inputpad_plugin.so /opt/cim/plugin
	cp plugin/gconf.sh /opt/cim/plugin 
	cp plugin/recover.sh /opt/cim/plugin 
	cp plugin/me.maemo.chinese.inputpad.service /opt/cim/plugin
	ln -s /opt/cim/plugin/inputpad_plugin.so /usr/lib/hildon-input-method/
	ln -s /opt/cim/plugin/me.maemo.chinese.inputpad.service /usr/share/dbus-1/services/
	cp data/formated /opt/cim/data
	cp ui/*.py /opt/cim/ui
	cp ui/*.pyo /opt/cim/ui
	cp run.sh /opt/cim
	hildon-im-recache
	su user -c "sh /opt/cim/plugin/gconf.sh"

uninstall :
	su user -c "sh /opt/cim/plugin/recover.sh"
	rm /usr/lib/hildon-input-method/inputpad_plugin.so
	rm /usr/share/dbus-1/services/me.maemo.chinese.inputpad.service
	rm -rf /opt/cim
