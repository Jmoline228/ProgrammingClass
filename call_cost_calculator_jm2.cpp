﻿/***********************************************************
Jose Molineros	        
Total Points:100
Due Date:  5/12/18   Due Time: 11:59PM
Course:  C0P3014
Assignment:  call_cost_calculator.cpp
Professor: Dr. Lofton Bullard

Description: This program gets call information (values of cell_num, relays, call_length) from the user as input and
			 uses that information to perform calculations (net_cost, call_tax, total_cost). The solutions to these calculations
			 are then given out as output to the user along with the original input information.


*************************************************************/

#include <iostream> 
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	string user_response = "y";
	string cell_num;
	int call_length;
	int relays;
	float net_cost, call_tax, total_cost, tax_rate;
	

	while (user_response == "y" || user_response == "Y")		
	{
		cout << "Enter cell phone number (with no parentheses, dashes, or spaces): \n";					
		cin >> cell_num;
		cout << "Enter number of relay stations: \n";
		cin >> relays;
		cout << "Enter the length of minutes in a call: \n";
		cin >> call_length;

		if (relays <= 5) {
			tax_rate = 0.01;
		}
		else if ((6 <= relays) && (relays <= 11)) {
			tax_rate = 0.03;
		}
		else if ((12 <= relays) && (relays <= 20)) {
			tax_rate = 0.05;
		}
		else if ((21 <= relays) && (relays <= 50)) {
			tax_rate = 0.08;
		}
		else if (relays > 50) {
			tax_rate = 0.12;
		}

		net_cost = (relays / 50.0 * 0.40 * call_length);
		call_tax = (net_cost * tax_rate);
		total_cost = (net_cost + call_tax);

		cout << "Cell Phone: " << setw(15) << cell_num << endl;
		cout << "Relay Stations: " << setw(3) << relays << endl;
		cout << "Minutes Used: " << setw(6) << call_length << endl;
		cout << "Net Cost: " << setw(9) << net_cost << setprecision(2) << fixed << endl;
		cout << "Tax Rate: " << setw(11) << tax_rate << setprecision(2) << fixed << endl;
		cout << "Call Tax: " << setw(11) << call_tax << setprecision(2) << fixed << endl;
		cout << "Total Cost: " << setw(10) << total_cost << setprecision(2) << fixed << endl;

		cout << "Would you like to do another calculation (Y or N): " << endl;
		cin >> user_response;
	}

	return  0;
}

