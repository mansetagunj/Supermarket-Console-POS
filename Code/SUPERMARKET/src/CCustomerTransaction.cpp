
#include <iostream>
#include "CCustomerTransaction.h"
#include "CCustomer.h"
#include "CError.h"
#include "common_helper.h"
#include <algorithm>

bool CustomerTransaction::Login() {

	int ch;
	cout << "\n**********************************************************\n";
	cout << "\n\t1. New Customer \t 2.Existing Customer \n";
	cout << "\n**********************************************************\n";
	cout << "\n\tEnter your choice -----> ";
	cin >> ch;
	if (ch == 1) {
		//new customer
		try {
			customer = new Customer("add"); //write the param constructor to add a new customer
			cout << "\n\tEnter Your Mobile Number:  ";
			unsigned long long phnum;
			cin >> phnum;
			customer->setCustPhNum(phnum);
			custcart.setCustid(customer->getCustId());
			list<Customer> li = getList_FromFile<Customer>(CUSTOMER_FILE);
			li.push_back(*customer);
			putList_InFile<Customer>(CUSTOMER_FILE, li);
			return true;
		}
		catch (errClass inerr) {

			inerr.display();
		}
	}
	else if (ch == 2)
	{
		//existing customer
		int count = 0;
		customer = new Customer();
		cout << "\n\tEnter Customer id:  ";
		unsigned long custid;
		cin >> custid;
		customer->setCustId(custid);
		custcart.setCustid(custid);

		list<Customer> li = getList_FromFile<Customer>(CUSTOMER_FILE);
		list<Customer>::iterator itr;
		for (itr = li.begin(); itr != li.end(); itr++) {

			if (customer->getCustId() == itr->getCustId())
			{
				customer->setCustPhNum(itr->getCustPhNum());
				customer->setCardNumber(itr->getCardNumber());
				customer->setCardPoints(itr->getCardPoints());
				return true;
			}
			else
				count++;
		}
		if (count == li.size() || li.size() == 0)
		{
			cout << "\n\tNo customer Id exists.";
			return false;
		}

	}
	else
	{
		cout << "\n\tInvalid Choice.";
		return false;
	}

}


bool CustomerTransaction::searchProductByCategory(Category inCat) {

	bool ret = false;
	list<Product> li = getList_FromFile<Product>(PRODUCT_FILE);

	list<Product>::iterator itr;
	int count = 0;
	for (itr = li.begin(); itr != li.end(); itr++) {

		if (itr->getProductCategoryName() == inCat.getCategoryName() && itr->getProductAvailStock()>0)
		{
			cout << *itr;
			cout << "\n";
			count++;
			ret = true;
		}

	}
	if (count == 0) {

		cout << "\n\tSorry! There are no Products Listed Under this Category.\n";
	}
	return ret;

}

void CustomerTransaction::updateStock_afterOrder() {

	list<Product> li = custcart.getCart();
	unsigned long *prodid = new unsigned long[li.size()];
	list<Product>::iterator itr;
	int i = 0, j;
	for (itr = li.begin(); itr != li.end(); itr++)
	{
		prodid[i] = itr->getProductId();
		i++;
	}
	i--;

	li = getList_FromFile<Product>(PRODUCT_FILE);

	for (itr = li.begin(); itr != li.end(); itr++)
	{
		j = i;
		while (j >= 0)
		{

			if (prodid[j] == itr->getProductId() && itr->getProductAvailStock()>0)
			{
				itr->setProductAvailStock(itr->getProductAvailStock() - 1);
			}
			j--;
		}
	}

	putList_InFile<Product>(PRODUCT_FILE, li);
	delete prodid;

}

void CustomerTransaction::displayMenu() {

	char choice;
	system("COLOR E0");
	do {
		char  ch;
		system("cls");
		string catName;
		unsigned long prodid;
		cout << "\n\t\t\tTEAM 1 SUPERMARKET\n";
		cout << "\n\t" << getDateString();
		cout << "\n\t\t\tWelcome Customer.\n";
		cout << "\n\t\t\tSelect choice\n";
		cout << "********************************************************************************";
		cout << "\n\t\t\t1.Search Products by Category and Add to cart.\n\n";
		cout << "\t\t\t2.Display Cart.\n\n";
		cout << "\t\t\t3.Sort the cart by Product Category and Display.\n\n";
		cout << "\t\t\t4.Sort the cart by Product Cost and Display.\n\n";
		cout << "\t\t\t5.Sort the cart by Product Name and Display.\n\n";
		cout << "\t\t\t6.Place Order.\n\n";
		cout << "\t\t\t7.EXIT.\n";
		cout << "\n********************************************************************************\n";
		cout << "\n\t\tEnter your choice -----> ";
		cin >> choice;

		switch (choice)
		{
		case '1':
			try {
				cout << "\n\t\tEnter category Name: ";
				cin >> catName;
				for_each(catName.begin(), catName.end(), [](char &a) {a = toupper(a); });
				cout << "\n\n";
				category.setCategoryName(catName);
				if (searchProductByCategory(category))
				{
					cout << "\n\tDo you want to add any Products into the cart??\n\n";
					cout << "\t1. Yes Any Other key for No. ---->  ";
					cin >> ch;
					while (ch == '1') {

						cout << "\n\tEnter the Product Id to add to Cart ---> ";
						cin >> prodid;
						custProducts.setProductId(prodid);
						custcart.addToCart(custProducts);
						cout << "\n\tDo you want to add more Products??\n";
						cout << "\t1. Yes Any OTher key for No --->  ";
						cin.clear();
						cin.sync();
						cin >> ch;
					}
				}
			}
			catch (errClass inErr) {
				inErr.display();
			}
			break;

		case '2':
			custcart.displayCart();
			break;
		case '3':
			custcart.sortBy_ProdCategory_displayCart();
			break;
		case '4':
			custcart.sortBy_ProdCost_displayCart();
			break;
		case '5':
			custcart.sortBy_ProdName_displayCart();
			break;
		case '6':
			if (!custcart.getCart().empty())
			{
				cout << "\n\tDo you want to place the order??\n";
				cout << "\t1. Yes Any other key for No ---->  ";
				cin >> ch;
				if (ch == '1') {
					custcart.enterCartToFile();
					updateStock_afterOrder();
					cout << "\n\tCongratulations. Your order has been successfully placed.\n";
					custcart.clearCartList();
				}
			}
			else
				cout << "\n\tSorry. You cannot Place Order. Your Cart is Empty!\n";
			break;
		case '7': choice = '0';
			break;
		default:
			cout << "\n\tInvalid Choice\n";
			break;
		}

		if (choice != '0')
		{
			cin.clear();
			cin.sync();
			cout << "\n\tDo you want to continue as Customer?\n\t1.Yes 0. EXIT ---->  ";
			cin >> choice;
		}
	} while (choice != '0' && choice == '1');
}