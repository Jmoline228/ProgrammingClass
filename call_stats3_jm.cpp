﻿/***********************************************************
Jose Molineros	        
Total Points:100
Due Date:  6/14/18   Due Time: 11:59PM
Course:  C0P3014
Assignment:  call_stats3.cpp
Professor: Dr. Lofton Bullard

Description: This program uses functions to print call information to the user from a local file. The Input function gets information
from a .txt file using ifstream and saving it to call_record. The Process function uses the call_record & customer_record to perform
calculations (net_cost, call_tax, total_cost). The solutions to these calculations are then used by the Output function to
save the information in a .txt file.

*************************************************************/

#include <iostream> 
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

class call_record
{
public:
	string cell_num;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};

void Input(ifstream &, call_record &);
void Output(const call_record &);
void Process(ofstream &, call_record &);

//Name: Input
//Precondition: The variables (ifstream & in, call_record & customer_record)) have not been initialized
//Postcondition: The variables (ifstream & in, call_record & customer_record)) have been initialized
//Description: Get input (ifstream & in, call_record & customer_record)) from the file and saves it in call_record.

void Input(ifstream & in, call_record & customer_record)
{
	in >> customer_record.cell_num;
	in >> customer_record.relays;
	in >> customer_record.call_length;
}

//Name: Output
//Precondition: The variables (call_record & customer_record) have not been initialized
//Postcondition: The variables (call_record & customer_record) have been initialized
//Description: Saves output (call_record & customer_record) in a text file.

void Output(ofstream & out, const call_record & customer_record)
{
	out.open("weekly_call_info.txt", ios_base::app);
	if (out.is_open())
	{
		out.setf(ios::showpoint);
		out.precision(2);
		out.setf(ios::fixed);

		out << right << customer_record.cell_num << "   ";
		out << right << setw(15) << customer_record.relays << "   ";
		out << right << setw(15) << customer_record.call_length << "   ";
		out << right << setw(15) << customer_record.net_cost << "   ";
		out << right << setw(15) << customer_record.tax_rate << "   ";
		out << right << setw(15) << customer_record.call_tax << "   ";
		out << right << setw(15) << customer_record.total_cost << endl;
		out.close();
	} 
	else cout << "Unable to open file.";
}

//Name:  Process
//Precondition: The variables (relays, call_length, net_cost, call_tax, total_cost, and tax_rate) have not been initialized
//Postcondition: The variables (relays, call_length, net_cost, call_tax, total_cost, and tax_rate) have been initialized
//Description: Perform calculations (net_cost, call_tax, total_cost) based on call_record & customer_record information and saves it in call_record.

void Process(call_record & customer_record)
{
	customer_record.net_cost = (customer_record.relays / 50.0 * 0.40 * customer_record.call_length);

	if (customer_record.relays <= 5) {
		customer_record.tax_rate = 0.01;
	}
	else if ((6 <= customer_record.relays) && (customer_record.relays <= 11)) {
		customer_record.tax_rate = 0.03;
	}
	else if ((12 <= customer_record.relays) && (customer_record.relays <= 20)) {
		customer_record.tax_rate = 0.05;
	}
	else if ((21 <= customer_record.relays) && (customer_record.relays <= 50)) {
		customer_record.tax_rate = 0.08;
	}
	else if (customer_record.relays > 50) {
		customer_record.tax_rate = 0.12;
	}

	customer_record.call_tax = (customer_record.net_cost * customer_record.tax_rate);
	customer_record.total_cost = (customer_record.net_cost + customer_record.call_tax);
}

int main()
{
	call_record customer_record;
	ifstream in;
	ofstream out;
	in.open("call_data.txt");
	if (in.fail())
	{
		cout << "Input file did not open correctly" << endl;
	}
	else
	{
		while (!in.eof())
		{
			Input(in, customer_record);
			Process(customer_record);
			Output(out, customer_record);
		}
	}
	in.close();



	return 0;

}
