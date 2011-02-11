#-!- coding=utf-8 -!-
import backend
import sys

backend.load( "../data/formated" )
print "done"

while True :
    code = sys.stdin.readline()[:-1]
    for c in code :
        backend.append( c )
    i = 0
    r = backend.get( i )
    while r and i < 3 :
    #while r :
        print r[0], r[1]
        print type(r[0]), type(r[1])
        i = i + 1
        r = backend.get( i )
    backend.clear()
