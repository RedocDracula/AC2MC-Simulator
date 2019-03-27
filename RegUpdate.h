#pragma once
#include "RegistryFile.h"
#include "InterStateBuffers.h"

class RegUpdate {
public:
	RegUpdate();
	~RegUpdate();
	void update (InterStateBuffers & buffer, Registry_File & Reg,int destination ) { // 
		Reg.writeInt( destination, buffer.RZ.readInt() );	
	}
};
