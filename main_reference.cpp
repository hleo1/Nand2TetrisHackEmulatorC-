#include <iostream>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>
#include <vector>
using Bit15 = std::bitset<15>;
using Bit16 = std::bitset<16>;

using namespace std;

using std::vector;

// // #include "header_files/classes.h"
// // #include "header_files/test.h"

// // int main() {
// //     // testROM();
// //     // testRAM();
// //     // testRegister();
// //     // testAddBitsets();
// //     // testALU();
// //     testRegister();
// // }





// Constants for window dimensions
// Constants for window dimensions
// Constants for window dimensions
// Constants for window dimensions
const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 512;

// Class to represent the screen
class Screen {
public:
    Screen() {
        // Initialize the screen array with 0 (black pixels)
        memset(pixels, 0, sizeof(pixels));
    }

    void draw(HDC hdc) {
        // Create a memory device context compatible with the specified device
        HDC memDC = CreateCompatibleDC(hdc);
        if (!memDC) return;

        // Create a bitmap compatible with the specified device context
        HBITMAP bmp = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
        if (!bmp) {
            DeleteDC(memDC);
            return;
        }

        // Select the bitmap into the memory device context
        SelectObject(memDC, bmp);

        // Set pixels in the memory device context
        for (int y = 0; y < SCREEN_HEIGHT; ++y) {
            for (int x = 0; x < SCREEN_WIDTH; ++x) {
                SetPixel(memDC, x, y, pixels[y][x] ? RGB(255, 255, 255) : RGB(0, 0, 0));
            }
        }

        // Copy the memory device context to the specified device context
        BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memDC, 0, 0, SRCCOPY);

        // Clean up
        DeleteObject(bmp);
        DeleteDC(memDC);
    }

    void setPixel(int x, int y, int color) {
        if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
            pixels[y][x] = color;
        }
    }

private:
    int pixels[SCREEN_HEIGHT][SCREEN_WIDTH];
};

// Class to represent the window
class MainWindow {
public:
    MainWindow(HINSTANCE hInstance, int nCmdShow) : hInstance(hInstance), nCmdShow(nCmdShow) {
        registerWindowClass();
        createWindow();
        showWindow();
    }

    void runMessageLoop() {
        MSG msg = { };
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        if (uMsg == WM_DESTROY) {
            PostQuitMessage(0);
            return 0;
        } else if (uMsg == WM_PAINT) {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            screen.draw(hdc);
            EndPaint(hwnd, &ps);
            return 0;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    static Screen screen;

private:
    HINSTANCE hInstance;
    int nCmdShow;
    HWND hwnd;

    void registerWindowClass() {
        const char CLASS_NAME[] = "Sample Window Class";
        WNDCLASS wc = { };

        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = CLASS_NAME;

        RegisterClass(&wc);
    }

    void createWindow() {
        hwnd = CreateWindowEx(
            0,                              // Optional window styles
            "Sample Window Class",          // Window class
            "256x512 Window",               // Window title
            WS_OVERLAPPEDWINDOW,            // Window style
            CW_USEDEFAULT, CW_USEDEFAULT,   // Position
            SCREEN_WIDTH, SCREEN_HEIGHT,    // Size
            NULL,                           // Parent window
            NULL,                           // Menu
            hInstance,                      // Instance handle
            NULL                            // Additional application data
        );

        if (hwnd == NULL) {
            exit(0);
        }
    }

    void showWindow() {
        ShowWindow(hwnd, nCmdShow);
    }
};

Screen MainWindow::screen;

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int nCmdShow = SW_SHOWDEFAULT;

    MainWindow mainWindow(hInstance, nCmdShow);

    // Example: Set some pixels on the screen
    MainWindow::screen.setPixel(50, 50, 1); // Set a white pixel
    MainWindow::screen.setPixel(100, 100, 1); // Set another white pixel

    mainWindow.runMessageLoop();

    return 0;
}



// class Screen
// {
// public:
//     void load16bitbinary(std::string sixteen_bit_string)
//     {
//         storage.push_back(Bit16(sixteen_bit_string));
//     }
//     void clear()
//     {
//         storage.clear();
//     }
//     int size()
//     {
//         return (storage.size());
//     }
//     void print()
//     {
//         //print into a screen where every 32 elements of storage form one row
//         //iterate through to the bit level. If 0 then white, if 1 then black.
//         //might want to keep the screen object as a private member variable.
//         for (int i = 0; i < storage.size(); i++)
//         {
//             cout << storage[i];
//             if (i != 0 && i % 32 == 0)
//             {
//                 cout << endl;
//             }
//         }
//     }

//     vector<Bit16> getStorage() {
//         return(storage);
//     }

// private:
//     vector<Bit16> storage;
// };

// int main()
// {
//     // Create a screen object and load some data into it
//     Screen test_screen;
//     for (int i = 0; i < 32; i++)
//     {
//         test_screen.load16bitbinary("0000000000000000");
//     }
//     for (int i = 0; i < 32; i++)
//     {
//         test_screen.load16bitbinary("1111111111111111");
//     }
//     for (int i = 0; i < 32; i++)
//     {
//         test_screen.load16bitbinary("0101010101010101");
//     }

//     test_screen.print();

   
//     return 0;
// }

