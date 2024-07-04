#include "RAM32K.h"
#include <iostream>

RAM32K::RAM32K()
{
    Bit16 new_value = Bit16("0000000000000000");
    space = std::vector<Bit16>(32768, new_value);
}

void RAM32K::read(Bit15 &address, Bit16 &in, bool load, Bit16 &out)
{
    r(address, out);
    if (load)
    {
        w(address, in);
    }
}

void RAM32K::outputRAMToTxt()
{
    std::string filepath = "output_files/RAMoutput.txt";
    std::ofstream file(filepath);
    if (file.is_open())
    {
        for (const auto &value : space)
        {
            file << value << std::endl;
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
}

void RAM32K::connectToKeyboard(Keyboard *keyboard)
{
    this->keyboard = keyboard;
}

Bit16 RAM32K::indexingRelativeToScreen(unsigned int i)
{
    return space[i + this->screen_index_start];
}

void RAM32K::pushToIndexRelativeToScreen(unsigned int i, Bit16 sixteen_bits)
{
    space[i + this->screen_index_start] = sixteen_bits;
}

void RAM32K::r(const Bit15 &address, Bit16 &out) const
{
    if (address.to_ulong() == keyboard_index)
    {
        out = keyboard->getCurrentKey();
    }
    else
    {
        out = space[address.to_ulong()];
    }
}

void RAM32K::w(const Bit15 &address, Bit16 &in)
{
    space[address.to_ulong()] = in;
}
