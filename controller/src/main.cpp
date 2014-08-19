#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

#include <map>

static const char *const evval[3] = {
    "RELEASED",
    "PRESSED ",
    "REPEATED"
};

#define JSKEY_A     0x001
#define JSKEY_B     0x101
#define JSKEY_X     0x201
#define JSKEY_Y     0x301
#define JSKEY_LB    0x401
#define JSKEY_RB    0x501
#define JSKEY_MODE  0x601
#define JSKEY_START 0x701
#define JSKEY_HOME  0x801

#define JSKEY_LEFTSTICK  0x901
#define JSKEY_RIGHTSTICK 0xa01

#define JSKEY_PRESS 0x001
#define JSKEY_RELEASE 0x0

#define JSKEY_LT 0x202
#define JSKEY_RT 0x502

#define JSKEY_CROSS_HORIZONT 0x602
#define JSKEY_CROSS_VERTICAL 0x702
#define JSKEY_LEFTSTICK_HORIZONT 0x002
#define JSKEY_LEFTSTICK_VERTICAL 0x102
#define JSKEY_RIGHTSTICK_HORIZONT 0x302
#define JSKEY_RIGHTSTICK_VERTICAL 0x402

#define JSKEY_CROSS_LOW_VALUE 0xffff8001
#define JSKEY_CROSS_HIGH_VALUE 0x7fff
#define JSKEY_CROSS_RELEASED 0x0



using namespace std;

int main()
{
    // const char *dev = "/dev/input/by-id/usb-Logitech_Wireless_Gamepad_F710_E4D19A61-joystick";
    const char *dev = "/dev/input/js0";
    ssize_t n;
    int fd;

    int buf[2];

    fd = open(dev, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }

    map<int, std::string> key_map;
    key_map[JSKEY_A] = "A";
    key_map[JSKEY_B] = "B";
    key_map[JSKEY_X] = "X";
    key_map[JSKEY_Y] = "Y";
    key_map[JSKEY_LB] = "LB";
    key_map[JSKEY_RB] = "RB";
    key_map[JSKEY_MODE] = "Mode";
    key_map[JSKEY_START] = "Start";
    key_map[JSKEY_HOME] = "Home";
    key_map[JSKEY_LEFTSTICK] = "Left Stick";
    key_map[JSKEY_RIGHTSTICK] = "Right Stick";
    key_map[JSKEY_LT] = "LT";
    key_map[JSKEY_RT] = "RT";
    key_map[JSKEY_CROSS_HORIZONT] = "cross horizont";
    key_map[JSKEY_CROSS_VERTICAL] = "cross vertical";
    key_map[JSKEY_LEFTSTICK_HORIZONT] = "left stick horizont";
    key_map[JSKEY_LEFTSTICK_VERTICAL] = "left stick vertical";
    key_map[JSKEY_RIGHTSTICK_HORIZONT] = "right stick horizont";
    key_map[JSKEY_RIGHTSTICK_VERTICAL] = "right stick vertical";
    
    map<int, std::string> state_map;
    state_map[JSKEY_PRESS] = "pressed";
    state_map[JSKEY_RELEASE] = "released";
    state_map[JSKEY_CROSS_LOW_VALUE] = "low value";
    state_map[JSKEY_CROSS_HIGH_VALUE] = "high value";
    state_map[JSKEY_CROSS_RELEASED] = "released";

    while (1) {
        memset(buf, 0, sizeof buf);
        n = read(fd, &buf, sizeof buf);
        n = n / sizeof(int);
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        }

        // printf("--------------------\n");
        // printf("read %d bytes\n", n);
        // for (int i=0; i<n; i++)
        // {
        //     printf("%x \n", buf[i]);
        // }

        unsigned short btn = buf[1] >> 16;
        short val = (short)(buf[1] & 0xffff);

        if (btn == JSKEY_LT || btn == JSKEY_RT)
        {
            unsigned short prs_val = val + 32768;
            val = (unsigned short) (((long)prs_val)*100/65536);
            // printf("button = %x, percantage = %d\n", btn, val);
            cout << key_map[btn] << " percentage = " << val << endl;
        }
        else if (btn == JSKEY_LEFTSTICK_HORIZONT || btn == JSKEY_LEFTSTICK_VERTICAL ||
                 btn == JSKEY_RIGHTSTICK_HORIZONT || btn == JSKEY_RIGHTSTICK_VERTICAL)
        {
            // unsigned short prs_val = val + 32768;
            val = val*100/32767;
            cout << key_map[btn] << " percentage = " << val << endl;
        }
        else
        // printf("button = %x, value = %x\n", btn, val);
        cout << key_map[btn] << " is " << state_map[val] << endl;

    }
    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));
    return EXIT_FAILURE;
}