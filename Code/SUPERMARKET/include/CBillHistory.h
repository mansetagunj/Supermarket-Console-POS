#pragma once

#include <list>
#include "CBill.h"

using namespace std;

class BillHistory		//class BillHistory
{
public:					//Public members of class BillHostory
	BillHistory() {}
	void setBillHistory(Bill b) { bill = b; }
	void printBillHistory() {}

private:				//Private members of class BillHistory
	list<Bill> listBill;
	Bill bill;
};