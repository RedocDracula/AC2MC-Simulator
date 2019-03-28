#include<iostream>
#include<fstream>
#include <sstream>
#include<string.h>
#include<bitset>
#include"RType.h"
#include"IType.h"
#include"SBType.h"
#include"SType.h"
#include"UJType.h"
#include"UType.h"
#include"ALU.h"
#include"IAG.h"
#include"Decode.h"
#include"Fetch.h"
#include"MUX_Y.h"
#include"RegistryFile.h"
#include"RegUpdate.h"
#include"MemoryAccess.h"
#include"InterStateBuffers.h"

using namespace std;

void findLabels(string,vector<string>&,vector<int>&);

int main(){

	RType rTypeInsObj;
	IType iTypeInsObj;
	SBType sbTypeInsObj;
  SType sTypeInsObj;
	UJType ujTypeInsObj;
	UType uTypeInsObj;

	InterStateBuffers isb;

	vector<string> labelNames;
	vector<int> labelLineNumber;

	int insType;
	
	string inputFileName = "input.txt";
	string outputFileName = "machineCode.txt";
	string basicCodeFileName = "basicCode.txt";

	// Directory path to source instruction text files
	string dir = "./instructions/";

	rTypeInsObj.initialise(dir + "RType.txt");
	iTypeInsObj.initialise(dir + "IType.txt");
	sbTypeInsObj.initialise(dir + "SBType.txt");
  sTypeInsObj.initialise(dir + "SType.txt");
	ujTypeInsObj.initialise(dir + "UJType.txt");
	uTypeInsObj.initialise(dir + "UType.txt");


	//Find All Labels in the input file
	findLabels(inputFileName,labelNames,labelLineNumber);	
	
	ifstream iFile(inputFileName.c_str());
	ofstream oFile(outputFileName.c_str());
	ofstream oFile2(basicCodeFileName.c_str());

	if(!iFile.is_open()) cout<<"Error in reading input file";
	else{
		int lineNo=0;
		bitset<32> machineCode;
		string line;
		while(getline(iFile,line)) {
			// Skip Label descriptions
			size_t found = line.find(':');			
			if(found != string::npos) continue;

			lineNo++;
			
			// replacing sp with x2
			for(int i=1;i<(line.size()-2);i++){
				if(line[i]=='s' &&line[i+1]=='p'&&(line[i-1]==' '||line[i-1]==',')&&(line[i+2]==' ' ||line[i+2]==','||line[i+2]=='\n')){
					line[i]='x';
					line[i+1]='2';
				}
			}

			// replacing labels
			for(int i=0;i<labelNames.size();i++){
				size_t found = line.find(labelNames[i]);
				if(found != string::npos){
					string newline;
					for(int j=0;j<found;j++) newline.push_back(line[j]);
					int offset = labelLineNumber[i] - lineNo -i;
				//	offset *= 4; // Multiplying offset by 4
					ostringstream numStr;
					numStr << offset;
					string intStr = numStr.str();
					line = newline + intStr;
				}
			}
		
			if(rTypeInsObj.isPresent(line)) {
				machineCode = rTypeInsObj.decode(line);
				insType = 1;
			}
			else if(iTypeInsObj.isPresent(line)) {
				machineCode = iTypeInsObj.decode(line);
				insType = 2;
			}
			else if(sbTypeInsObj.isPresent(line)) {
				machineCode = sbTypeInsObj.decode(line);
				insType = 3;
			}
			else if(sTypeInsObj.isPresent(line)) {
				machineCode = sTypeInsObj.decode(line);
				insType = 4;
			}
			else if(ujTypeInsObj.isPresent(line)) {
				machineCode = ujTypeInsObj.decode(line);
				insType = 5;
			}
			else if(uTypeInsObj.isPresent(line)) {
				machineCode = uTypeInsObj.decode(line);
				insType = 6;
			}
			else {
				cout<<"!! Instuction not identified : "<<line<<endl;
				machineCode = bitset<32>(0);
				insType = -1;
			}
			oFile <<lineNo<<" "<< machineCode <<" "<< insType << endl;
			oFile2 <<lineNo<<" "<< line << endl;
		}
		oFile<<lineNo+1<<" 0 0"<<endl;
		cout<<"Machine code file generated succesfully."<<endl;
	}
	iFile.close();
	oFile.close();
	oFile2.close();

	Registry_File rFile;
	Fetch fetch;
	MUX_Y muxy;
	Decode decode;
	MemoryAccess memAccess;
	RegUpdate regUpdate;
	ALU alu;
	IAG iag;
	

	decode.initialise();

	// Control
	while(1){
		fetch.get(isb);
		if(isb.IR.readInt() == 0)
			break;
//		cout<<"PC Value : "<<isb.PC<<" IR : "<<isb.IR.readBitset()<<" Instype : "<<isb.insType<<endl;
		decode.decoder(isb,rFile);
		alu.compute(isb);
		if(isb.isMem == true){
				if(isb.insType == 4){
					memAccess.writeMem(isb);
					muxy.MUX_Y_SELECT = 1;
				}
				else {
					memAccess.readMem(isb);
					muxy.MUX_Y_SELECT = 2; // for getting register val from memory

				}
		}
		else if(isb.isjalr == true || isb.insType == 5){
			muxy.MUX_Y_SELECT = 3;
		}
		else
			muxy.MUX_Y_SELECT = 1;
		
		isb.RY.writeInt(muxy.output(isb));
		
		if(isb.write_back_location != -1){
			regUpdate.update(isb,rFile, isb.write_back_location);
		}
		rFile.print();
		

		iag.step(isb,alu);
	}
	

	cout<<"Code executed succesfully."<<endl;
	// rFile.print();
	return 0;
}

void findLabels(string inputFileName, vector<string> &labelNames, vector<int> &labelLineNumber){
	ifstream iFile(inputFileName.c_str());
	if(iFile.is_open()){
		int lineNo = 0;	
		string line;
		while(getline(iFile,line)) {
			lineNo++;
			size_t found = line.find(':');
			if(found != string::npos){
				string labelName;
				int i=0;
				while(!isalnum(line[i])) i++;
				while(line[i]!=':' && i<line.size()) labelName.push_back(line[i++]);
				labelNames.push_back(labelName);
				labelLineNumber.push_back(lineNo);
			//	cout<<"Label found : "<<labelName<<" at line no. "<<lineNo<<endl;
			}
		}
	}
	iFile.close();
}
