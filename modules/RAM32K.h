#ifndef RAM32K_H
#define RAM32K_H

#include <vector>
#include <bitset>
#include <string>
#include <fstream>
#include "Keyboard.h"

using Bit15 = std::bitset<15>;
using Bit16 = std::bitset<16>;

class RAM32K
{
public:
    RAM32K();
    void read(Bit15 &address, Bit16 &in, bool load, Bit16 &out);
    void outputRAMToTxt();
    void connectToKeyboard(Keyboard *keyboard);
    Bit16 indexingRelativeToScreen(unsigned int i);
    void pushToIndexRelativeToScreen(unsigned int i, Bit16 sixteen_bits);

private:
    std::vector<Bit16> space;
    Keyboard *keyboard;
    unsigned int screen_index_start = 16384;
    unsigned int screen_index_end = 24575;
    unsigned int keyboard_index = 24756;

    void r(const Bit15 &address, Bit16 &out) const;
    void w(const Bit15 &address, Bit16 &in);
};

#endif // RAM32K_H
