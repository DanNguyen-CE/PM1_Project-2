/*************************************************************************
//																		//
//	Programming Methodology I (14:332:252)								//
//	PROJECT 2 -- "Stock & Bank System"									//
//																		//
//	Daniel Nguyen														//
//	Section 1															//
//	May 2018															//
//																		//
*************************************************************************/

#include "Account.h"
#include "stockAccount.h"
#include "functions.h"

#ifndef bankAccount_h
#define bankAccount_h

class bankAccount : public Account, public stockAccount{
public:
	bankAccount(double = 10000.00);
	~bankAccount();

	void menu(std::vector<Profile> &);

	void displayBalance(std::vector<Profile> &);
	void deposit(std::vector<Profile> &);
	void withdraw(std::vector<Profile> &);
	void displayHistory(std::vector<Profile> &);

	void returnMain();
};

#endif