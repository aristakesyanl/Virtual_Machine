#include"VirtualMachine.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<string>
int main(int argc, char* argv[]) {
    
    if(argc<2){
        std::cerr<<"No Arguments Provided"<<std::endl;
    }
    
    for (int i = 1; i < argc; i++) {

        std::string str(argv[i]);
        VirtualMachine a(str);
        a.run();
        a.watchRegisters();
    }
    
}
