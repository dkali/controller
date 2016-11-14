controller
==========

Logitech F710 support for Raspberry pi

All you need to do is to
- connect F710 bluetooth receiver to rpi
- find your input device in the /dev/input
   additional info can be found here "cat /proc/bus/input/devices"
- update path to the input device in the .cpp file (if needed)

code compiled using gcc and tested on Raspbian OS