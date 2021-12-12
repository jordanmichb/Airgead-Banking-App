#include <iostream>
using namespace std;

#include "UserInvestment.h"  // Include header file

int main()
{
	char userInput = 'y';  // Initialize variable to control loop
	UserInvestment investment1;  // Create new object based on the class

	while (userInput == 'y') {  // Loop until prompted to exit
		investment1.getUserInput();  // Get and validate input
		investment1.displayWithoutDeposit();  // Show table without monthly deposits
		investment1.displayWithDeposit();  // Show table with monthly deposits

		cout << "Would you like to try different values? (Y/y or N/n)" << endl;  // Opportunity to exit loop
		cin >> userInput;
		cout << endl;
	}

	cout << "Exiting Program..." << endl;
}