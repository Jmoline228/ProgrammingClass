﻿/*************************************************************************
***********************************************
Name: Jose Molineros        
Course: COP 3014
Professor: Dr. Lofton Bullard
Due Date:  06/28/18         Due Time: 11:59PM
Total Points: 20
Assignment 6: call_stats4.cpp
Description:This program uses functions to print call information to the user from a local file. The Input function gets information
from a .txt file using ifstream and saving it to call_record. The Process function uses the call_record & customer_record to perform
calculations (net_cost, call_tax, total_cost). The solutions to these calculations are then used by the Output function to
save the information in a .txt file.

**************************************************************************
***********************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
const int SIZE = 200; 

class call_record
{
public:
	string cell_number;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};

void Input(call_record call_DB[], int & count);
void Output(const call_record call_DB[], const int & count);
void Process(call_record call_DB[], const int & count);
///*************************************************************************************
//Name:  Input
//Precondition: The variables (call_record call_DB[], int & count) have not been initialized
//Postcondition: The variables (call_record call_DB[], int & count) have been initialized
//Description: Get input (call_record call_DB[], int & count) from the file and saves it in call_record.
//*************************************************************************************
void Input(call_record call_DB[], int & count)
{
	ifstream in; 
	count = 0;  
	in.open("call_data.txt"); 
		if (in.fail()) 
		{
			cout << "Input file did not open correctly" << endl;
			exit(1);
		}
	
	while (!in.eof())
	{
		in >> call_DB[count].cell_number;
		in >> call_DB[count].relays;
		in >> call_DB[count].call_length; 
		count++;
	}
	in.close();
}
///*************************************************************************************
//Name:  Output
//Precondition: The variables (const call_record call_DB[],const int & count) have not been initialized
//Postcondition: The variables (const call_record call_DB[],const int & count) have been initialized
//Description: Saves output (const call_record call_DB[],const int & count) in a text file.
//*************************************************************************************
void Output(const call_record call_DB[], const int & count)
{
	ofstream out; 
	out.open("weekly4_call_info.txt");
		if (out.fail()) 
		{
			cout << "Output file did not open correctly" << endl;
	exit(1);
		}
		for (int i = 0; i < count; i++)
		{
			out.setf(ios::showpoint);
			out.precision(2);
			out.setf(ios::fixed);

			out << right << call_DB[i].cell_number << "   ";
			out << right << setw(15) << call_DB[i].relays << "   ";
			out << right << setw(15) << call_DB[i].call_length << "   ";
			out << right << setw(15) << call_DB[i].net_cost << "   ";
			out << right << setw(15) << call_DB[i].tax_rate << "   ";
			out << right << setw(15) << call_DB[i].call_tax << "   ";
			out << right << setw(15) << call_DB[i].total_cost << endl;
		}
			
	out.close();
}
///*************************************************************************************
//Name:  Process
//Precondition: The variables (call_record call_DB[], const int & count) have not been initialized
//Postcondition: The variables (call_record call_DB[], const int & count) have been initialized
//Description: Perform calculations (net_cost, call_tax, total_cost) based on call_record call_DB[] and saves it in call_record.
//*************************************************************************************
void Process(call_record call_DB[], const int & count)
{
	int i;
	for (i = 0; i < count; i++)
	{
		call_DB[i].net_cost = call_DB[i].relays / 50.0 * .40 * call_DB[i].call_length;
		if (call_DB[i].relays >= 0 && call_DB[i].relays <= 5)
		{
			call_DB[i].tax_rate = 0.01;
		}
		else if ((6 <= call_DB[i].relays) && (call_DB[i].relays <= 11)) {
			call_DB[i].tax_rate = 0.03;
		}
		else if ((12 <= call_DB[i].relays) && (call_DB[i].relays <= 20)) {
			call_DB[i].tax_rate = 0.05;
		}
		else if ((21 <= call_DB[i].relays) && (call_DB[i].relays <= 50)) {
			call_DB[i].tax_rate = 0.08;
		}
		else if (call_DB[i].relays > 50) {
			call_DB[i].tax_rate = 0.12;
		}
		call_DB[i].call_tax = (call_DB[i].net_cost * call_DB[i].tax_rate);
		call_DB[i].total_cost = (call_DB[i].net_cost + call_DB[i].call_tax);
	}
}
int main()
{
	call_record call_DB[SIZE];
	int count = 0;
	
	Input(call_DB, count); 
	Process(call_DB, count); 
	Output(call_DB, count);
	
	return 0;
}
