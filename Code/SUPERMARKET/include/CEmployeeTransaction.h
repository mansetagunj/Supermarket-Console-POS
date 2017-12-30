#pragma once

#include <string>
#include "CCustomer.h"
#include "CTransaction.h"
#include "CBill.h"
#include "CEmployee.h"
#include "CCart.h"
#include "COffers.h"

class EmployeeTransaction : public Transaction {

public:
	EmployeeTransaction() {}
	bool Login();
	void displayMenu();

private:
	void changeName(string);
	void changePasswd(string);
	bool billing();
	//void addOffers();
	void addDiscount();
	void addPointsToCard();
	void generateBill();
	void updateCart_File();
	void updateCardPoints_File();
	//void getCart();

	//date Members
	Employee employee;
	Cart empCart;
	Customer customer;
	Bill bill;
	Offers empOffers;

};