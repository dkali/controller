controller
==========

Logitech F710 support for raspberry pi

All you need to do is to
1) connect F710 bluetooth receiver to rpi
2) find your input device in the /dev/input
   additional info can be found here "cat /proc/bus/input/devices"
3) update path to the input device in the .cpp file (if needed)