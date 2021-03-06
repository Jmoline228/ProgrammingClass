﻿/***********************************************************
Jose Molineros	        
Total Points:100
Due Date:  08/02/2018   Due Time: 11:59PM
Course:  C0P3014
Assignment:  call_stats7.cpp
Professor: Dr. Lofton Bullard

Description: This program will implement a class called “call_class," which
will manage a dynamic array of call records (Call_DB). It reads data from a file (callstats_data.txt) and input the information 
into the dynamic array. If the count is equal to the size then double_size is called and the memory allocated to call_DB is doubled. 
The process function is called to process the file information and the file is closed. The destructor is called at the end,
de-allocating all memory in the array.
*************************************************************/

#include <iostream>
#include <string>
#include <fstream>

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
class call_class
{
public:
	call_class();
	~call_class(); //de-allocates all memory allocate to call_DB by operator new.
	bool is_empty(); //inline implementation
	bool is_full();//inline implementation
	int search(const string key);//returns location if item in listl; otherwise return -1
	void add(); //adds a call record to call_DB
	call_class & operator-(const string key); //removes an item from the list
	void double_size();
	void process();
	friend ostream & operator<<(ostream & out_to_screen, call_class & Org); //prints all the elements in the list to the screen.
private:
	int count;
	int size;
	call_record *call_DB;
};
/*************************************************************************
***********************************************************/
//Name: default constructor
//Precondition: No file has been opened or any information entered
//Postcondition: Reads information from "callstats_data.txt" and put it into dynamic array
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record,
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/*************************************************************************
***********************************************************/
call_class::call_class()
{
	count = 0;
	size = 5;
	call_DB = new call_record[size];

	ifstream in;

	in.open("callstats_data.txt");

	while (!in.eof())
	{
		if (is_full())
		{
			double_size();
		}
		
		in >> call_DB[count].firstname;
		in >> call_DB[count].lastname;
		in >> call_DB[count].cell_number;
		in >> call_DB[count].relays;
		in >> call_DB[count].call_length;

		count++;
	}

	process();
	in.close();
}
/*************************************************************************
**********************************************************/
//Name: is_empty
//Precondition: Bool function with unknown capacity status
//Postcondition: Status of capacity is known, Returns true if count is equal to 0
//Decription: returns true if call_DB is empty
/*************************************************************************
*********************************************************/
bool call_class::is_empty()
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
/*************************************************************************
*********************************************************/
//Name: is_full
//Precondition: Bool function with unknown capacity status
//Postcondition: Status of capacity is known, Returns true if count is equal to size
//Decription: returns true if call_DB is full
/*************************************************************************
********************************************************/
bool call_class::is_full()
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
/*************************************************************************
*********************************************************/
//Name: search
//Precondition: Int function with no known key
//Postcondition: Key is Known, returns location of key in call_db if it is there
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*************************************************************************
********************************************************/
int call_class::search(const string key)
{
	int i;
	if (!is_empty()) {
		for (i = 0; i < count; i++)
		{
			if (call_DB[i].cell_number == key) {
				return i;
			}
		}
	}

	return -1;
}
/*************************************************************************
********************************************************/
//Name: add
//Precondition: void function with no action
//Postcondition: Prompts the user for input, adds new array member and count goes up by 1
//Decription: adds the informaton for a call record to call_DB; if call_DB is full, double_size is called to increase the size of call_DB.
/*************************************************************************
*******************************************************/
void call_class::add()
{
	if (is_full()) 
	{
		double_size(); 
	}

	int i = count;


	cout << "Please enter the first name." << endl;
	cin >> call_DB[i].firstname;
	cout << "Please enter the last name." << endl;
	cin >> call_DB[i].lastname;
	cout << "Please enter the cell phone number." << endl;
	cin >> call_DB[i].cell_number;
	cout << "Please enter the number of relays." << endl;
	cin >> call_DB[i].relays;
	cout << "Please enter the number of minutes." << endl;
	cin >> call_DB[i].call_length;

	count++;

	if (is_full())
	{
		double_size();
	}

	
	process();
}
/*************************************************************************
*******************************************************/
//Name: operator-
//Precondition: Class and variables remain unchanged
//Postcondition: If key is found, removes key and elements from array and count goes down by 1
//Decription: remove key from call_DB if it is there.
/*************************************************************************
******************************************************/
call_class & call_class::operator-(const string key)
{
	if (!is_empty()) 
	{
		if (search(key) != -1) 
		{
			do 
			{
				
				for (int x = search(key); x < count - 1; x++)
				{ 
					call_DB[x] = call_DB[x + 1];
				}
				count--; 

			} while (search(key) != -1); 
		}
	}
	return *this;
}
/*************************************************************************
*****************************************************/
//Name: double_size
//Precondition: Array size remains unchanged
//Postcondition: Array size has been doubled
//Decription: doubles the size (capacity) of call_DB
/*************************************************************************
*****************************************************/
void call_class::double_size()
{
	size *= 2;
	call_record *temp = new call_record[size];
	for (int i = 0; i<count; i++)
	{
		temp[i] = call_DB[i];
	}
	delete[] call_DB;
	call_DB = temp;
}
/*************************************************************************
*****************************************************/
//Name: process
//Precondition: Array variables and elements remain unchanged
//Postcondition: Calculations have been performed
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*************************************************************************
****************************************************/
void call_class::process()
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
		else  if (call_DB[i].relays > 50)
		{
			call_DB[i].tax_rate = 0.12;
		}

		call_DB[i].call_tax = (call_DB[i].net_cost*call_DB[i].tax_rate);
		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;
	}
}
/*************************************************************************
***************************************************/
//Name: operator<<
//Precondition: Nothing has been printed to screen
//Postcondition: Call_record info has been printed to screen
//Decription: Overloading operator<< as a friend function. Prints every field of every call_record in call_DB
//                   formatted to the screen.
/*************************************************************************
**************************************************/
ostream & operator<<(ostream & out, call_class & Org)
{
	out.setf(ios::showpoint);
	out.precision(2);
	out.setf(ios::fixed);

	for (int i = 0; i < Org.count; i++)
	{
		out << Org.call_DB[i].firstname 
			<< "  " << Org.call_DB[i].lastname << "   \t"
			<< Org.call_DB[i].relays << "   \t"
			<< Org.call_DB[i].cell_number << "   \t"
			<< Org.call_DB[i].call_length <<  "   \t"
			<< Org.call_DB[i].net_cost << "   \t"
			<< Org.call_DB[i].tax_rate << "   \t"
			<< Org.call_DB[i].call_tax << "   \t"
			<< Org.call_DB[i].total_cost << "   \t" << endl;
	}
	return out;
}
/*************************************************************************
***************************************************/
//Name: destructor
//Precondition: Memory for array call_DB remains unchanged
//Postcondition: All memory de-allocated for call_DB
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/*************************************************************************
**************************************************/
call_class::~call_class()
{
	{
		cout << "Destructor Called." << endl;
		delete[] call_DB;
	}
}

//driver to test the functionality of your class.
int main()
{
	cout << "TEST1: Testing the Default Constructor, is_full and double_size\n";
	call_class MyClass;
	cout << "Finish TEST1: testing the default constructor\n\n\n\n";
	
	cout << "Test2: Testing add, double_size, process, and is_full() \n"; 
	MyClass.add();
	cout << "Finish TEST2\n\n\n\n";
	
	cout << "Test3: Testing operator-, serach, and is_empty\n";
	MyClass -"5617278899" - "9546321555" - "1234567890";
	cout << MyClass;
	cout << "Finish TEST3\n\n\n\n";
	
	cout << "Test4: Testing operator<<\n\n";
	cout << MyClass << endl;
	cout << "Finish TEST4\n\n\n\n";
	
	cout << "The destructor will be called automatically\n";
	return 0;
}
