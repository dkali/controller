#include "F710_driver.h"

using namespace std;

F710::F710(char* device)
{
    dev = device;
    memset(buf, 0, sizeof buf);
}

int F710::init()
{
    fd = open(dev, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }

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

    state_map[JSKEY_PRESS] = "pressed";
    state_map[JSKEY_RELEASE] = "released";
    state_map[JSKEY_CROSS_LOW_VALUE] = "low value";
    state_map[JSKEY_CROSS_HIGH_VALUE] = "high value";
    state_map[JSKEY_CROSS_RELEASED] = "released";

    return 0;
}

void F710::listen_input()
{
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
}