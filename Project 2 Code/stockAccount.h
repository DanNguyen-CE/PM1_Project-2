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
#include "functions.h"

#ifndef stockAccount_h
#define stockAccount_h

class stockAccount : public Account{
public:
	stockAccount(double = 10000.00);
	~stockAccount();

	void menu(std::vector <Profile> &);

	void displayPrice(std::vector <Profile>);
	void buy(std::vector<Profile> &);
	void sell(std::vector<Profile> &);
	void displayPortfolio(std::vector<Profile> &);
	void displayHistory(std::vector <Profile>);

	void returnMain();
};

#endif