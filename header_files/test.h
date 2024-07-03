#ifndef TESTS_H
#define TESTS_H

#include "classes.h"
void testROM() {
    ROM32K ROM;
    ROM.readToROMFromTxt("test_input/Mult_Bin.txt");

    Bit15 address = Bit15("000000000000000");
    Bit16 out_value;
    ROM.read(address, out_value);
    cout << out_value << endl;


    ROM.outputROMToTxt();
}
void testRAM() {
    cout << "Hey" << endl;
    RAM32K RAM;
    cout << "Current value at b000000000000000:" << endl;
    Bit15 address = Bit15("000000000000000");
    Bit16 new_value = Bit16("1111111111111111");
    Bit16 out;
    cout << out << endl;
    RAM.read(address, new_value, true, out);
    cout << out << endl;
    RAM.read(address, new_value, false, out);

    cout << out << endl;
    RAM.outputRAMToTxt();
}

void testRegister() {
    Register testReg;
    cout << testReg.getOut() << endl;
    Bit16 new_in = Bit16("1111111111111111");
    
    testReg.loadWithCondition(new_in, false);
    cout << testReg.getOut() << endl;
    testReg.loadWithCondition(new_in, true);
    cout << testReg.getOut() << endl;
}

void testAddBitsets() {
    Bit16 fifteen = Bit16("0000000000001111");
    Bit16 sixteen = Bit16("0000000000010000");
    cout << fifteen.to_ulong() << endl;
    cout << sixteen.to_ulong() << endl;
    Bit16 result = addBitsets(fifteen, sixteen);
    cout << result.to_ulong() << endl;
}

void addTwoNumbers(string& a, string& b) {
    Bit16 out;
    Bit16 fifteen = Bit16(a);
    Bit16 sixteen = Bit16(b);
    cout << "first num is" << endl;
    cout << fifteen.to_ulong() << endl;
    cout << "second num is" << endl;
    cout << sixteen.to_ulong() << endl;

    bool zero;
    bool negative;
    ALU(fifteen, sixteen, false, false, false, false, true, false, out, zero, negative);

    cout << out << endl;
    cout << zero << endl;
    cout << negative << endl;
}

void andTwoNumbers(string& a, string& b) {
    Bit16 out;
    Bit16 fifteen = Bit16(a);
    Bit16 sixteen = Bit16(b);
    cout << "first num is" << endl;
    cout << fifteen.to_ulong() << endl;
    cout << "second num is" << endl;
    cout << sixteen.to_ulong() << endl;

    bool zero;
    bool negative;
    ALU(fifteen, sixteen, false, false, false, false, false, false, out, zero, negative);

    cout << out << endl;
    cout << zero << endl;
    cout << negative << endl;
}

/*


0   0   0   0   0   0   0   0   0   0   0   0   0    0    0   0   0   0
                                    128   64   32    16   8   4   2   1

*/



