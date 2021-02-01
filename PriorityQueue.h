#pragma once
#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;
#include "Member.h"


class PriorityQueue
{
    Member arr[1000];
    int size = 0;
public:
    int Parent(int i)
    {
        return i / 2;
    }
    int Left_Child(int i)
    {
        return i * 2;
    }
    int Right_Child(int i)
    {
        return (i * 2) + 1;
    }
    void Add(Member p)
    {
        ++size;
        arr[size] = p;
        Maintain_Heap(size);
    }
    void Maintain_Heap(int ind)
    {
        while (ind > 1 && arr[Parent(ind)].VIP < arr[ind].VIP)
        {
            swap(arr[Parent(ind)], arr[ind]);
            ind = Parent(ind);
        }
    }
    Member GetMax()
    {
        return arr[1];
    }
    Member RemoveMax()
    {
        Member result = arr[1];
        arr[1] = arr[size];
        --size;
        MoveToBottom(1);
        return result;
    }
    void MoveToBottom(int i)
    {
       int left = Left_Child(i);
       int right = Right_Child(i);
       int max = i;
       if (left < size && arr[left].VIP > arr[i].VIP)
           max = left;
       if (right < size && arr[right].VIP > arr[max].VIP)
           max = right;
       if (max != i) {
          swap(arr[i], arr[max]);
          MoveToBottom(max);
       }
    }

    int GetSize()
    {
        return size;
    }

    void printqueue()
    {
        cout << "--------Queue ---------\n";
        for (int i = 1; i <= size; i++)
            cout << arr[i].id << "  " << arr[i].VIP << "  " << arr[i].name << "\n";
    }

    void printfull()
    {
        for (int i = 1; i <= size; i++)
            cout << "Sorry," << arr[i].name << " the club is full\n";
    }
};

