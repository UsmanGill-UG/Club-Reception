#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;
#include "Member.h"
#include "Club.h";

int main()
{
	Club Gills;
	ofstream writer;
	writer.open("log.txt"); // to store the daily log of the club
	vector<Member> line; // vector of queue outside the club
	int id;
	string name;
	int choice = 0;
	string ch = "yes";
	Member A;
	do
	{
		cout << "----------Gill's Club-----------\n";
		Gills.DisplatCount();
		cout << "1 - Print All Members\n";
		cout << "2 - Print All Members  in Club\n";
		cout << "3 - Enter Club \n";
		cout << "4 - Leave Club \n";
		cout << "5 - New Membership \n";
		cout << "6 - End Membership \n";
		cout << "7 - Check In Club \n";
		cout << "8 - Exit\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			Gills.Print_Members();
			break;
		case 2:
			Gills.Print_Members_In_Club();
			break;
		case 3:
			cout << "-----------Enter Member-------------\n";
			do
			{
				cout << "Is there a person in line yes/no? \n";
				cin >> ch;
				if (ch == "no")
					break;
				if (ch != "yes" && ch != "no")
					continue;
				cout << "ID :";
				cin >> A.id;
				line.push_back(A);
			} while (ch != "no");
			Gills.Enter_Club(line, writer);
			line.clear();
			break;
		case 4:
			cout << "ID : ";
			cin >> A.id;
			Gills.Leaving_Club(A, writer);
			break;
		case 5:
			cout << "-----------New Member-------------\n";
			cout << "Name : ";
			cin >> A.name;
			cout << "VIP : (yes=1  no = 0)";
			cin >> A.VIP;
			Gills.New_Membership(A); // id will be assigned in function
			cout << A.name << " is a member now\n";
			break;		
		case 6:
			cout << "-----------End Membership-------------\n";
			cout << "Member ID : ";
			cin >> id;
			Gills.End_Membership(id);
				break;
		case 7:
			cout << "-----------In Club Presence-------------\n";
				cout << "ID :";
				cin >> A.id;
				if (Gills.CheckInClub(A))
					cout << A.name << " is in the Club\n";
				else
					cout << A.name << " is not in the Club\n";
			break;
		default:
			break;
		}
		_getch();
		system("cls");
	} while (choice != 8);
	writer.close();
	Gills.SaveMemberFile(); // saves new members in file
	string a;
	cout << "Do you want to see Log ?  yes/no \n";
	cin >> a;
	if (a == "yes")
	{
		cout << "-----------Log-------------\n";
		Gills.PrintLog();
	}
	return _getch();
}