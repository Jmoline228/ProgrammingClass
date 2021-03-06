﻿/***********************************************************
Jose Molineros	        
Total Points:100
Due Date:  07/05/2018   Due Time: 11:59PM
Course:  C0P3014
Assignment:  charword_freq.cpp
Professor: Dr. Lofton Bullard

Description: This program uses functions to obtain and provide letter frequencies to the user. 
The letter_count function opens the "mytext.dat" file, reads the file and counts how many 
letters of each type there are, then outputs the results to the user.
*************************************************************/


#include <fstream>
#include <iostream>

using namespace std;

void letter_count(ifstream & words);

//Name: letter_count
//Precondition: The variables (ifstream) have not been initialized
//Postcondition: The variables (ifstream) have been initialized
//Description: Get input "mytext.dat", reads the file and counts how many letters of each type there are, then outputs to the user.
void letter_count(ifstream & words)
{
	int freq[128];
	char ch;

	words.open("mytext.dat");
	if (!words)
	{
		cout << "The input file could not be opened." << endl;
		return;
	}

	for (int i = 0; i < 128; i++)
	{
		freq[i] = 0;
	}

	ch = words.get();
	while (ch != EOF)
	{
		cout << ch;
		ch = toupper(ch);
		freq[ch]++;
		ch = words.get();
	}

	cout << endl << "Letter frequencies." << endl;
	for (char ch = 'A'; ch <= 'Z'; ch++)
	{
		if (freq[ch] > 0)
		{
			cout << ch << " " << freq[ch] << endl;
		}
	}
}

int main()
{
	ifstream words;
	
	letter_count(words);

	return 0;
}
