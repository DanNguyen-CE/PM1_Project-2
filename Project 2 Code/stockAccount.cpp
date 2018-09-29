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

#include "stockAccount.h"

stockAccount::stockAccount(double a) : Account(a) {}

stockAccount::~stockAccount() {}

void stockAccount::menu(std::vector <Profile> &ProfileData){
	
	int selection;

	Sleep(500);

	sortProfile(ProfileData); // Sorts Stocks Profile

	std::cout <<
		"\n ============================================" <<
		"\n |          Stock Portfolio Account         |" <<
		"\n ============================================" <<
		
		"\n 1. Display current price for a stock symbol" <<
		"\n 2. Buy stock" << 
		"\n 3. Sell stock" <<
		"\n 4. Display current portfolio" <<
		"\n 5. Display transactions history" <<
		"\n 6. Return to main menu" <<

		"\n\n Your selection : ";

	std::cin >> selection;

	switch (selection) {
	case 1: displayPrice(ProfileData); break;
	case 2: buy(ProfileData); break;
	case 3: sell(ProfileData); break;
	case 4: displayPortfolio(ProfileData); menu(ProfileData); break;
	case 5: displayHistory(ProfileData); break;
	case 6: returnMain(); break;
	default: std::cout << "\n /!\\ Error! Invalid Input. /!\\\n"; 
		std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
		menu(ProfileData);
	}
}

void stockAccount::displayPrice(std::vector <Profile> ProfileData) {

	int i,check;
	std::vector <std::string> tokens;
	std::time_t const time = std::time(NULL);

	check = searchStocks(i,tokens); // Custom function to ask for and find certain stock given stock symbol.

	if (check == -1) { // If cannot be found, returned to menu.
		std::cout << "\n /!\\ Error! Stock not found. /!\\\n";
		menu(ProfileData);
	}

	else if (check != -1) { // If found, print price.
		std::cout << "\n " << tokens[i] << "\t" << tokens[i + 1] << "\t\t" << tokens[i + 2] << "\t" << std::put_time(std::localtime(&time), "%T") << "\n";
		menu(ProfileData);
	}
}

void stockAccount::buy(std::vector <Profile> &ProfileData){

	int i,amount,check;
	double price, payment, total;
	std::vector <std::string> tokens;
	std::time_t const time = std::time(NULL);


	check = searchStocks(i, tokens); // Custom function to ask for and find certain stock given stock symbol.

	if (check == -1) { // If cannot be found, returned to menu.
		std::cout << "\n /!\\ Error! Stock not found. /!\\\n";
		menu(ProfileData);
	}

	else if (check != -1) // If found, print price.
		std::cout << "\n " << tokens[i] << "\t" << tokens[i + 1] << "\t\t" << tokens[i + 2] << "\t" << std::put_time(std::localtime(&time), "%T") << "\n";

	std::cout << "\n Please enter the amount of share you want to buy: ";
	std::cin >> amount;
	if (checkInput(amount) == -1) {
		menu(ProfileData);
	}
	std::cout << "\n Please enter the price you are willing to pay for each share: $";
	std::cin >> payment;
	if (checkInput(payment) == -1) { 
		menu(ProfileData);
	}

	price = stod(tokens[i + 2]); // Convert string to double

	total = payment * amount;
	
	if (amount <= 0) {
		std::cout << "\n /!\\ Sorry, you cannot buy that amount! /!\\\n";
		menu(ProfileData);
	}

	else if (payment < price) {
		std::cout << "\n /!\\ Sorry, you must be willing to pay more than or equal to the current price per stock! /!\\\n";
		menu(ProfileData);
	}

	if (buyProfile(ProfileData, i, tokens, amount, price) == -1 || withdrawBalance(total) == -1)
		menu(ProfileData);

	{// Record transaction history
		std::fstream fs;
		fs.open("stock_transaction_history.txt", std::fstream::in | std::fstream::out | std::fstream::app);

		fs << "\n Buy" 
			<< "\t\t" << tokens[i] 
			<< "\t\t" << amount 
			<< setTabs(amount) << "$" << std::fixed << std::setprecision(2) << payment 
			<< "\t\t" << std::put_time(std::localtime(&time), "%T");

		fs.close();
	}

	std::cout << "\n Purchase Successful! Returning to menu...\n";

	menu(ProfileData); // Return to submenu.
}

