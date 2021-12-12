#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

#include "UserInvestment.h"  // Include header file

UserInvestment::UserInvestment()  // Default constructor to initialize variables
{
	m_initialInvestment = 0;
	m_monthlyDeposit = 0;
	m_interestRate = 0;
	m_numYears = 0;
	m_openingAmount = 0;
	m_closingBalance = 0;
	m_totalInterest = 0;
}

void UserInvestment::setInitialInvestment()  // Get and validate input for investment
{
	cout << "Initial Investment Amount: ";
	cin >> m_initialInvestment;

	if (m_initialInvestment < 0)  // Check for negative number
	{
		throw runtime_error("Number cannot be below 0.");
	}

	if (cin.fail())  // Check for non-number input
	{
		throw invalid_argument("Input must be a number.");
	}
}

void UserInvestment::setMonthlyDeposit() // Get and validate input for monthly deposit
{
	cout << "Monthly Deposit: ";
	cin >> m_monthlyDeposit;

	if (m_monthlyDeposit < 0)  // Check for negative number
	{
		throw runtime_error("Number cannot be below 0.");
	}

	if (cin.fail())  // Check for non-number input
	{
		throw invalid_argument("Input must be a number.");
	}
}

void UserInvestment::setInterestRate()  // Get and validate input for interest
{
	cout << "Annual Interest: ";
	cin >> m_interestRate;

	if (m_interestRate < 0)  // Check for negative number
	{
		throw runtime_error("Number cannot be below 0.");
	}

	if (cin.fail())  // Check for non-number input
	{
		throw invalid_argument("Input must be a number.");
	}
}

void UserInvestment::setNumYears()  // Get and validate input for years
{
	cout << "Number of Years: ";
	cin >> m_numYears;

	if (m_numYears < 1)  // Check for at least one year
	{
		throw runtime_error("Number cannot be below 0.");
	}

	if (cin.fail())  // Check for non-number input
	{
		throw invalid_argument("Input must be a number.");
	}
}

void UserInvestment::getUserInput()
{
	bool validInput = false;

    cout << setfill('*') << setw(36) << "" << endl;  // Create design for output
	cout << setw(12) << "";
	cout << setfill(' ') << " Your Input ";
    cout << setfill('*') << setw(12) << "" << endl;
    cout << setfill(' ');

	while (!validInput)  // Loop until valid input is entered
	{
		try
		{
			setInitialInvestment();  // Call functions to set variables

			setMonthlyDeposit();

			setInterestRate();

			setNumYears();
		}
		catch (runtime_error& excpt)  // Catch block for thrown input errors for negative number
		{
			cout << endl;
			cout << excpt.what() << endl;  // Print error message from throw statement
			cout << "Please re-enter your values." << endl;
			cout << endl;

			continue;  // Restart loop
		}
		catch (invalid_argument& excpt)  // Catch block for thrown input errors for non-number
		{
			cout << endl;
			cout << excpt.what() << endl;  // Print error message from throw statement
			cout << "Please re-enter your values." << endl;
			cout << endl;
			cin.clear();  // Clear error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore all characters up to max size of stream or until newline is reached, used to clear cin

			continue;
		}

		validInput = true;  // Condition to end loop
	}

	system("pause");  // Print message to prompt user to press any key to continue, system will wait until key is pressed
    cout << endl;

    cout << setfill('*') << setw(36) << "" << endl << endl;  // Create bottom border
    cout << setfill(' ');  // Reset fill
}

void UserInvestment::setBalanceAndInterest(double t_monthlyDeposit)  // Calculate both closing balance each month and cumulative interest
{
	int months = m_numYears * 12;
	double interestDollars;
	double total;

	total = m_openingAmount + t_monthlyDeposit;
	interestDollars = total * ((m_interestRate / 100) / 12);

	m_closingBalance = total + interestDollars;  // Closing balance for the month
	m_totalInterest += interestDollars;  // Cumulative interest
}

void UserInvestment::displayBalance(double t_monthlyDeposit)  // Display table of yearly balance and earned interest
{
	int months = m_numYears * 12;
	stringstream balanceString;  // String to hold balance with dollar sign, allows correct formatting within columns
	stringstream interestString;  // String to hold interest with dollar sign, allows correct formatting within columns

	cout << setfill('=') << setw(62) << "" << endl;  // Desgin table for output
	cout << setfill(' ');

	cout << setw(6) << right << "Year";
	cout << setw(24) << right << "Year End Balance";
	cout << setw(27) << right << "Year End Interest" << endl;

	cout << setfill('-') << setw(62) << "" << endl;

	cout << setfill(' ');

	m_openingAmount = m_initialInvestment;  // Initialize opening amount
	int j = 1;  // Variable to keep track of years
	for (int i = 1; i <= months; ++i)  // Loop until number of years is reached
	{
		setBalanceAndInterest(t_monthlyDeposit);  // Calculate balance and cumulative interest

		if ((i % 12) == 0)  // If 12 months have passed
		{
			balanceString << fixed << setprecision(2) << "$" << m_closingBalance;  // Create string for balance and dollar sign
			interestString << fixed << setprecision(2) << "$" << m_totalInterest;  // Create string for interest and dollar sign

			cout << setw(6) << right << j;
			cout << setw(23) << right << balanceString.str().substr(0, 23);  // Print balance string, format so there is no overflow out of column
			cout << setw(27) << right << interestString.str().substr(0, 27) << endl;  // Print interest string, format so there is no overflow out of column
			
			m_totalInterest = 0;  // Reset total interest to keep track of one year at a time
			
			j += 1;  // Increment year number
			balanceString.str("");  // Clear string
			interestString.str("");  // Clear string
		}

		m_openingAmount = m_closingBalance;  // Update opening amount for enxt month
	}
}

void UserInvestment::displayWithoutDeposit()  // Display ttable with no monthly deposits
{
	cout << "   Balance and Interest Without Additional Monthly Deposits   " << endl;
	displayBalance();  // No parameter, default used
	cout << endl;
	cout << endl;
}

void UserInvestment::displayWithDeposit()  // Display table with monthly deposits
{
	cout << "   Balance and Interest With Additional Monthly Deposits   " << endl;
	displayBalance(m_monthlyDeposit);  // Pass variable as parameter
	cout << endl;
	cout << endl;
}
