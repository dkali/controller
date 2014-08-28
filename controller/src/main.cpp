#include "../drivers/F710_driver.h"
#include <bcm2835.h>

using namespace std;

int main()
{
    //          = "/dev/input/by-id/usb-Logitech_Wireless_Gamepad_F710_E4D19A61-joystick";
    char path[] = "/dev/input/js0";
    F710 gamepad(path);

    gamepad.init();
    gamepad.listen_input();

    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));
    return 0;
}