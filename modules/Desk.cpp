#include "Desk.h"

Desk::Desk(int delay) : keyboard(), screen(512, 256), delay(delay)
{
    this->ram = RAM32K();
    this->ram.connectToKeyboard(&keyboard);
    this->screen.connectToRAM(&ram);
}

void Desk::run()
{
    std::cout << "Press keys to see which ones are pressed. Press ESC to exit." << std::endl;
    SDL_Thread *keyboardThread = SDL_CreateThread(runKeyboardThread, "KeyboardThread", this);
    screen.run();
    SDL_WaitThread(keyboardThread, NULL);
}

void Desk::loadScreenData(unsigned int index, const std::string &sixteen_bit_string)
{
    Bit16 newBit = Bit16(sixteen_bit_string);
    screen.pushToScreen(index, newBit);
}

int Desk::runKeyboardThread(void *data)
{
    Desk *desk = static_cast<Desk *>(data);
    while (true)
    {
        Sleep(desk->delay);
        if (!desk->runKeyboardProtocol())
        {
            desk->screen.cleanup();
            break;
        }
    }
    return 0;
}

bool Desk::runKeyboardProtocol()
{
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    {
        return false; // Exit the loop if the ESC key is pressed
    }
    keyboard.updatePressedKey();
    std::cout << keyboard.getCurrentKey() << std::endl;
    return true;
}
