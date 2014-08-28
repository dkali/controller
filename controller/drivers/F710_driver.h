#ifndef F710_DRIVER
#define F710_DRIVER

#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <map>

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

class F710{
private:
    char *dev;
    ssize_t n;
    int fd;
    int buf[2];

    map<int, std::string> key_map;
    map<int, std::string> state_map;

public:
    F710(char* device);
    int init();
    void listen_input();

};

#endif //F710_DRIVER