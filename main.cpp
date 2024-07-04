#include "modules/Keyboard.h"
#include "modules/RAM32k.h"
#include "modules/Screen.h"
#include "modules/Desk.h"

int SDL_main(int argc, char *argv[])
{
    Desk desk(50);

    // Load some data into the screen through Desk's public method
    unsigned int count = 0;

    for (int i = 0; i < 32; i++)
    {
        desk.loadScreenData(count, "1111111111111111");
        count++;
    }
    for (int i = 0; i < 32; i++)
    {
        desk.loadScreenData(count, "0000000000000000");
        count++;
    }
    for (int i = 0; i < 32; i++)
    {
        desk.loadScreenData(count, "0101010101010101");
        count++;
    }

    desk.ram.outputRAMToTxt();

    desk.run();
    return 0;
}
