#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<bitset>
#include<locale.h>
#include<algorithm>
#include"VirtualMachine.h"

VirtualMachine::VirtualMachine(std:: string& filename){

    std::ifstream ifs(filename);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
    ifs.close();

    content.erase(remove(content.begin(), content.end(),' '), content.end());

    
	if((int)content.size()%8!=0){
		throw std::invalid_argument("Invalid Input Format");
	}

    for(int i=0; i<(int)content.size();i++){
		if(!isdigit(content[i])&&(content[i]-'A'< 0 ||content[i]-'A'>5)){
			throw std::invalid_argument("Invalid Symbol");
		}
    }
}

void VirtualMachine::run(){
	int Count=R[6];

    while(Count<(int)content.size()){

    	//get opcode
		//if 7th or 8th bits are not set or opcode is for conditional statement
		//it is arithmetic instruction with registers
		std::string op1=hexToBin(content[Count], content[Count+1]);
		int op2=hexToDec(content[Count], content[Count+1]);
		int arg1;
		int arg2;
		int dest;
		if(op1[6]=='1'){
			arg1=hexToDec(content[Count+2], content[Count+3]);
		}
		else{
			if(content[Count+3]!='0'){
				throw std::invalid_argument("Invalid First Argument");
			}
			int index=hexDec[content[Count+2]];
			if(index>7){
				throw std::invalid_argument("Invalid First Argument");
			}
			else{
				arg1=R[index];
			}
		}
		if(op1[7]=='1'){
			arg2=hexToDec(content[Count+4], content[Count+5]);
		}
		else{
			if(content[Count+5]!='0'){
				throw std::invalid_argument("Invalid Second Argument");
			}
			int index=hexDec[content[Count+4]];
			if(index>7){
				throw std::invalid_argument("Invalid Second Argument");
			}
			else{
				arg2=R[index];
			}
		}
		
	
		dest=hexDec[Count+6];
		if(dest>7){
			throw std::invalid_argument("Invalid Destination");
		}
		if(dest==7){
			dest++;
		}
		
		if(!(op2>=32 && op2<=37)){
			int fbyte=hexDec[Count+1];
			if(fbyte>3){
				throw std::invalid_argument("Invalid Instruction Opcode");
			}
			int opNum=hexDec[Count];
			if(opNum>5){
				throw std::invalid_argument("Invalid Instruction Opcode");
			}
			else{
				ALU(opNum, arg1, arg2, dest);
				Count+=8;
			}
		}
		else{
            int jumpaddress=hexToDec(content[Count+6],content[Count+7]);
			Condition(op2, arg1, arg2, jumpaddress);
		}

    }

}

void VirtualMachine::ALU(int op, int arg1, int arg2, int dest){

	switch(op){
		case 0:
		{
			R[dest]=arg1+arg2;
		}
		break;
		case 1:
		{
			R[dest]=arg1-arg2;
		}
		break;
		case 2:
		{
			R[dest]=arg1&arg2;
		}
		break;
		case 3:
		{
			R[dest]=arg1|arg2;
		}
		break;
		case 4:
		{
			R[dest]=~arg1;
		}
		break;
		case 5:
		{
			R[dest]=arg1^arg2;
		}
	}

}

void VirtualMachine::Condition(int op, int arg1, int arg2,int jumpaddress){
	int Count=R[6];

	switch(op){
		case 32:
		{
			if(arg1==arg2){
				Count=jumpaddress;
			}
			else{
				Count+=8;
			}
		}
		break;
		case 33:
		{
			if(arg1!=arg2){
				Count=jumpaddress;
			}
			else{
				Count+=8;
			}
		}
		break;
		case 34:
		{
			if(arg1<arg2){
				Count=jumpaddress;
			}
			else{
				Count+=8;
			}
		}
		break;
		case 35:
		{
			if(arg1<=arg2){
				Count=jumpaddress;
			}
			else{
				Count+=8;
			}
		}
		break;
		case 36:
		{
			if(arg1>arg2){
				Count=jumpaddress;
			}
			else{
				Count+=8;
			}
		}
		break;
		case 37:
		{
			if(arg1>=arg2){
				Count=jumpaddress;
			}
			else{
				Count+=8;
			}
		}
	}

}

int VirtualMachine::hexToDec(char a, char b){
	return 16*hexDec[a]+hexDec[b];
}

std::string VirtualMachine::hexToBin(char a, char b){
	return hexBin[a]+hexBin[b];
}


void VirtualMachine::watchRegisters(){

	std::cout<<"R0: "<<R[0]<<std::endl;
	std::cout<<"R1: "<<R[1]<<std::endl;
	std::cout<<"R2: "<<R[2]<<std::endl;
	std::cout<<"R3: "<<R[3]<<std::endl;
	std::cout<<"R4: "<<R[4]<<std::endl;
	std::cout<<"R5: "<<R[5]<<std::endl;
	std::cout<<"Counter: "<<R[6]<<std::endl;
	std::cout<<"Input: "<<R[7]<<std::endl;
	std::cout<<"Output: "<<R[8]<<std::endl;

}
