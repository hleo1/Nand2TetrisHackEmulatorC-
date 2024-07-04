#include "modules/Keyboard.h"
#include "modules/RAM32k.h"
#include "modules/Screen.h"
#include "modules/Desk.h"


void testKeyboard() {
    while(true) {
            Sleep(500);
            Keyboard new_keyboard = Keyboard();
            // suggestion to combine update and get
            new_keyboard.updatePressedKey();
            std::cout << new_keyboard.getCurrentKey() << std::endl;
        }

}

int SDL_main(int argc, char *argv[])
{

    

    return 0;
}
