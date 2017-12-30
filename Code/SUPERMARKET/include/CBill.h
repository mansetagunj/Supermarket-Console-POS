#pragma once

#include <string>
#include <list>
#include "CProduct.h"
#include "CCustomer.h"
#include "CEmployee.h"

using namespace std;

class Bill		//Class Bill
{
public:			//Public members of class Bill
	Bill();
	void setBillNum(unsigned long);
	void setBillAmt(double);
	void setBillDiscount(float);
	void setBillDate(string);
	void setBillTime(string);
	void setBillList(list<Product>);
	unsigned long getBillNum();
	double getBillAmt();
	float getDiscount();
	void printBill(Customer &, Employee &);
	void storeBill(Customer &, Employee &);
	string getBillDate();
	string getBillTime();

private:	//Private members of class Bill
	unsigned long billNum;
	double billAmt;
	float billDiscountAmt;
	string billDate;
	string billTime;
	//Customer billInCust;
	list<Product> productList;

};