#pragma once

#include <list>
#include <fstream>
#include "CProduct.h"

using namespace std;



class Cart			//Cart Class
{
public:				//Public members of Cart class
	Cart() {}
	void setCustid(unsigned);
	unsigned getCustid();
	void addToCart(Product &);
	void displayCart();
	list<Product> getCart();
	void sortBy_ProdName_displayCart();
	void sortBy_ProdCost_displayCart();
	void sortBy_ProdCategory_displayCart();
	void enterCartToFile();
	void clearCartList();
	friend ofstream& operator<<(ofstream &, Cart &);
	friend ifstream& operator>>(ifstream &, Cart &);
	friend ostream& operator<<(ostream &, Cart &);

private:			//Private members of Cart class
	unsigned custId;
	list<Product> cartList;

};