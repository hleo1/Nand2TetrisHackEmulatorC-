// Keyboard.cpp

#include "Keyboard.h"
#include <windows.h>

Keyboard::Keyboard() : currentKey('0') {}

bool Keyboard::updatePressedKey()
{
    for (int i = 37; i <= 40; ++i)
    {
        if (GetAsyncKeyState(i) & 0x8000)
        { // Check if the high-order bit is set
            switch (i)
            {
            case 37:
                currentKey = 'l';
                break;
            case 38:
                currentKey = 'u';
                break;
            case 39:
                currentKey = 'r';
                break;
            case 40:
                currentKey = 'd';
                break;
            }
            return true;
        }
    }
    currentKey = '0';
    return false;
}

char Keyboard::getCurrentKey() const
{
    return currentKey;
}
