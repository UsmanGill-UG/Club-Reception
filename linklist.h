#pragma once
#include <iostream>

using namespace std;
#include "Member.h"
struct node
{
    Member Data;
    node* next;
};

class linklist
{
private:
    node* head;
public:
    int size = 0;
    linklist()
    {
        head = NULL;
    }
    void add_node(Member M)
    {
        node* t = new node;
        t->Data.id = M.id;
        t->Data.name = M.name;
        t->Data.VIP = M.VIP;
        t->next = NULL;
        node* temp = new node;
        temp = head;
        if (head == NULL)
            head = t;
        else
        {
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = t;
        }
        size++;
    }
    void RemoveAtIndex(Member M)
    {
        if (head == NULL)
        {
            cout << "No members in the Club\n";
            return;
        }
        node* t = new node;
        t->Data.id = M.id;
        t->Data.name = M.name;
        t->Data.VIP = M.VIP;
        t->next = NULL;
        if (head->Data.id == M.id)
        {
            node* hn = new node;
            hn = head->next;
            head = hn;
            return;
        }
        node* temp = new node;
        node* prev = new node;
        temp = head;
        while (temp != NULL)
        {
            if (temp->Data.id == t->Data.id)
            {
                node* t3 = temp; // jider equal
                prev->next = temp->next; 
                return;
            }
            prev = temp; // jider equal ka nichla node
            temp = temp->next; //temp mein agla next
        }

    }
    void MICprint()
    {
        node* t = new node;
        t = head;
        cout << "--------Members in Club---------\n";
        if (t == NULL)
        {
            cout << "\n Club is empty :( \n";
            return;
        }
        while (t != NULL)
        {
            cout << t->Data.name << " is in the Club\n";
            t = t->next;
        }
    }

    bool IsIn(Member a)
    {
        node* t = new node;
        t = head;
        while (t != NULL)
        {
            if (t->Data.id ==  a.id)
                return true;
            t = t->next;
        }
        return false;
    }
};
