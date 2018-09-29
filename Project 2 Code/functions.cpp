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
int index = -1;

int mainMenu() {

	int selection;

	std::cout <<
		"\n ============================================" <<
		"\n | Welcome to the Account Management System |" <<
		"\n |   Please select an account to access     |" <<
		"\n ============================================" <<

		"\n\n 1. Stock Portfolio Account" <<
		"\n 2. Bank Account" <<
		"\n 3. Exit" <<

		"\n\n Your selection : ";

	std::cin >> selection;

	if (typeid(selection) != typeid(int) || selection < 1 || selection > 3) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return -1;
	}

	else if (typeid(selection) == typeid(int) && selection >= 1 && selection <= 3)
		return selection;
}

void close() {

	std::cout <<
		"\n Thank you for using the Account Management System!";

	Sleep(1000);

	exit(0);
}

void sortProfile(std::vector <Profile> &ProfileData) {
	int n, k, sm_index;
	std::string smallest;

	// Checks for smallest account number in vector
	for (k = 0; k <= index; k++) {
		smallest = ProfileData[k].symbol;
		sm_index = k;

		for (n = k + 1; n <= index; n++) {
			if (ProfileData[n].symbol < smallest) {
				smallest = ProfileData[n].symbol;
				smallest = n;

				// Swaps accounts
				std::string temp1; std::string temp2;
				int temp3;
				double temp4;
				double temp5;

				temp1 = ProfileData[sm_index].symbol;
				temp2 = ProfileData[sm_index].company;
				temp3 = ProfileData[sm_index].number;
				temp4 = ProfileData[sm_index].price;
				temp5 = ProfileData[sm_index].total;

				ProfileData[sm_index].symbol = ProfileData[n].symbol;
				ProfileData[sm_index].company = ProfileData[n].company;
				ProfileData[sm_index].number = ProfileData[n].number;
				ProfileData[sm_index].price = ProfileData[n].price;
				ProfileData[sm_index].total = ProfileData[n].total;

				ProfileData[n].symbol = temp1;
				ProfileData[n].company = temp2;
				ProfileData[n].number = temp3;
				ProfileData[n].price = temp4;
				ProfileData[n].total = temp5;
			}
		}
	}

}


// Gets random stock file and saves all information for use.
int searchStocks(int &i, std::vector <std::string> &tokens) {

	std::string symbol;
	std::string line;
	std::ifstream file;

	// Requests stock symbol.
	std::cout << "\n Please enter stock symbol: ";
	std::cin.clear();
	std::cin.ignore();
	std::getline(std::cin, symbol);

	// Obtains a random "Stock#.txt" file.
	srand(time(NULL));
	int num = rand() % 4 + 1;
	std::string name = "stock" + std::to_string(num) + ".txt";

	file.open(name);

	// Reads through "Stock#.txt" file and isolates data.
	while (std::getline(file, line)) {

		std::string delim = "\t";
		for (int i = 0; i < 3; i++) {
			if (i == 2) {
				line = line.substr(line.rfind(delim) + 1, std::string::npos);
				tokens.push_back(line);
			}
			tokens.push_back(line.substr(0, line.find(delim)));
			line = line.substr(line.find(delim) + 1, std::string::npos);
		}
	}

	// Compares data to requested stock symbol and sets index number.
	for (i = 0; i <= 140; i = i + 4) {

		if (i == 140) {
			std::cout << "\n /!\\ Error! Stock currently not available.\n";
			return -1;
		}

		else if (tokens[i] == symbol)
			break;
	}

	return 0;
}

void updateStocks(int &i, int j, std::vector <std::string> &tokens, std::vector <Profile> &ProfileData) {

	std::string symbol;
	std::string line;
	std::ifstream file;

	symbol = ProfileData[j].symbol;

	// Obtains a random "Stock#.txt" file.
	srand(time(NULL));
	int num = rand() % 4 + 1;
	std::string name = "stock" + std::to_string(num) + ".txt";

	file.open(name);

	// Reads through "Stock#.txt" file and isolates data.
	while (std::getline(file, line)) {

		std::string delim = "\t";
		for (int i = 0; i < 3; i++) {
			if (i == 2) {
				line = line.substr(line.rfind(delim) + 1, std::string::npos);
				tokens.push_back(line);
			}
			tokens.push_back(line.substr(0, line.find(delim)));
			line = line.substr(line.find(delim) + 1, std::string::npos);
		}
	}

	// Compares data to requested stock symbol and sets index number.
	for (i = 0; i <= 140; i = i + 4) {

		if (tokens[i] == symbol)
			break;
	}
}


