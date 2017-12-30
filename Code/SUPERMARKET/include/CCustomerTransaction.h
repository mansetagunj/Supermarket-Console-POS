#pragma once

#include "CCustomer.h"
#include "CCategory.h"
#include "CProduct.h"
#include "CTransaction.h"
#include "CCart.h"

using namespace std;

class CustomerTransaction : public Transaction {

public:
	CustomerTransaction() {}
	bool Login();
	void displayMenu();
	~CustomerTransaction() {
		if (customer)
		{
			delete customer;
			customer = NULL;
		}
	}

private:
	void signup(Customer);
	bool searchProductByCategory(Category);
	void updateStock_afterOrder();

	//data members
	Customer *customer;
	Category category;
	Product custProducts;
	Cart custcart;

};