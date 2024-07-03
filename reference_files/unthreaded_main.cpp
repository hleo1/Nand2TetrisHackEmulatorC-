#include <iostream>
#include <windows.h>
#include <SDL2/SDL.h>
#include <vector>
#include <bitset>
#include <string>

using Bit16 = std::bitset<16>;

class Keyboard {
public:
    Keyboard() : currentKey('0') {}
    bool updatePressedKey() {
        for (int i = 37; i <= 40; ++i) {
            if (GetAsyncKeyState(i) & 0x8000) {  // Check if the high-order bit is set
                switch (i) {
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
    char getCurrentKey() const {
        return currentKey;
    }
private:
    char currentKey;
};

class Screen {
public:
    Screen(int width, int height);
    ~Screen();
    void load16bitbinary(const std::string& sixteen_bit_string);
    void clearStorage();
    int getStorageSize() const;
    void render();
    void run();
    void cleanup(); // Make cleanup public

private:
    void init();

    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    bool running;
    std::vector<Bit16> storage;
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

void Screen::load16bitbinary(const std::string& sixteen_bit_string) {
    storage.push_back(Bit16(sixteen_bit_string));
}

void Screen::clearStorage() {
    storage.clear();
}

int Screen::getStorageSize() const {
    return storage.size();
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

class Desk {
public:
    Desk(int delay) : keyboard(), screen(512, 256), delay(delay) {}

    void run() {
        std::cout << "Press keys to see which ones are pressed. Press ESC to exit." << std::endl;
        while (true) {
            Sleep(delay);
            if (!runKeyboardProtocol()) {
                screen.cleanup();
                break;
            }
            screen.render();
        }
    }

    void loadScreenData(const std::string& sixteen_bit_string) {
        screen.load16bitbinary(sixteen_bit_string);
    }

private:
    bool runKeyboardProtocol() {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            return false;  // Exit the loop if the ESC key is pressed
        }
        keyboard.updatePressedKey();
        std::cout << keyboard.getCurrentKey() << std::endl;
        return true;
    }

    Keyboard keyboard;
    Screen screen;
    int delay;
};

int SDL_main(int argc, char* argv[]) {
    Desk desk(50);

    // Load some data into the screen through Desk's public method
    for (int i = 0; i < 32; i++) {
        desk.loadScreenData("1111111111111111");
    }
    for (int i = 0; i < 32; i++) {
        desk.loadScreenData("0000000000000000");
    }
    for (int i = 0; i < 32; i++) {
        desk.loadScreenData("0101010101010101");
    }

    desk.run();
    return 0;
}
