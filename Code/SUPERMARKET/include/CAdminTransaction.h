#pragma once

#include "CTransaction.h"
#include "CProduct.h"
#include "CAdmin.h"
#include "CEmployee.h"
#include "COffers.h"

class AdminTransaction : public Transaction {

public:
	AdminTransaction() {}
	bool Login();
	void displayMenu();

private:
	//private functions which are called in the public member function displayMenu();
	//two strings for the new password and confirm password
	void changePasswd(string);
	bool checkAdmin(Admin);
	void addAdmin(Admin);
	void removeAdmin(Admin);
	void addEmployee();
	bool checkEmployee();
	void removeEmployee();
	void addProduct();
	bool checkProduct();
	void removeProduct();
	void addOffers(); //to do
	void updateOffers(); //to do
	void updateStock(Product, unsigned);
	void displayLowStockProducts();

	//date members
	Admin admin;
	Employee Emp;
	Product adminProduct;
	Offers adminOffers;

};