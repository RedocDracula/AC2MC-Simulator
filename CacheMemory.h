#include <iostream>
#include <set>
#include <bitset>
#include <vector>
#include "MemoryAccess.h"
#include "InterStateBuffers.h"
#define NUMBER_SETS 64 
#define SET_SIZE 2
// Address is 16 BIT .
// SIZE OF MAIN MEMORY IS 32 MB
using namespace std;

class Cache{ 
    private:
    vector <int> CacheMem;
    vector <int> WriteBack; // The Dirty bit.
    vector <int> hits;
    vector <int> Tag;
    int CacheSize, BlockSize,choice,waysofset;

    
    public:
    Cache(){
        CacheMem.resize(128);
        WriteBack.resize(128);
        hits.resize(128);
        Tag.resize(128);
    }
    Cache(int cs,int bs, int choice, int ways){
        CacheMem.resize(cs);
        
    }

    void ReadCache(MemoryAccess &memobject, InterStateBuffers &isb, bitset <16> address){
        bitset <2> word; //block offset
        bitset <7> line,tag;
        
        int k = 0;
        for(int i = 0 ; i <= 1 ; i++)
            word[k++] = address[i];
        k = 0;
        for(int i = 2; i <= 8 ; i++)
            line[k++] = address[i];
        k = 0;
        for(int i = 9 ; i <= 15 ; i++)
            tag[k++] = address[i];
        
        int lineindex = line.to_ulong();

        bool hit = 0;
        int linenumber = line.to_ulong();
        if(Tag[linenumber] == tag.to_ulong()){ // it's a hit

        }

    }

    void WriteCache(MemoryAccess &memobject, InterStateBuffers &isb, bitset <16> address){

    }
};