void stockAccount::sell(std::vector <Profile> &ProfileData){

	int i, amount, check;
	double price, payment, total;
	std::vector <std::string> tokens;
	std::time_t const time = std::time(NULL);

	check = searchStocks(i, tokens); // Custom function to ask for and find certain stock given stock symbol.

	if (check == -1) // If cannot be found, returned to menu.
		menu(ProfileData);

	else if (check != -1) // If found, print price.
		std::cout << "\n " << tokens[i] << "\t" << tokens[i + 1] << "\t\t" << tokens[i + 2] << "\t" << std::put_time(std::localtime(&time), "%T") << "\n";

	std::cout << "\n Please enter the amount of share you want to sell: ";
	std::cin >> amount;
	std::cout << "\n Please enter the price you are willing to sell for each share: $";
	std::cin >> payment;

	price = stod(tokens[i + 2]); // Convert string to double.

	total = payment * amount;

	if (checkProfile(ProfileData, i, tokens, amount, price) == -1) {
			menu(ProfileData);
	}

	else if (amount <= 0) {
		std::cout << "\n /!\\ Sorry, you cannot sell that amount! /!\\\n";
		menu(ProfileData);
	}

	else if (payment > price) {
		std::cout << "\n /!\\ Sorry, you must be willing to sell for less than or equal to the current price per stock! /!\\\n";
		menu(ProfileData);
	}

	else if (sellProfile(ProfileData, i, tokens, amount, price) == -1 || depositBalance(total) == -1)
		menu(ProfileData);

	{// Record transaction history
		std::fstream fs;
		fs.open("stock_transaction_history.txt", std::fstream::in | std::fstream::out | std::fstream::app);

		fs << "\n Sell"
			<< "\t\t" << tokens[i]
			<< "\t\t" << amount
			<< setTabs(amount) << "$" << std::fixed << std::setprecision(2) << payment
			<< "\t\t" << std::put_time(std::localtime(&time), "%T");

		fs.close();
	}

	std::cout << "\n Sale Successful! Returning to menu...\n";

	menu(ProfileData); // Return to submenu.
}

void stockAccount::displayPortfolio(std::vector<Profile> &ProfileData){

	std::vector <std::string> tokens; int i = 0;
	double value = 0; double currentPrice = 0; int number;

	std::cout <<
		"\n ============================================" <<
		"\n |          Your Current Portfolio          |" <<
		"\n ============================================" <<
		std::fixed << std::setprecision(2) << "\n Cash Balance: $" << getBalance() << std::endl <<

		"\n Symbol" << "\t\t" << "Company" << "\t\t\t\t" << "Number" << "\t\t" << "Price" << "\t\t\t" << "Total\n\n";

	for (int j = 0; j < index + 1; j++) {

		updateStocks(i, j, tokens, ProfileData);
		currentPrice = stod(tokens[i + 2]);

		ProfileData[j].price = currentPrice;
		ProfileData[j].total = ProfileData[j].price * ProfileData[j].number;
		number = ProfileData[j].number;

		std::cout << " " <<
			ProfileData[j].symbol <<
			"\t\t" << ProfileData[j].company <<
			setTabs(i+1,tokens) << ProfileData[j].number <<
			setTabs(number) << "$" << ProfileData[j].price <<
			setTabs(currentPrice) << "$" << ProfileData[j].total << 
			std::endl;

		value += ProfileData[j].total;
	}

	std::cout << "\n Total Profile Value: $" << value + getBalance() << std::endl;
}

void stockAccount::displayHistory(std::vector <Profile> ProfileData){
	
	std::ifstream file("stock_transaction_history.txt");
	std::string line;
	
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
	}

	file.close();
	menu(ProfileData);
}

void stockAccount::returnMain(){}
