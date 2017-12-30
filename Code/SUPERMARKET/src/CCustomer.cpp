

#include <fstream>
#include <string>
#include "CCustomer.h"
#include "CError.h"
#include "CCard.h"
#include "common_helper.h"

//CUSTOMER

/*function definition for Customer Class*/


Customer::Customer(const string inStr) {

	unsigned long id = 200000;
	if (inStr == "add") {

		ofstream OFcustIdFile(CUSTOMERID_FILE, std::ofstream::binary | std::ofstream::app);
		if (OFcustIdFile.is_open())
			OFcustIdFile.close();
		ifstream  IFcustIdFile;
		IFcustIdFile.open(CUSTOMERID_FILE, std::ifstream::binary);
		unsigned long long cardNum = 0;
		unsigned long BILLNUM = 0;
		CustId = 0;

		while (!IFcustIdFile.eof())
		{
			IFcustIdFile >> CustId >> cardNum >> BILLNUM;
		}

		IFcustIdFile.close();

		OFcustIdFile.open(CUSTOMERID_FILE, std::fstream::binary);
		if (CustId >= id)
			OFcustIdFile << (++CustId) << " " << cardNum << " " << BILLNUM;
		else
		{
			CustId = id;
			OFcustIdFile << id << " " << cardNum << " " << BILLNUM;
		}

		OFcustIdFile.close();
		//Custcard = new Card(inStr);
		Custcard = Card(inStr);
	}
	else
	{
		errClass err("Invalid Input String while Adding a Customer", -32);
		throw err;
	}
}
void Customer::setCustId(unsigned long CusId)					//setters for Customer
{

	if ((CusId>99999) && (CusId<1000000))
	{
		CustId = CusId;
	}
	else
	{
		errClass err("Invalid Customer ID", -99);
		throw err;
	}
}

void Customer::setCustPhNum(unsigned long long CustPhNo)
{

	if ((CustPhNo>999999999) && (CustPhNo<10000000000))
	{
		CustPhNum = CustPhNo;
	}
	else
	{
		errClass err("Invalid phone number", -99);
		throw err;
	}

}

void Customer::setCardNumber(unsigned long long cardNumber)
{
	if (cardNumber>0)
	{
		Custcard.setCardNumber(cardNumber);
	}
	else
	{
		errClass err("Invalid Customer Card Number", -99);
		throw err;
	}
}

void Customer::setCardPoints(unsigned points)
{
	if (points >= 0)
	{
		Custcard.setCardPoints(points);
	}
	else
	{
		errClass err("Invalid Card points", -99);
		throw err;
	}
}

unsigned long Customer::getCustId()						//getters for Customer
{
	return CustId;
}

unsigned long long Customer::getCustPhNum()
{
	return CustPhNum;
}

unsigned long long Customer::getCardNumber()
{
	return Custcard.getCardNumber();
}

unsigned Customer::getCardPoints()
{
	return Custcard.getCardPoints();
}

bool Customer::operator==(const Customer &inCust){

	return ( CustId == inCust.CustId);

}

ostream& operator<<(ostream& out2, Customer &cust)
{
	out2 << "\nCustomer ID :" << cust.CustId;
	out2 << "\nCustomer PhoneNumer :" << cust.CustPhNum;
	out2 << "\nCustomer Card Number :" << cust.getCardNumber();
	out2 << "\nCustomer Card Points :" << cust.getCardPoints();
	return out2;
}

//File Handling for Customer

//writting to the Customer file

ofstream& operator<<(ofstream &fout, Customer &OfCust)
{	
	fout << "\n" << OfCust.CustId << " " << OfCust.CustPhNum << " " << OfCust.getCardNumber() << " " << OfCust.getCardPoints();
	return fout;
}

//Reading from the Customer file

ifstream& operator>>(ifstream &fin, Customer &IfCust)
{
	unsigned long long cardnum;
	unsigned cardpoint;
	fin >> IfCust.CustId >> IfCust.CustPhNum >> cardnum >> cardpoint;
	IfCust.setCardNumber(cardnum);
	IfCust.setCardPoints(cardpoint);
	return fin;
}