#ifndef DESK_H
#define DESK_H

#include <iostream>
#include <windows.h>
#include <bitset>
#include "Keyboard.h"
#include "RAM32K.h"
#include "Screen.h"

using Bit15 = std::bitset<15>;
using Bit16 = std::bitset<16>;

class Desk
{
public:
    Desk(int delay);
    void run();
    void loadScreenData(unsigned int index, const std::string &sixteen_bit_string);

    RAM32K ram;

private:
    static int runKeyboardThread(void *data);
    bool runKeyboardProtocol();

    Keyboard keyboard;
    Screen screen;
    int delay;
};

#endif // DESK_H
