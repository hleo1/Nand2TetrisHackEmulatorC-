
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
using Bit3 = std::bitset<3>;

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

std::bitset<15> addBitsets(const std::bitset<15>& a, const std::bitset<15>& b) {
    std::bitset<15> result;
    bool carry = false;

    for (std::size_t i = 0; i < 15; ++i) {
        bool bitA = a[i];
        bool bitB = b[i];

        // Sum the bits with the carry
        result[i] = bitA ^ bitB ^ carry;

        // Determine the carry for the next bit
        carry = (bitA && bitB) || (carry && (bitA || bitB));
    }

    return result;
}


class ALU {
    public :
    void ALU_calculate(Bit16 x, Bit16 y, bool zx, bool nx, bool zy, bool ny, bool f, bool no, Bit16& out, bool& zr, bool& ng) {
    // Implement the ALU function here according to the specifications
    if (zx) x = 0; // Zero the x input
    if (nx) x = ~x; // Negate the x input
    if (zy) y = 0; // Zero the y input
    if (ny) y = ~y; // Negate the y input
    if (f) out = addBitsets(x, y); else out = x & y; // Function selector: Add or AND
    if (no) out = ~out; // Negate the output
    zr = (out == 0); // Zero flag
    ng = out[15]; // Negative flag

    this->last_out = out;
    }

    Bit16 getLastOut() {
        return (last_out);
    }

    private :
    Bit16 last_out; 
};


class PC {
    public: 
    PC(): count(0) {};
    Bit15 getCount() {
        return count;
    }
    void loadWithConditions(Bit15 input, bool reset, bool load, bool inc, Bit15& out) {
        if (reset == true) {
            this->reset();
        } else if (load == true) {
            this->load(input, load);
        } else if (inc == true) {
            this->inc();
        }
    }
    
    private :
    void load(Bit15 new_count, bool load) {
        if (load) {
            count = new_count;
        }
    }
    void inc() {
        count = addBitsets(count, Bit15("000000000000001"));
    }
    void reset() {
        count = Bit15("000000000000000");
    }
    Bit15 count; 
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

Bit15 extractLast15Bits(const Bit16& bitset16) {
    Bit15 bitset15;
    int j = 0;
    for (int i = 1; i < 16; ++i) {
        bitset15[j++] = bitset16[i];
    }

    return bitset15;
}

Bit3 extractLast3Bits(const Bit16& bitset16) {
    Bit3 bitset3;
    int j = 0;
    for (int i = 13; i < 16; ++i) {
        bitset3[j++] = bitset16[i];
    }
}

void EightWayDMux(bool in1, bool in2, bool in3, bool in4, bool in5, bool in6, bool in7, bool in8, Bit3& instruction, bool& out) {
    unsigned long instruction_converted = instruction.to_ulong();

    switch(instruction_converted) {
        case 0: 
            out = in1;
        case 1:
            out = in2;
        case 2:
            out = in3;
        case 3:
            out = in4;
        case 4:
            out = in5;
        case 5:
            out = in6;
        case 6:
            out = in7;
        case 7:
            out = in8;
    }

}

class CPU {
    public: 
    void reset() {}
    void runNext(Bit16& instruction, Bit16& inM, bool& reset, Bit16& outM, bool& writeM, Bit15& addressM, Bit15& pc) {
        Bit16 last_out_alu = alu.getLastOut();

        bool load_condition = !instruction.test(0) || (instruction.test(0) && instruction.test(12));

        Bit16 first_mux16_out;
        Mux16(last_out_alu, instruction, load_condition,first_mux16_out);

        aReg.loadWithCondition(first_mux16_out, load_condition);

        Bit16 aRegOutput = aReg.getOut();
        Bit15 aRegLast15Output = extractLast15Bits(aRegOutput);

        Bit16 A_or_M;
        Mux16(aRegOutput, inM, instruction.test(3), A_or_M);

        bool dRegCondition = instruction.test(0) && instruction.test(11);
        dReg.loadWithCondition(last_out_alu, dRegCondition);
        Bit16 dRegOutput = dReg.getOut();

        Bit16 aluOut;
        bool zr;
        bool ng;
        alu.ALU_calculate(dRegOutput,A_or_M, instruction.test(4), instruction.test(5), instruction.test(6), instruction.test(7), instruction.test(8), instruction.test(9), aluOut, zr, ng);


        outM = alu.getLastOut();
        writeM = instruction.test(0) && instruction.test(12);
        addressM = aRegLast15Output;

        bool loadCondition;

        Bit3 jjj = extractLast3Bits(instruction);
        EightWayDMux(false, false, false, false, false, false, false, false, jjj, loadCondition);
        this->pc.loadWithConditions(aRegLast15Output, reset, loadCondition, true, pc);
    }

    private:
    ALU alu;
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

