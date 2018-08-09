/***********************************************************
Jose Molineros	        
Total Points:100
Due Date:  5/25/18   Due Time: 11:59PM
Course:  C0P3014
Assignment:  call_info.cpp
Professor: Dr. Lofton Bullard

Description: This program uses functions to obtain and provide call information to the user. The Input function gets information
(values of cell_num, relays, call_length) from the user as input. The Process function uses the Input information to perform
calculations (net_cost, call_tax, total_cost). The solutions to these calculations are then used by the Output function and
given out as output to the user along with the original input information.

*************************************************************/

#include <iostream> 
#include <string>
#include <iomanip>

using namespace std;

void Input(string & cell_num, int & relays, int & call_length);
void Output(const string cell_num, const int relays, const int call_length, const double & net_cost, const double & call_tax, const double & total_cost);
void Process(const int relays, const int call_length, double & net_cost, double & call_tax, double & total_cost, double & tax_rate);

//Name: Input
//Precondition: The variables (cell_num, relays, and call_length) have not been initialized
//Postcondition: The variables (cell_num, relays, and call_length) have been initialized
//Description: Get input (cell_num, relays, and call_length) from the user.

void Input(string & cell_num, int & relays, int & call_length)
{
	cout << "Enter cell phone number (with no parentheses, dashes, or spaces): \n";
	cin >> cell_num;
	cout << "Enter number of relay stations: \n";
	cin >> relays;
	cout << "Enter the length of minutes in a call: \n";
	cin >> call_length;
}

//Name: Output
//Precondition: The variables (net_cost, call_tax, and total_cost) have not been initialized
//Postcondition: The variables (net_cost, call_tax, and total_cost) have been initialized
//Description: Prints output (cell_num, relays, call_length, net_cost, call_tax, and total_cost) to the user.

void Output(const string cell_num, const int relays, const int call_length, const double & net_cost, const double & call_tax, const double & total_cost)
{
	cout << "***************************" << endl;
	cout << "Cell Phone: " << setw(15) << cell_num << endl;
	cout << "***************************" << endl;
	cout << "Relay Stations: " << setw(3) << relays << endl;
	cout << "Minutes Used: " << setw(5) << call_length << endl;
	cout << "Net Cost: " << setw(12) << net_cost << setprecision(2) << fixed << endl;
	cout << "Call Tax: " << setw(11) << call_tax << setprecision(2) << fixed << endl;
	cout << "Total Cost: " << setw(10) << total_cost << setprecision(2) << fixed << endl;
}

//Name:  Process
//Precondition: The variables (relays, call_length, net_cost, call_tax, total_cost, and tax_rate) have not been initialized
//Postcondition: The variables (relays, call_length, net_cost, call_tax, total_cost, and tax_rate) have been initialized
//Description: Perform calculations (net_cost, call_tax, total_cost) based on Input information.

void Process(const int relays, const int call_length, double & net_cost, double & call_tax, double & total_cost, double & tax_rate)
{
	net_cost = (relays / 50.0 * 0.40 * call_length);

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

	call_tax = (net_cost * tax_rate);
	total_cost = (net_cost + call_tax);
}

int main()
{
	string user_response = "y";
	string cell_num;
	int call_length;
	int relays;
	double net_cost, call_tax, total_cost, tax_rate;

	while (user_response == "y" || user_response == "Y")
	{
		Input(cell_num, relays, call_length);
		Process(relays, call_length, net_cost, call_tax, total_cost, tax_rate);
		Output(cell_num, relays, call_length, net_cost, call_tax, total_cost);

		cout << "Would you like to do another calculation (Y or N): " << endl;
		cin >> user_response;
	}

	return  0;
}







