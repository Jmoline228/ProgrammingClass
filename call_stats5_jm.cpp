﻿/************************************************************************************************************************
Name: Jose Molineros        
Course: COP 3014
Professor: Dr. Lofton Bullard
Due Date:  07/12/18         Due Time: 11:59PM
Total Points: 20
Assignment 6: call_stats5.cpp
Description: This program manages a dynamic array (call_DB) and inputs information from a data file (callstats_data.txt)
into the array elements. It uses differemt void functions to add or remove items to the array, double the size of the array,
and perform calculations. It will ultimately print the information to the user.
*************************************************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class call_record
{
public:
	string firstname;
	string lastname;
	string cell_number;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};


void Initialize(call_record *& call_DB, int & count, int & size);
bool Is_empty(const int count); //inline implementation
bool Is_full(const int count, int size);//inline implementation
int Search(const call_record *call_DB, const int count, const string key);//returns location if item in listl; otherwise return -1
void Add(call_record * &call_DB, int & count, int & size, const string key); //adds item in order to the list
void Remove(call_record *call_DB, int & count, const string key); //removes an item from the list
void Double_size(call_record * &call_DB, int & count, int & size);
void Process(call_record *call_DB, const int & count);
void Print(const call_record *call_DB, int & count); //prints all the elements in the list to the screen
void Destroy_call_DB(call_record * &call_DB); //de-allocates all memory allocate to call_DB by operator new.



//Name: Initialize
//Precondition: The file has not been opened or read
//Postcondition: callstats_data.txt is opened and read into elements of a dynamic array.
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
void Initialize(call_record * & call_DB, int & count, int & size)
{
	ifstream in;

	in.open("callstats_data.txt"); 

	if (in.fail()) 
	{
		cout << "Input file did not open correctly." << endl;
	}
	else
	{
		while (!in.eof())
		{
			for (int i = 0; i < count; i++) 
			{

				in >> call_DB[i].firstname;
				in >> call_DB[i].lastname;
				in >> call_DB[i].cell_number;
				in >> call_DB[i].relays;
				in >> call_DB[i].call_length;

				count++;
			}

			if (Is_full(count, size)) 
			{
				Double_size(call_DB, count, size);
			}

		}
	}

	Process(call_DB, count); 

	in.close(); 
}

/***********************************************************************************************************************************/
//Name: Is_empty
//Precondition: The empty status of the capacity of the array is unknown 
//Postcondition: The empty status of the capacity of the array is known (if the array is empty or not)
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/
bool Is_empty(const int count)
{
	if (count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**********************************************************************************************************************************/
//Name: Is_full 
//Precondition: The status of the capacity of the array is unknown.
//Postcondition: The full status of the capacity of the array is known.
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
bool Is_full(const int count, int size)
{
	if (count == size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**********************************************************************************************************************************/
//Name: Search
//Precondition: The location of the key is unknown
//Postcondition: The location of the key is known. If it does not exist in the array, -1 is returned.
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int Search(const call_record *call_DB, const int count, const string key)
{

	for (int i = 0; i < count; i++)
	{
		if (call_DB[i].cell_number == key)
		{
			return i;
		}
	}
	return -1;
}

/*********************************************************************************************************************************/
//Name: Add
//Precondition: The current array remains unchanged.
//Postcondition: A new array member is added and count is increased by 1.
//Decription: add key to call_DB; if call_DB is full, double_size is called to increase the size of call_DB.
/********************************************************************************************************************************/
void Add(call_record * &call_DB, int & count, int & size, const string key)
{
	if (Is_full(count, size)) 
	{
		Double_size(call_DB, count, size); 
	}

	int i = count;

	call_DB[i].cell_number = key;
	cout << "Please enter the first name." << endl;
	cin >> call_DB[i].firstname;
	cout << "Please enter the last name." << endl;
	cin >> call_DB[i].lastname;
	cout << "Please enter the number of relays." << endl;
	cin >> call_DB[i].relays;
	cout << "Please enter the number of minutes." << endl;
	cin >> call_DB[i].call_length;

	count++;

	Process(call_DB, count);
}

/********************************************************************************************************************************/
//Name: Remove
//Precondition: Unknown if key exists in array.
//Postcondition: If key existed in array, the entry is removed.
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
void Remove(call_record *call_DB, int & count, const string key)
{

	if (Is_empty(count)) 
	{
		return;
	}
	
	int loc = Search(call_DB, count, key);
	if (loc != 1)
	{
		for (int j = loc; j < count; j++)
		{
			call_DB[j] = call_DB[j + 1];
		}
		count--;
	}

}

/******************************************************************************************************************************/
//Name: Double_Size
//Precondition: The size of the array is unchanged.
//Postcondition: The size of the array is doubled.
//Decription: doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void Double_size(call_record * &call_DB, int & count, int & size)
{
	size = size * 2;

	call_record *temp = new call_record[size];

	for (int i = 0; i < count; i++)
	{
		temp[i] = call_DB[i];
	}

	delete[]call_DB;

	call_DB = temp;
}


/******************************************************************************************************************************/
//Name: Process
//Precondition: The net cost, tax rate, call tax, and total cost have not been calculated, initialized or stored in the call record.
//Postcondition: The net cost, tax rate, call tax, and total cost have been calculated and stored in the call record for each entry.
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void Process(call_record *call_DB, const int & count)
{
	for (int i = 0; i < count; i++)
	{
		
		call_DB[i].net_cost = (call_DB[i].relays / (50.0 / 0.40))*call_DB[i].call_length;

		if (call_DB[i].relays >= 0 && call_DB[i].relays <= 5)
		{
			call_DB[i].tax_rate = 0.01;
		}
		else if (call_DB[i].relays >= 6 && call_DB[i].relays <= 11)
		{
			call_DB[i].tax_rate = 0.03;
		}
		else if (call_DB[i].relays >= 12 && call_DB[i].relays <= 20)
		{
			call_DB[i].tax_rate = 0.05;
		}
		else if (call_DB[i].relays >= 21 && call_DB[i].relays <= 50)
		{
			call_DB[i].tax_rate = 0.08;
		}
		else if (call_DB[i].relays > 50)
		{
			call_DB[i].tax_rate = 0.12;
		}

	
		call_DB[i].call_tax = (call_DB[i].net_cost*call_DB[i].tax_rate);
		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;
	}
}


/****************************************************************************************************************************/
//Name: Print
//Precondition: There is no output of the call record
//Postcondition: Output is printed to the user
//Decription: prints every field of every call_record in call_DB formatted to the screen.
/***************************************************************************************************************************/
void Print(const call_record *call_DB, int & count)
{
	
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout.setf(ios::fixed);

	for (int i = 0; i < count; i++)
	{
		cout << call_DB[i].firstname << " ";
		cout << call_DB[i].lastname << " \t";
		cout << call_DB[i].cell_number << "  \t";
		cout << call_DB[i].relays << "   \t";
		cout << call_DB[i].call_length << "  \t";
		cout << call_DB[i].net_cost << "  \t";
		cout << call_DB[i].tax_rate << "  \t";
		cout << call_DB[i].call_tax << "  \t";
		cout << " " << call_DB[i].total_cost << endl;
	}
}

/****************************************************************************************************************************/
//Name: Destroy_call_DB
//Precondition: The array is unchanged
//Postcondition: All memory is de-allocated from array.
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
void Destroy_call_DB(call_record * &call_DB)
{
	delete[]call_DB;
	call_DB = 0;
}


int main()
{
	int size = 5; 
	int count = 0;
	call_record *call_DB = new call_record[size];
	
	Initialize(call_DB, count, size);
	cout << "Add the record with cell number 9546541223" << endl;
	Add(call_DB, count, size, "9546541223");
	Process(call_DB, count);
	Print(call_DB, count);
	cout << "Remove the record with cell number 9546541223" << endl;
	Remove(call_DB, count, "9546541223");
	Print(call_DB, count);
	Destroy_call_DB(call_DB);

	return 0;
}
