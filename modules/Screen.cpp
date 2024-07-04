#include "Screen.h"
#include <iostream>

Screen::Screen(int width, int height) : window(nullptr), renderer(nullptr), width(width), height(height), running(true)
{
    init();
}

Screen::~Screen()
{
    cleanup();
}

void Screen::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int i = 0; i < 8192; ++i)
    {
        int row = i / 32;
        int col_offset = (i % 32) * 16;
        for (int bit = 0; bit < 16; ++bit)
        {
            if (RAM->indexingRelativeToScreen(i)[bit])
            {
                SDL_RenderDrawPoint(renderer, col_offset + bit, row);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void Screen::run()
{
    SDL_Event e;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
        }
        render();
    }
}

void Screen::cleanup()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void Screen::connectToRAM(RAM32K *ram)
{
    this->RAM = ram;
}

void Screen::pushToScreen(unsigned int i, Bit16 sixteen_bits)
{
    this->RAM->pushToIndexRelativeToScreen(i, sixteen_bits);
}

void Screen::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        running = false;
        return;
    }

    window = SDL_CreateWindow("SDL App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        running = false;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        running = false;
        return;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
