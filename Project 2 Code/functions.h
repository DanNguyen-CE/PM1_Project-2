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

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <typeinfo>
#include <windows.h>
#include <time.h>
#include <chrono>
#pragma warning(disable : 4996) // In order to make the date/time functions work in MS Visual Studios.
#include <windows.h>
#undef max

extern int index;

// Structure for data storage
struct Profile {
	std::string symbol;
	std::string company;
	int number;
	double price;
	double total;
};


// Function Prototypes
int mainMenu();
void close();

void sortProfile(std::vector <Profile> &);

int searchStocks(int &, std::vector <std::string> &);
void updateStocks(int &, int, std::vector <std::string> &, std::vector <Profile> &);

int buyProfile(std::vector <Profile> &, int, std::vector <std::string>, int, double);
int sellProfile(std::vector <Profile> &, int, std::vector <std::string>, int, double);
int checkProfile(std::vector <Profile> &, int, std::vector <std::string>, int, double);

int checkInput(int);
int checkInput(double);

std::string setTabs(double);
std::string setTabs(int);
std::string setTabs(int, std::vector <std::string>);