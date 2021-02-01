#pragma once
#include <iostream>
#include <conio.h>

using namespace std;

#define size_bf  1000  
class BloomFilter{

	int BF[size_bf] = {0};// initialize array to 0/false
public:
	BloomFilter(){}
    int GetIndex(int Member_id)
    {
        return Hash(Member_id);
    }
    void AddToBF(int Member_id)
    {
        int index = GetIndex(Member_id);
        if (BF[index] != 1)
          ++BF[index]; 
    }
    bool IsPresent(int Member_id)
    {
        if (BF[GetIndex(Member_id)] == 1)
            return 1; 
            return 0;
    }
    int Hash(int Member_id)
    {
        return ((Member_id * 2654435761) % (1000));
    }
};