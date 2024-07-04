@echo off
g++ -c modules/Keyboard.cpp -o executable/Keyboard.o
g++ -c modules/RAM32K.cpp -o  executable/RAM32K.o
g++ -I src/include -c modules/Screen.cpp -o executable/Screen.o
g++ -I src/include -c modules/Desk.cpp -o executable/Desk.o

g++ -I src/include -c main.cpp -o executable/main.o

g++ executable/Keyboard.o executable/RAM32K.o executable/Screen.o executable/Desk.o executable/main.o -o executable/main -L src/lib -lmingw32 -lSDL2main -lSDL2
if %errorlevel%==0 (
    .\executable\main.exe
)