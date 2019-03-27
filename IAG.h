#pragma once
#include <iostream>
#include"InterStateBuffers.h"
using namespace std;

// Instruction Adddress generator
class IAG{
	public:
		
		void step(InterStateBuffers &isb){
			isb.return_address = isb.PC+1;
			if(isb.isjalr == true){
				isb.PC = isb.RZ.readInt();
			}
			else if(isb.insType == 3 || isb.insType == 5){
				isb.PC = isb.PC + isb.pc_offset;
			}
			else{
				isb.PC++;
			}
			return;
		}
};
