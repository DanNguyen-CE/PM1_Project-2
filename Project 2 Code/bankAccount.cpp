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

#include "bankAccount.h"

bankAccount::bankAccount(double a) : Account (a) {}

bankAccount::~bankAccount() {}

void bankAccount::menu(std::vector<Profile> &ProfileData){

	int selection;

	Sleep(500);

	std::cout <<
		"\n ============================================" <<
		"\n |              Bank Account                |" <<
		"\n ============================================" <<

		"\n 1. Display current cash balance" <<
		"\n 2. Deposit to account" <<
		"\n 3. Withdraw from account" <<
		"\n 4. Display transactions history" <<
		"\n 5. Return to main menu" <<

		"\n\n Your selection : ";

	std::cin >> selection;

	switch (selection) {
	case 1: displayBalance(ProfileData); break;
	case 2: deposit(ProfileData); break;
	case 3: withdraw(ProfileData); break;
	case 4: displayHistory(ProfileData); break;
	case 5: returnMain(); break;
	default: std::cout << "\n /!\\ Error! Invalid Input. /!\\\n"; 
		std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
		menu(ProfileData);
	}
}

void bankAccount::displayBalance(std::vector<Profile> &ProfileData){
	
	stockAccount::displayPortfolio(ProfileData);
	menu(ProfileData);
}

void bankAccount::deposit(std::vector<Profile> &ProfileData){
	
	double amount;

	std::cout << "\n Please input the amount you would like to deposit: $";
	std::cin >> amount;
	
	if (checkInput(amount) == -1)
		menu(ProfileData);

	Account::depositBalance(amount);
	stockAccount::displayPortfolio(ProfileData);

	{// Record transaction history

		std::time_t const time = std::time(NULL);
		std::time_t const date = std::time(NULL);

		std::fstream fs;
		fs.open("bank_transaction_history.txt", std::fstream::in | std::fstream::out | std::fstream::app);

		fs << "\n Deposit"
			<< "\t" << "$" << std::fixed << std::setprecision(2) << amount
			<< setTabs(amount) << "$" << std::left << std::fixed << std::setprecision(2) << Account::getBalance()
			<< setTabs(Account::getBalance()) << std::put_time(std::localtime(&time), "%F")
			<< "\t" << std::put_time(std::localtime(&time), "%T");

		fs.close();
	}

	std::cout << "\n Deposit Successful! Returning to menu...\n";

	menu(ProfileData);
}

void bankAccount::withdraw(std::vector<Profile> &ProfileData){
	
	double amount;

	std::cout << "\n Please input the amount you would like to withdraw: $";
	std::cin >> amount;

	if (checkInput(amount) == -1)
		menu(ProfileData);

	if (amount > Account::getBalance()) {
		std::cout << "\n /!\\ Error! You do not have enough money in your account to withdraw that amount! /!\\\n";
		menu(ProfileData);
	}

	Account::withdrawBalance(amount);
	stockAccount::displayPortfolio(ProfileData);

	{// Record transaction history

		std::time_t const time = std::time(NULL);
		std::time_t const date = std::time(NULL);

		std::fstream fs;
		fs.open("bank_transaction_history.txt", std::fstream::in | std::fstream::out | std::fstream::app);

		fs << "\n Withdraw"
			<< "\t" << "$" << std::fixed << std::setprecision(2) << amount
			<< setTabs(amount) << "$" << std::left << std::fixed << std::setprecision(2) << Account::getBalance()
			<< setTabs(Account::getBalance()) << std::put_time(std::localtime(&time), "%F")
			<< "\t" << std::put_time(std::localtime(&time), "%T");

		fs.close();
	}

	std::cout << "\n Withdrawl Successful! Returning to menu...\n";

	menu(ProfileData);
}

void bankAccount::displayHistory(std::vector<Profile> &ProfileData){
	
	std::ifstream file("bank_transaction_history.txt");
	std::string line;

	while (std::getline(file, line)) {
		std::cout << line << std::endl;
	}

	file.close();
	menu(ProfileData);
}

void bankAccount::returnMain(){}
