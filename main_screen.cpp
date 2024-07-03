#include <SDL2/SDL.h>
#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>

using Bit16 = std::bitset<16>;
using namespace std;

class Screen {
public:
    Screen(int width, int height);
    ~Screen();
    void run();
    void load16bitbinary(std::string sixteen_bit_string);
    void clearStorage();
    int getStorageSize();
    void printStorage();

private:
    void init();
    void cleanup();
    void render();

    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    bool running;
    vector<Bit16> storage;
};

Screen::Screen(int width, int height) : window(nullptr), renderer(nullptr), width(width), height(height), running(true) {
    init();
}

Screen::~Screen() {
    cleanup();
}

void Screen::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        running = false;
        return;
    }

    window = SDL_CreateWindow("SDL App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        running = false;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        running = false;
        return;
    }

    // Set render color to white and clear the renderer
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Screen::cleanup() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void Screen::render() {
    // Set render color to white (background)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Set render color to black (pixels)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Iterate over storage. Every 32 elements of storage represents a row.
    // Each element has 16 bits. 1 to mark as black and 0 to mark as white.
    for (int i = 0; i < storage.size(); ++i) {
        int row = i / 32;
        int col_offset = (i % 32) * 16;
        for (int bit = 0; bit < 16; ++bit) {
            if (storage[i][bit]) {
                SDL_RenderDrawPoint(renderer, col_offset + bit, row);
            }
        }
    }

    // Present the renderer
    SDL_RenderPresent(renderer);
}


void Screen::run() {
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
        render();
    }
}

void Screen::load16bitbinary(std::string sixteen_bit_string) {
    storage.push_back(Bit16(sixteen_bit_string));
}

void Screen::clearStorage() {
    storage.clear();
}

int Screen::getStorageSize() {
    return storage.size();
}

void Screen::printStorage() {
    run();
}

int main(int argc, char* argv[]) {
    // Create an Screen object and load some data into it
    Screen app(512, 256);
    
    for (int i = 0; i < 32; i++) {
        app.load16bitbinary("1111111111111111");
    }
    for (int i = 0; i < 32; i++) {
        app.load16bitbinary("0000000000000000");
    }
    for (int i = 0; i < 32; i++) {
        app.load16bitbinary("0101010101010101");
    }

    app.printStorage();
    return 0;
}
