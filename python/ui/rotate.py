from ctypes import *
import os
import sys
import time
from math import atan2
from pprint import pprint

xlib = cdll.LoadLibrary( "libX11.so.6" )
rr = cdll.LoadLibrary( "libXrandr.so.2" )

def get_rotation():
    f = open( "/sys/class/i2c-adapter/i2c-3/3-001d/coord", 'r' )
    coords = [ int(w) for w in f.readline().split() ]
    f.close()
    return coords

def rotate( angle ):
    rr.XRRSetScreenConfigAndRate( display, config, root, size, angle, rate, timestamp )

display = xlib.XOpenDisplay( os.getenv( "DISPLAY" ) )
screen = xlib.XDefaultScreen( display )
root = xlib.XDefaultRootWindow( display, screen )

class XRRScreenConfiguration( Structure ):
   pass

gsi = rr.XRRGetScreenInfo
gsi.restype = POINTER( XRRScreenConfiguration )
config = gsi( display, root )

current_time = c_ulong()
rr.XRRTimes.restpye = c_ulong
timestamp = rr.XRRTimes( display, screen, byref(current_time) )

xccr = rr.XRRConfigCurrentRate
xccr.restype = c_int
rate = xccr( config )

rotation = c_ushort()
size = rr.XRRConfigCurrentConfiguration( config, byref( rotation) )

#while True:
    #[x,y,z] = get_rotation()
    #print x,y,z
    #if y < -500:
        #rotate(1)
    #elif y > 500:
        #rotate(4)

    #elif x < -500:
        #rotate(2)
    #elif x > 500:
        #rotate(8)

    #time.sleep(1)

if __name__ == "__main__" :
    print get_rotation()
    rotate( int( sys.argv[1] ) )
