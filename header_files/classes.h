
#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>

#include <bitset>
using Bit15 = std::bitset<15>;
using Bit16 = std::bitset<16>;

using std::string;
using std::cout;
using std::endl;

class ROM32K {
    public:
    ROM32K() : space{new Bit16[32768]}, size{32768} {
    }
    void read(const Bit15& address, Bit16& out) const {
        out = space[address.to_ulong()];
    }
    void readToROMFromTxt(const string& filepath) {
        std::ifstream file(filepath);
        std::string str;
        int index = 0;
        while (std::getline(file, str))
        {
            // Process str
            space[index] = Bit16(str);
            index++;
        }
    }
    void outputROMToTxt() {
        string filepath = "output_files/ROMoutput.txt";
        std::ofstream file(filepath);
        if (file.is_open()) {
            for (unsigned int i = 0; i < size; i++) {
                file << space[i] << endl;
            }
            file.close();
        } else {
            cout << "Unable to open file" << endl;
        }
    }
    ~ROM32K() {
        delete[] space;
    }
private:
    Bit16* space;
    unsigned int size;
};

class RAM32K {
public:
RAM32K() : space{new Bit16[32768]}, size{32768} {};
void read(Bit15& address, Bit16& in, bool load, Bit16& out) {
    //always output whatever is in the address NOW
    r(address, out);
    //save whatever is in the input after, so that it can be accessed after
    if (load == true) {
        w(address, in);
    }
}

void outputRAMToTxt() {
        string filepath = "output_files/RAMoutput.txt";
        std::ofstream file(filepath);
        if (file.is_open()) {
            for (unsigned int i = 0; i < size; i++) {
                file << space[i] << endl;
            }
            file.close();
        } else {
            cout << "Unable to open file" << endl;
        }
}

private:
Bit16* space;
unsigned int size;
unsigned int screen_index_start = 16384;
unsigned int screen_index_end = 24575;
unsigned int keyboard_index = 24756;

void r(const Bit15& address, Bit16& out) const {
    out = space[address.to_ulong()];
}
void w(const Bit15& address, Bit16& in) {
    space[address.to_ulong()] = in;
}
};

class Register {
    public:
    Register(): data() {}
    Bit16 getOut() {return data;}
    void loadWithCondition(Bit16& in, bool c) {
        if (c) data = in;
    }
    private:
    Bit16 data;
};

std::bitset<16> addBitsets(const std::bitset<16>& a, const std::bitset<16>& b) {
    std::bitset<16> result;
    bool carry = false;

    for (std::size_t i = 0; i < 16; ++i) {
        bool bitA = a[i];
        bool bitB = b[i];

        // Sum the bits with the carry
        result[i] = bitA ^ bitB ^ carry;

        // Determine the carry for the next bit
        carry = (bitA && bitB) || (carry && (bitA || bitB));
    }

    return result;
}


void ALU(Bit16 x, Bit16 y, bool zx, bool nx, bool zy, bool ny, bool f, bool no, Bit16& out, bool& zr, bool& ng) {
    // Implement the ALU function here according to the specifications
    if (zx) x = 0; // Zero the x input
    if (nx) x = ~x; // Negate the x input
    if (zy) y = 0; // Zero the y input
    if (ny) y = ~y; // Negate the y input
    if (f) out = addBitsets(x, y); else out = x & y; // Function selector: Add or AND
    if (no) out = ~out; // Negate the output
    zr = (out == 0); // Zero flag
    ng = out[15]; // Negative flag
}

class PC {
    public: 
    PC(): count(0) {};
    Bit16 getCount() {
        return count;
    }
    void load(Bit16 new_count, bool load) {
        if (load) {
            count = new_count;
        }
    }
    void inc() {
        count = addBitsets(count, Bit16("0000000000000001"));
    }
    void reset() {
        count = Bit16("0000000000000000");
    }
    private :
    Bit16 count; 
};

void Mux16(Bit16& input_one, Bit16& input_two, bool c, Bit16& out) {
    if (c == false) {
        out = input_one;
    } else {
        out = input_two;
    }
}


/*
TODO: 
Test PC with test suite online
How to bind the keyboard/screen wtih the RAM locations?
Convert ALU to class. Need to retain state. ALU put

*/

class CPU {
    public: 
    void reset() {}
    void runNext(Bit16 instruction, Bit16 inM) {


    }

    private:
    Register aReg;
    Register dReg;
    PC pc;
    Bit16 outM;
    Bit16 addressM;
    Bit16 pcOut;
    bool writeM;
};

//16 bit Emulator Start
class HackEmulator {
    public:
    void reset() {}
    
    private:
    CPU cpu;
    RAM32K ram;
    ROM32K rom;
};


#endif 

