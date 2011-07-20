DIRS = data
QML_PLUGIN_DIRS = src/mousetrack

ALL : qml_plugin maliit engine
	set -e ; for d in $(DIRS) ; do $(MAKE) -C $$d ; done

maliit :
	qmake -makefile src/maliit/plugin.pro -o src/maliit/Makefile 
	$(MAKE) -C src/maliit

engine :
	qmake -makefile src/engine/plugin.pro -o src/maliit/Makefile 
	$(MAKE) -C src/engine

qml_plugin :
	set -e ; for d in $(QML_PLUGIN_DIRS) ; do qmake -makefile $$d/plugin.pro -o $$d/Makefile ; done
	set -e ; for d in $(QML_PLUGIN_DIRS) ; do $(MAKE) -C $$d ; done

clean :
	set -e ; for d in $(DIRS) ; do $(MAKE) -C $$d clean ; done
	set -e ; for d in $(QML_PLUGIN_DIRS) ; do $(MAKE) -C $$d clean ; done
	$(MAKE) -C src/host clean

install :
	mkdir -p $(DESTDIR)/usr/share/cuteinputmethod
	mkdir -p $(DESTDIR)/usr/share/cuteinputmethod/maliit
	mkdir -p $(DESTDIR)/usr/share/cuteinputmethod/maliit/qml
	mkdir -p $(DESTDIR)/usr/share/cuteinputmethod/maliit/qml/mouseArea
	mkdir -p $(DESTDIR)/usr/share/cuteinputmethod/plugin
	mkdir -p $(DESTDIR)/usr/share/cuteinputmethod/data
	mkdir -p $(DESTDIR)/usr/lib/meego-im-plugins
	cp src/maliit/qml/*.qml $(DESTDIR)/usr/share/cuteinputmethod/maliit/qml
	cp src/maliit/qml/*.js $(DESTDIR)/usr/share/cuteinputmethod/maliit/qml
	cp src/maliit/qml/qmldir $(DESTDIR)/usr/share/cuteinputmethod/maliit/qml
	cp src/maliit/qml/mouseArea/*.qml $(DESTDIR)/usr/share/cuteinputmethod/maliit/qml/mouseArea
	cp src/maliit/qml/mouseArea/qmldir $(DESTDIR)/usr/share/cuteinputmethod/maliit/qml/mouseArea
	cp data/formated $(DESTDIR)/usr/share/cuteinputmethod/data
	cp data/prePhrase.py $(DESTDIR)/usr/share/cuteinputmethod/data
	set -e ; for d in $(QML_PLUGIN_DIRS) ; do cp $$d/*.so $(DESTDIR)/usr/share/cuteinputmethod/maliit/qml/mouseArea ; done
	cp src/engine/libengine.so $(DESTDIR)/usr/share/cuteinputmethod/maliit/qml
	cp src/maliit/libcuteinputmethod.so $(DESTDIR)/usr/lib/meego-im-plugins

uninstall :
	rm -rf $(DESTDIR)/usr/share/cuteinputmethod
	rm $(DESTDIR)/usr/lib/meego-im-plugins/libcuteinputmethod.so
