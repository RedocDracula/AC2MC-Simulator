#pragma once
#include <iostream>
#include"InterStateBuffers.h"
#include"ALU.h"
using namespace std;

// Instruction Adddress generator
class IAG{
	public:
		
		void step(InterStateBuffers &isb, ALU &alu){
			isb.return_address = isb.PC+1;
			if(isb.isjalr == true){
				isb.PC = isb.RZ.readInt();
			}
			else if(isb.insType == 5){
				isb.PC = isb.PC + isb.pc_offset;
			}
			else if(isb.insType == 3 && alu.state == true){
				isb.PC = isb.PC + isb.pc_offset;
			}
			else{
				isb.PC++;
			}
			return;
		}
};