void testALU() {    
    Bit16 allZeros = Bit16("0000000000000000");
    Bit16 allOnes = Bit16("1111111111111111");
    Bit16 out;
    bool zr_out;
    bool ng_out;

   
 ALU(allZeros, allOnes, true, false, true, false, true, false, out, zr_out, ng_out);
    cout << (out == Bit16("0000000000000000")) << endl;

    ALU(allZeros, allOnes, true, true, true, true, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("0000000000000001")) << endl;

    ALU(allZeros, allOnes, true, true, true, false, true, false, out, zr_out, ng_out);
    cout << (out == Bit16("1111111111111111")) << endl;
    ALU(allZeros, allOnes, false, false, true, true, false, false, out, zr_out, ng_out);
    cout << (out == Bit16("0000000000000000")) << endl;

    ALU(allZeros, allOnes, true, true, false, false, false, false, out, zr_out, ng_out);
    cout << (out == Bit16("1111111111111111")) << endl;

    ALU(allZeros, allOnes, false, false, true, true, false, true, out, zr_out, ng_out);
    cout << (out == Bit16("1111111111111111")) << endl;

    ALU(allZeros, allOnes, true, true, false, false, false, true, out, zr_out, ng_out);
    cout << (out == Bit16("0000000000000000")) << endl;

    ALU(allZeros, allOnes, false, false, true, true, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("0000000000000000")) << endl;

    ALU(allZeros, allOnes, true, true, false, false, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("0000000000000001")) << endl;

    ALU(allZeros, allOnes, false, true, true, true, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("0000000000000001")) << endl;

    ALU(allZeros, allOnes, true, true, false, true, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("0000000000000000")) << endl;

    ALU(allZeros, allOnes, false, false, true, true, true, false, out, zr_out, ng_out);
    cout << (out == Bit16("1111111111111111")) << endl;

    ALU(allZeros, allOnes, true, true, false, false, true, false, out, zr_out, ng_out);
    cout << (out == Bit16("1111111111111110")) << endl;

    ALU(allZeros, allOnes, false, false, false, false, true, false, out, zr_out, ng_out);
    cout << (out == Bit16("1111111111111111")) << endl;

    ALU(allZeros, allOnes, false, true, false, false, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("0000000000000001")) << endl;

    ALU(allZeros, allOnes, false, false, false, true, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("1111111111111111")) << endl;

    ALU(allZeros, allOnes, false, false, false, false, false, false, out, zr_out, ng_out);
    cout << (out == Bit16("0000000000000000")) << endl;

    ALU(allZeros, allOnes, false, true, false, true, false, true, out, zr_out, ng_out);
    cout << (out == Bit16("1111111111111111")) << endl;


    Bit16 inOne = Bit16("0101101110100000");
    Bit16 inTwo = Bit16("0001111011010010");

    ALU(inOne, inTwo, true, false, true, false, true, false, out, zr_out, ng_out);
    cout << (out == Bit16("0000000000000000")) << endl;

    ALU(inOne, inTwo, true, true, true, true, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("0000000000000001")) << endl;

    ALU(inOne, inTwo, true, true, true, false, true, false, out, zr_out, ng_out);
    cout << (out == Bit16("1111111111111111")) << endl;

    ALU(inOne, inTwo, false, false, true, true, false, false, out, zr_out, ng_out);
    cout << (out == Bit16("0101101110100000")) << endl;

    ALU(inOne, inTwo, true, true, false, false, false, false, out, zr_out, ng_out);
    cout << (out == Bit16("0001111011010010")) << endl;

    ALU(inOne, inTwo, false, false, true, true, false, true, out, zr_out, ng_out);
    cout << (out == Bit16("1010010001011111")) << endl;

    ALU(inOne, inTwo, true, true, false, false, false, true, out, zr_out, ng_out);
    cout << (out == Bit16("1110000100101101")) << endl;

    ALU(inOne, inTwo, false, false, true, true, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("1010010001100000")) << endl;

    ALU(inOne, inTwo, true, true, false, false, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("1110000100101110")) << endl;

    ALU(inOne, inTwo, false, true, true, true, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("0101101110100001")) << endl;

    ALU(inOne, inTwo, true, true, false, true, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("0001111011010011")) << endl;

    ALU(inOne, inTwo, false, false, true, true, true, false, out, zr_out, ng_out);
    cout << (out == Bit16("0101101110011111")) << endl;

    ALU(inOne, inTwo, true, true, false, false, true, false, out, zr_out, ng_out);
    cout << (out == Bit16("0001111011010001")) << endl;

    ALU(inOne, inTwo, false, false, false, false, true, false, out, zr_out, ng_out);
    cout << (out == Bit16("0111101001110010")) << endl;

    ALU(inOne, inTwo, false, true, false, false, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("0011110011001110")) << endl;

    ALU(inOne, inTwo, false, false, false, true, true, true, out, zr_out, ng_out);
    cout << (out == Bit16("1100001100110010")) << endl;

    ALU(inOne, inTwo, false, false, false, false, false, false, out, zr_out, ng_out);
    cout << (out == Bit16("0001101010000000")) << endl;

    ALU(inOne, inTwo, false, true, false, true, false, true, out, zr_out, ng_out);
    cout << (out == Bit16("0101111111110010")) << endl;

}


#endif // TESTS_H