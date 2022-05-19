#include<string>
#include<map>
#include<utility>
#include<vector>
#include<fstream>
#include<map>
/***********************************************
 * Emulator receives machine code in hexadecimal
 * form.
 
************************************************/


#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H
class VirtualMachine {
public:
    VirtualMachine(std::string&);
    void run();
    void watchRegisters();
private:
    std::string content;
    //6 general-purpose registers
    //Counter
    //Input
    //Output
    int R[9]={0};
    void ALU(int, int, int, int);
    void Condition(int, int, int, int);
    int hexToDec(char, char);
    std::string hexToBin(char, char);
    std::map<char, std::string> hexBin{
        {'0', "0000"};
        {'1', "0001"};
        {'2', "0010"};
        {'3', "0011"};
        {'4', "0100"};
        {'5', "0101"};
        {'6', "0110"};
        {'7', "0111"};
        {'8', "1000"};
        {'9', "1001"};
        {'A', "1010"};
        {'B', "1011"};
        {'C', "1100"};
        {'D', "1101"};
        {'E', "1110"};
        {'F', "1111"};
    }

    std::map<char, int> hexDec{
        {'0', 0};
        {'1', 1};
        {'2', 2};
        {'3', 3};
        {'4', 4};
        {'5', 5};
        {'6', 6};
        {'7', 7};
        {'8', 8};
        {'9', 9};
        {'A', 10};
        {'B', 11};
        {'C', 12};
        {'D', 13};
        {'E', 14};
        {'F', 15};
    }
};

#endif
