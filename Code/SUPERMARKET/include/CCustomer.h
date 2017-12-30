#pragma once

#include <string>
#include <list>
#include <fstream>
#include <iostream>

#include "CCard.h"
//#include "CBillHistory.h"

using namespace std;


class Customer							//Customer Class
{
public:
	Customer() { }//Custcard = new Card(); }
	Customer(const string);//to do
	void setCustId(unsigned long);		//setters
	void setCustPhNum(unsigned long long);
	void setCardNumber(unsigned long long);
	void setCardPoints(unsigned);
	unsigned long getCustId();			//getters
	unsigned long long getCustPhNum();
	unsigned long long getCardNumber();
	unsigned getCardPoints();
	friend ostream& operator<<(ostream&, Customer&);
	friend ofstream& operator<<(ofstream&, Customer&);
	friend ifstream& operator>>(ifstream&, Customer&);
	bool operator==(const Customer&);
	~Customer() {
		//if (Custcard) { delete Custcard; Custcard = NULL; }
	}
private:
	unsigned long CustId;
	unsigned long long CustPhNum;
	//Card *Custcard;
	Card Custcard;
	//BillHistory Custbillhistory;
};