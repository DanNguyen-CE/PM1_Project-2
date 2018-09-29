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

#include "functions.h"
#include "Account.h"
#include "bankAccount.h"
#include "stockAccount.h"

double Account::cashBalance;

int main() {
	
	// Reset all transaction history
	{
		std::ofstream stock;
		stock.open("stock_transaction_history.txt", std::ofstream::out | std::ofstream::trunc);
		stock << "\n Action\t\tSymbol\t\tShares\t\tPrice\t\tTime\n";
		stock.close();

		std::ofstream bank;
		bank.open("bank_transaction_history.txt", std::ofstream::out | std::ofstream::trunc);
		bank << "\n Action\t\tAmount\t\t\tBalance\t\t\tDate\t\tTime\n";
		bank.close();
	}

	// Profile data storage
	std::vector <Profile> ProfileData;

	// Instatiate Accounts
	stockAccount myStocks;
	bankAccount myBank;

	while (1) {

		Sleep(500);

		switch (mainMenu()) {
		case 1: myStocks.menu(ProfileData); break;
		case 2: myBank.menu(ProfileData); break;
		case 3: close(); break;
		default: std::cout << "\n /!\\ Error! Invalid Input. /!\\\n"; break;
		}
	}

	return 0;
}