// Manipulates the stocks profile.
int buyProfile(std::vector <Profile> &ProfileData, int i, std::vector <std::string> tokens, int amount, double price) {

	int j;

	for (j = 0; j <= index + 1; j++) {
		if (ProfileData.empty()) { // Checks if profile is empty.
			++index;
			j = index;
			ProfileData.resize(index + 1);
			break;
		}

		else if (ProfileData[j].symbol == tokens[i]) // Checks if user owns selected stock.
			break;

		else if (ProfileData[j].symbol != tokens[i] && j == index) { // Checks if user does not own selected stock.
			++index;
			j = index;
			ProfileData.resize(index + 1);
			break;
		}
	}

	ProfileData[j].symbol = tokens[i];
	ProfileData[j].company = tokens[i + 1];
	ProfileData[j].number += amount;
	ProfileData[j].price = price;
	ProfileData[j].total += price * amount;

	return 0;
}

int sellProfile(std::vector <Profile> &ProfileData, int i, std::vector <std::string> tokens, int amount, double price) {

	int j;

	for (j = 0; j <= index + 1; j++) {
		
		if (ProfileData.empty()) { // Checks if profile is empty.
			std::cout << "\n /!\\ Error! You do not have any stocks to sell. /!\\ \n";
			return -1;
		}

		else if (ProfileData[j].symbol == tokens[i]) { // Checks if user owns selected stock.
			if (ProfileData[j].number > amount) // Checks if user has enough stocks to sell amount.
				break;
			
			else if (ProfileData[j].number < amount) {
				std::cout << "\n /!\\ Error! You do not own enough stocks to sell this much. /!\\ \n";
				return -1;
			}
		}

		else if (ProfileData[j].symbol != tokens[i] && j == index) { // Checks if user does not own selected stock.
			std::cout << "\n /!\\ Error! You do not own any stocks from this company. /!\\ \n";
			return -1;
		}
	}

	ProfileData[j].symbol = tokens[i];
	ProfileData[j].company = tokens[i + 1];
	ProfileData[j].number -= amount;
	ProfileData[j].price = price;
	ProfileData[j].total -= price * amount;

	return 0;
}

int checkProfile(std::vector <Profile> &ProfileData, int i, std::vector <std::string> tokens, int amount, double price) {

	int j;

	for (j = 0; j <= index; j++) {

		if (ProfileData[j].symbol == tokens[i])
			break;

		else if (ProfileData[j].symbol != tokens[i] && j == index) {
			std::cout << "\n /!\\ Error! You do not own any stocks from this company. /!\\ \n";
			return -1;
		}
	}
}


// Checks for a valid numerical and positive input
int checkInput(int a){
	
	if (typeid(a) != typeid(int) || a < 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\n /!\\ Error! Invalid Input. /!\\\n";
		return -1;
	}

	else if (typeid(a) == typeid(int) && a >= 0)
		return 0;
}

int checkInput(double a) {

	if (typeid(a) != typeid(double) || a < 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\n /!\\ Error! Invalid Input. /!\\\n";
		return -1;
	}

	else if (typeid(a) == typeid(double) && a >= 0)
		return 0;


}


// Dynamically sets tab. Used for transaction history
std::string setTabs(double a) {

	int b = a; // Remove Decimals

	std::string c = std::to_string(b);

	if (c.length() <= 3)
		return "\t\t\t";

	else if (c.length() <= 8)
		return "\t\t";

	else if (c.length() <= 12)
		return "\t";

	else if (c.length() > 12)
		return "";

}

std::string setTabs(int a) {

	std::string c = std::to_string(a);

	if (c.length() <= 4)
		return "\t\t";

	else if (c.length() <= 8)
		return "\t";

	else if (c.length() > 8)
		return "";

}

std::string setTabs(int i, std::vector <std::string> tokens) {

	if (tokens[i].length() <= 4)
		return "\t\t\t\t";

	else if (tokens[i].length() <= 8)
		return "\t\t\t\t";

	else if (tokens[i].length() <= 12)
		return "\t\t\t";

	else if (tokens[i].length() <= 16)
		return "\t\t\t";

	else if (tokens[i].length() <= 20)
		return "\t\t";

	else if (tokens[i].length() <= 24)
		return "\t\t";

	else if (tokens[i].length() <= 28)
		return "\t";

	else if (tokens[i].length() <= 32)
		return "\t";

	else if (tokens[i].length() > 32)
		return "";
}