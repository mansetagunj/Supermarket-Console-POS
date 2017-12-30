
#include <string>
#include <iostream>
#include <fstream>
#include "CCard.h"
#include "common_helper.h"

using namespace std;

/*Getters & Setters for Card class*/
Card::Card(const string inStr) {

	if (inStr == "add")
	{
		unsigned long long cardnum = 6000000000;
		ofstream OFcustIdFile;
		ifstream  IFcustIdFile;
		IFcustIdFile.open(CUSTOMERID_FILE, std::fstream::binary);
		unsigned long CustId = 0;
		unsigned long BILLNUM = 0;

		while (!IFcustIdFile.eof())
		{
			IFcustIdFile >> CustId >> cardNumber >> BILLNUM;
		}

		IFcustIdFile.close();

		OFcustIdFile.open(CUSTOMERID_FILE, std::fstream::binary);
		if (cardNumber >= cardnum)
			OFcustIdFile << CustId << " " << ++cardNumber << " " << BILLNUM;
		else
		{
			cardNumber = cardnum;
			OFcustIdFile << CustId << " " << cardnum << " " << BILLNUM;
		}

		OFcustIdFile.close();
		points = 0;
	}
	else
	{
		cout << "Invalid String";
	}
}

void Card::setCardNumber(unsigned long long cNumber)
{
	cardNumber = cNumber;
}
void Card::setCardPoints(unsigned cPoints)
{
	points = cPoints;
}
unsigned long long Card::getCardNumber()
{
	return  cardNumber;
}
unsigned Card::getCardPoints()
{
	return points;
}