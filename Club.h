#pragma once
#include <iostream>
#include <conio.h>
#include <string>
using namespace std;
#include "linklist.h"
#include "HashMap.h"
#include "PriorityQueue.h"
#include "BloomFilter.h"
#define AMsize 1000

class Club {
	linklist MIC;// members currently in the club
	HashTable AM[AMsize];//  All members
	BloomFilter BF;
	PriorityQueue line;
	int totalmembers =  0;
	int inclub = 0;
public:
	Club(){
		AM->InsertFromFile(BF, totalmembers); // load members from file
	}
	bool Check_VIP(Member A) {
		return A.VIP;
	}
	bool Check_Membership(int Member_id) {
		int present = BF.IsPresent(Member_id);
		if (present == 0)
			return false;
		else
		{
			bool present  = AM->searchintable(Member_id);
			return present;
		}
	}
	bool CheckInClub(Member& A){
		A = AM->GetMember(A);
		return MIC.IsIn(A);
	}
	void New_Membership(Member& M) { // insert in hash map
		int mid = AM->GetNewID();
		M.id = mid;
		AM->InsertNewMember(BF, totalmembers , M);
	}
	void Print_Members() {
		AM->PrintHashTable();
	}
	void Print_Members_In_Club() {
		MIC.MICprint();
	}
	void Leaving_Club(Member L ,ofstream &writer) {
		if (Check_Membership(L.id) == false)
		{
			cout << "ID : " << L.id << " is not a member\n";
			return;
		}
		Member A = AM->GetMember(L);
		if ( CheckInClub(L))
		{
			MIC.RemoveAtIndex(A);
			cout << A.name << " left the Club\n";
			writer << A.name << " left the Club\n";
			--inclub;
		}
		else
			cout << A.name << " is not in the Club!";
	}
	void End_Membership(int id) {
		Member A;
		A.id = id;
		if (AM->SearchAndDelete(id, totalmembers) == false)
		{
			//MIC.RemoveAtIndex(A); // remove that person from the club too
			cout << "ID : " << id << ", already NOT a member!\n";
		}
	}
	void Upgrade_to_VIP(Member A) {
		if (Check_Membership(A.id))
		{
			if (A.VIP == 0)
				A.VIP = 1;
		}
		else
			cout << "ID : "<<A.id << " is not a member!\n";
	}
	void Enter_Club(vector<Member> line_ , ofstream&writer) {
		for(int i = 0 ; i < line_.size() ; i++)
		{
			if (Check_Membership(line_[i].id) == true)
			{
				Member A = AM->GetMember(line_[i]);
				if (CheckInClub(line_[i]))
				{
					cout << A.name << " is already in the Club!\n";
					continue;
				}
				line.Add(A);
			}
			else
				cout <<"ID: " <<line_[i].id << " does not have a membership!\n";
		}
		int size1 = line.GetSize();
		//line.printqueue();
		for (int i = 0 ; i < size1; i++)
		{
			Member B = line.GetMax();
			if(B.VIP == 1 || MIC.size < 100)
			{
				inclub++;
				cout << B.name << " entered the Club\n";
				writer << B.name <<" entered the Club\n";
				MIC.add_node(B);
				line.RemoveMax();
			}
		}
		line.printfull();
	}
	void PrintPresent(Member A){
		if (Check_Membership(A.id))
			cout << A.name << " is a member\n";
		else
			cout << A.name << " is not a member\n";
	}
	void SaveMemberFile(){
		ofstream writer2;
		writer2.open("AllMembers.txt");
		AM->SaveFile(writer2);
	}
	void DisplatCount(){
		cout << "Total Members : " << totalmembers << endl;
		cout << "In Club : " << inclub << endl;
	}
	void PrintLog()
	{
		ifstream rdr("log.txt");
		while (!rdr.eof())
		{
			char* entry = new char[100];
			rdr.getline(entry,100);
			cout << entry << endl;
		}
	}
};
