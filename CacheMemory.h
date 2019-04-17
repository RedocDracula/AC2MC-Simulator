#include <iostream>
#include <set>
#include <bitset>
#include <vector>
#include "MemoryAccess.h"
#include "InterStateBuffers.h"
#define NUMBER_SETS 64 
#define SET_SIZE 2
// Address is 16 BIT .
using namespace std;

class Cache{ // Cache has 2^8 lines now.
    private:
    vector < vector <int> > CacheMem; // technicaly vector <Lines> , Lines is a vector as Line size can vary based on block size
    vector <int> WriteBack; // The Dirty bit.
    vector <int> hits;
    vector <int> Tag;
    
    public:
    Cache(){
        CacheMem.resize(128);
        WriteBack.resize(128);
        hits.resize(128);
        Tag.resize(128);
    }
    Cache(int Lines){
        CacheMem.resize(Lines);
        WriteBack.resize(Lines);
        hits.resize(Lines);
        Tag.resize(Lines);
    }

    void ReadCache(MemoryAccess &memobject, InterStateBuffers &isb, bitset <16> address){
        bitset <2> word; //block offset
        bitset <7> set,tag;
        int k = 0;
        for(int i = 0 ; i <= 1 ; i++)
            word[k++] = address[i];
        k = 0;
        for(int i = 2; i <= 8 ; i++)
            set[k++] = address[i];
        k = 0;
        for(int i = 9 ; i <= 15 ; i++)
            tag[k++] = address[i];
        
        int setindex = set.to_ulong();

        bool hit = 0;

        for(int i = 0 ; i < CacheMem[setindex].size() ; i++){
            if(){

            }
        }

    }

    void WriteCache(MemoryAccess &memobject, InterStateBuffers &isb, bitset <16> address){

    }
};