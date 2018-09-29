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

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <typeinfo>
#include <time.h>
#include <chrono>
#pragma warning(disable : 4996)  // In order to make the date/time functions work in MS Visual Studios.
#include <windows.h>
#undef max

#ifndef Account_h
#define Account_h

class Account {
public:
	Account(double = 10000.00);
	~Account();

	int depositBalance(double);
	int withdrawBalance(double);

	double getBalance();

private:
	static double cashBalance;
};

#endif