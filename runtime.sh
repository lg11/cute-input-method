#!/bin/sh

touch bin
rm -rf bin
mkdir bin
cd bin
ln -s ../mcip .
ln -s ../python/pinyinLookup .
ln -s ../python/qwert .
ln -s ../python/ui .
ln -s ../python/utils .
ln -s ../data .
ln -s qwert/qml .
ln -s ui/main.py ./mcip.py
python -OO -m py_compile ./mcip.py
