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

Account::Account(double a){
	cashBalance = a;
}

Account::~Account() {}

int Account::depositBalance(double total) {
	
	if (typeid(total) != typeid(double) || total < 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\n /!\\ Error! Invalid Input. /!\\\n";
		return -1;
	}

	else if (typeid(total) == typeid(double) && total >= 0)
		cashBalance += total;
}

int Account::withdrawBalance(double total) {

	if (typeid(total) != typeid(double) || total < 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\n /!\\ Error! Invalid Input. /!\\\n";
		return -1;
	}
	
	else if (cashBalance < total) {
		std::cout << "\n /!\\ Error! Exceeds current account balance.\n";
		return -1;
	}

	else if (cashBalance >= total && typeid(total) == typeid(double) && total >= 0)
		cashBalance -= total;
}

double Account::getBalance(){

	return cashBalance;
}
