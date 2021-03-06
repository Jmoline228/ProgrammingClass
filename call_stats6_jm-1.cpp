﻿/***********************************************************
Jose Molineros	        
Total Points:100
Due Date:  07/26/2018   Due Time: 11:59PM
Course:  C0P3014
Assignment:  call_stats6.cpp
Professor: Dr. Lofton Bullard

Description: This program will implement a class called “call_class", which
will manage a dynamic array of call records called "call_stats6.cpp"

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
	void remove(const string key); //removes an item from the list
	void double_size();
	void process();
	void print(); //prints all the elements in the list to the screen
private:
	int count;
	int size;
	call_record *call_DB;
};




/************************************************************************************************************************************/
//Name: default constructor
//Precondition: Reads information from "callstats_data.txt" and puts it into dynamic array
//Postcondition: no parameters in the functions because it is called above
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
call_class::call_class()
{

	ifstream in; 
	in.open("callstats_data.txt"); 

	if (in.fail()) 
	{
		cout << "Input file did not open correctly"
			<< endl;
		exit(1);
	}
	count = 0;
	size = 10;
	call_DB = new call_record[size];

	while (!in.eof())
	{
		in >> call_DB[count].firstname;
		in >> call_DB[count].lastname;
		in >> call_DB[count].cell_number;
		in >> call_DB[count].relays;
		in >> call_DB[count].call_length;
		count++;
		if (is_full())
		{
			double_size();
		}

	}
	in.close();
}

/***********************************************************************************************************************************/
//Name: is_empty
//Precondition: Bool function
//Postcondition: Returns true if count is equal to 0
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/
bool call_class::is_empty()
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition: Bool function
//Postcondition: Returns true if count is equal to size
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
bool call_class::is_full()
{
	return count == size;
}

/**********************************************************************************************************************************/
//Name: search
//Precondition: Int function
//Postcondition: Will return location of key in call_db
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
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

/*********************************************************************************************************************************/
//Name: add
//Precondition: Void function
//Postcondition: Prompts the user for input
//Decription: Adds a call_record to call_DB; if call_DB is full, double_size is called to increase the size of call_DB. The user 
//            is prompted to enter the firstname, lastname, cell number, relays and call length. 
/********************************************************************************************************************************/
void call_class::add()
{
	call_record call_recd;

	if (is_full())
	{
		double_size();
	}
	cout << "Enter the Cell Number: ";
	cin >> call_recd.cell_number;
	cout << "Enter the First Name: ";
	cin >> call_recd.firstname;
	cout << "Enter the Last Name: ";
	cin >> call_recd.lastname;
	cout << "Enter the Number of relays: ";
	cin >> call_recd.relays;
	cout << "Enter the Call Length: ";
	cin >> call_recd.call_length;

	call_DB[size - 1] = call_recd;
	count++;

}

/********************************************************************************************************************************/
//Name: remove
//Precondition: Void function
//Postcondition: Duplicate records with same cell number are deleted.
//Decription: Removes key from call_DB if it is there.
/*******************************************************************************************************************************/
void call_class::remove(const string key)
{
	cout << "Deleting the record with cell number :" + key << endl;

	int loc = search(key);
	if (loc != -1)
	{
		for (int j = loc; j<count - 1; j++)
		{
			call_DB[j] = call_DB[j + 1];
		}
		count--;
	}
}

/******************************************************************************************************************************/
//Name: double_size
//Precondition: Void function
//Postcondition: Capacity of Call_DB doubled
//Decription: Doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
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


/******************************************************************************************************************************/
//Name: process
//Precondition: Void function
//Postcondition:  Performs calculation from information provided
//Decription: Calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void call_class::process()
{
	int i; 
	for (i = 0; i < count; i++)
	{

		if (0 <= call_DB[i].relays && call_DB[i].relays <= 5)
		{
			call_DB[i].tax_rate = 0.01;
		}
		else if (6 <= call_DB[i].relays && call_DB[i].relays <= 11)
		{
			call_DB[i].tax_rate = 0.03;
		}
		else if (12 <= call_DB[i].relays && call_DB[i].relays <= 20)
		{
			call_DB[i].tax_rate = 0.05;
		}
		else if (21 <= call_DB[i].relays && call_DB[i].relays <= 50)
		{
			call_DB[i].tax_rate = 0.08;
		}
		else if (call_DB[i].relays >50)
		{
			call_DB[i].tax_rate = 0.12;
		}

		call_DB[i].net_cost = call_DB[i].relays / 50.0 * .40 * call_DB[i].call_length;

		call_DB[i].call_tax = call_DB[i].net_cost * call_DB[i].tax_rate;
		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;

	}
}


/****************************************************************************************************************************/
//Name: print
//Precondition: Void function
//Postcondition: Prints the information to the screen
//Decription: Prints every field of every call_record in call_DB formatted to the screen.
/***************************************************************************************************************************/
void call_class::print()
{
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout.setf(ios::fixed);

	for (int i = 0; i<count; i++)
	{
		cout << call_DB[i].firstname
			<< "  " << call_DB[i].lastname
			<< "  " << call_DB[i].relays << "   \t"
			<< "  " << call_DB[i].cell_number << "   \t"
			<< "  " << call_DB[i].call_length << "   \t"
			<< "  " << call_DB[i].net_cost << "   \t"
			<< "  " << call_DB[i].tax_rate << "   \t"
			<< "  " << call_DB[i].call_tax << "   \t"
			<< "  " << call_DB[i].total_cost << "   \t" << endl;
	}
}

/****************************************************************************************************************************/
//Name: destructor
//Precondition: 
//Postcondition: De-allocates memory
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
call_class::~call_class()
{
	cout << "Destructor called\n";

	delete[]  call_DB;
}


int main()
{
	call_class MyClass;
	MyClass.process();
	cout << "************TEST#1*******************************\n";
	cout << "Testing the default constructor, is_full";
	cout << " double_size, process and print\n";
	MyClass.print();
	cout << endl;
	cout << "*************************************************\n";
	cout << endl << endl;
	
	cout << "************TEST#2********************************\n";
	cout << "Testing add (possible is_full and double_size) and ";
	cout << "print \n";
	MyClass.add();
	MyClass.process();
	MyClass.print();
	cout << "*************************************************\n";
	cout << endl << endl;
	
	cout << "************TEST#3********************************";
	cout << "Testing remove, search (possible is_empty) and print \n";
	MyClass.remove("954321555");
	MyClass.print();
	MyClass.remove("5617278899");
	MyClass.print();
	MyClass.remove("7542346622");
	MyClass.print();
	MyClass.remove("000000000");
	MyClass.print();
	cout << "Destructor Test**********************************************\n";
	cout << "Destructor called automatically by compiler*************************\n";
	cout << endl << endl;
	cout << "*************************************************\n";
	cout << endl << endl;
	return 0;
}
