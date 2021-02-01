#pragma once
#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;
#include "Member.h"
#include "BloomFilter.h"
#define size_HM 1000

int Hash(int Member_id)
{
    return ((Member_id * 2654435761) % (1000));
}

class HashTable
{
public:
    Member M;
    bool occupied = false;

    void InsertNewMember(BloomFilter& BF, int& totalmembers, Member N)
    {
        int index = Hash(N.id);
        if (this[index].occupied == true) // to deal with collision
        {
            for (int i = index; i < size_HM; i++)
            {
                if (this[i].occupied == false)
                {
                    this[i].M.name = N.name;
                    this[i].M.id = N.id;
                    this[i].M.VIP = N.VIP;
                    this[i].occupied = true;
                    BF.AddToBF(N.id);
                    break;
                }
            }
        }
        else // if there is no collision
        {
            this[index].M.name = N.name;
            this[index].M.id = N.id;
            this[index].M.VIP = N.VIP;
            this[index].occupied = true;
            BF.AddToBF(N.id);
        }
        totalmembers++;
    }
    void InsertFromFile(BloomFilter& BF, int& totalmembers)
    {
        ifstream rdr("AllMembers.txt");
        char* data = new char[100];
        int key1;
        int vip;
        int index;
        while (!rdr.eof())
        {
            rdr >> key1;
            rdr >> vip;
            rdr.ignore();
            index = Hash(key1);
            rdr.getline(data, 100);
            if (this[index].occupied == true)
            {
                for (int i = index; i < size_HM; i++)
                {
                    if (this[i].occupied == false)
                    {
                        this[i].M.name = data;
                        this[i].M.id = key1;
                        this[i].M.VIP = vip;
                        this[i].occupied = true;
                        BF.AddToBF(key1);
                        break;
                    }
                }
            }
            else
            {
                this[index].M.name = data;
                this[index].M.id = key1;
                this[index].M.VIP = vip;
                this[index].occupied = true;
                BF.AddToBF(key1);
            }
            totalmembers++;
        }
    }

    bool searchintable(int Member_id)
    {
        int index = Hash(Member_id);
        bool present = false;
        if (this[index].M.id == Member_id)
            present = true;
        else
        {
            for (int i = index; i < size_HM; i++)
            {
                if (this[i].M.id == Member_id)
                {
                    present = true;
                    break;
                }
            }
        }
        return present;
    }

    void PrintHashTable()
    {
        cout << "------Member List------\n";
        for (int i = 0; i < size_HM; i++)
        {
            if (this[i].occupied == true)
            {
                cout << "\nID : " << this[i].M.id;
                cout << "\nName : " << this[i].M.name;
                if (this[i].M.VIP == 1)
                    cout << "\nVIP : YES";
                else
                    cout << "\nVIP : NO";
                cout << endl;
            }
        }
    }

    int GetNewID()
    {
        int max = 0;
        for (int i = 0; i < size_HM; i++)
            if (this[i].occupied == true)
                if (this[i].M.id >= max)
                    max = this[i].M.id + 1;
        return max;
    }

    void VIPUpgrade(Member A)
    {
        int index = Hash(A.id); // getting index
        bool present = false;
        if (this[index].M.id == A.id)
            this[index].M.VIP = true;
        else
        {
            for (int i = index; i < size_HM; i++)
            {
                if (this[i].M.id == A.id)
                {
                    present = true;
                    this[index].M.VIP = true;
                    break;
                }
            }
        }
    }

    Member GetMember(Member A)
    {
        int Member_id = A.id;
        int index = Hash(Member_id);
        if (this[index].M.id == Member_id)
            return this[index].M;
        else
        {
            for (int i = index; i < size_HM; i++)
                if (this[i].M.id == Member_id)
                    this[index].M;
        }
        return A;
    }

    void SaveFile(ofstream& writer)
    {
        int cnt = 0;
        for (int i = 0; i < size_HM; i++)
            if (this[i].occupied == true)
            {
                if (cnt > 0)
                    writer << "\n";
                writer << this[i].M.id << " " << this[i].M.VIP << " " << this[i].M.name;
                cnt++;
            }
    }


    bool SearchAndDelete(int Member_id, int & totalmembers)
    {
        int index = Hash(Member_id);
        if (this[index].M.id == Member_id)
        {
            totalmembers--;
            this[index].occupied = false;
            cout << this[index].M.name << " is not a member now";
            return true;
        }
        else
        {
            for (int i = index; i < size_HM; i++)
                if (this[i].M.id == Member_id)
                {
                    this[index].occupied = false;
                    cout << this[index].M.name << " is not a member now";
                    return true;
                }
        }
        return false;
    }

};


