#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <bitset>
#include "RAM32K.h"

using Bit16 = std::bitset<16>;

class Screen
{
public:
    Screen(int width, int height);
    ~Screen();
    void render();
    void run();
    void cleanup();
    void connectToRAM(RAM32K *ram);
    void pushToScreen(unsigned int i, Bit16 sixteen_bits);

private:
    void init();
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;
    bool running;
    RAM32K *RAM;
};

#endif // SCREEN_H
