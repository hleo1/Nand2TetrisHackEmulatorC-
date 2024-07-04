// Keyboard.h

#ifndef KEYBOARD_H
#define KEYBOARD_H

/*
Simple Keyboard abstraction only supports
left, up, down, right arrows at the moment.
If nothing any of these NOT pressed, '0' is outputed.

Uses windows.h's GetAsyncKeyState(i) to get the CURRENT
pressed key.
*/

class Keyboard
{
public:
    Keyboard();
    bool updatePressedKey();
    char getCurrentKey() const;

private:
    char currentKey;
};

#endif // KEYBOARD_H
