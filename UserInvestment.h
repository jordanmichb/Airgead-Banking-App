#ifndef AIRGEADBANKINGAPP_USERINVESTMENT_H_
#define AIRGEADBANKINGAPP_USERINVESTMENT_H_

class UserInvestment  // Class for user investment
{
	public:  // Public members for use in main
		UserInvestment();
		void getUserInput();
		void displayWithoutDeposit();
		void displayWithDeposit();
	private:  // Private members for use within class
		double m_initialInvestment;
		double m_monthlyDeposit;
		double m_interestRate;
		int m_numYears;
		double m_openingAmount;
		double m_closingBalance;
		double m_totalInterest;
		void setInitialInvestment();
		void setMonthlyDeposit();
		void setInterestRate();
		void setNumYears();
		void setBalanceAndInterest(double t_monthlyDeposit);
		void displayBalance(double t_monthlyDeposit = 0);
};

#endif